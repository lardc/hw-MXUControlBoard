// Header
#include "Controller.h"
//
// Includes
#include "Board.h"
#include "Delay.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "LowLevel.h"
#include "SysConfig.h"
#include "DebugActions.h"
#include "Diagnostic.h"
#include "BCCIxParams.h"
#include "CommutationTable.h"
#include "ZcRegistersDriver.h"
#include "PMXU.h"
#include "BCCIMHighLevel.h"
#include "SelfTest.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSelfTestState CONTROL_SubState = STS_None;
static Boolean CycleActive = false;
volatile Int64U CONTROL_TimeCounter = 0;
//
DevType AllowedCases[] = {SC_Type_MIAA, SC_Type_MIDA, SC_Type_MIFA, SC_Type_MIHA, SC_Type_MIHM, SC_Type_MIHV, SC_Type_MISM, SC_Type_MISV,
							SC_Type_MIXM, SC_Type_MIXV, SC_Type_MISM2_CH, SC_Type_MISM2_SS_SD, SC_Type_MIADAP};

// Forward functions
//
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_SafetyCheck();
bool CONTROL_DevCaseCheck(DevType DevCase);

// Functions
//
void CONTROL_Init()
{
	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_NID, 0);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);

	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_Idle()
{
	CONTROL_SafetyCheck();
	SELFTEST_Process();

	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	if(Reason == DF_PMXU_INTERFACE)
	{
		BHLError Error = BHL_GetError();
		DataTable[REG_EXT_UNIT_ERROR_CODE] = Error.ErrorCode;
		DataTable[REG_EXT_UNIT_FUNCTION] = Error.Func;
		DataTable[REG_EXT_UNIT_EXT_DATA] = Error.ExtData;
	}

	CONTROL_SetDeviceState(DS_Fault);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//------------------------------------------

void CONTROL_SetDeviceSubState(DeviceSelfTestState NewSubState)
{
	CONTROL_SubState = NewSubState;
	DataTable[REG_SUB_STATE] = NewSubState;
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	CONTROL_ResetOutputRegisters();
	COMM_Default();
	LL_SetStateSFGreenLed(true);

	CONTROL_SetDeviceState(DS_None);
	CONTROL_SetDeviceSubState(STS_None);
}
//------------------------------------------

bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			if(CONTROL_State == DS_None)
			{
				if(PMXU_Enable())
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_NONE;
					CONTROL_SetDeviceState(DS_InSelfTest);
					CONTROL_SetDeviceSubState(STS_InputBoard);
				}
			}
			else if(CONTROL_State != DS_Enabled)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Enabled)
			{
				if(PMXU_Disable())
				{
					COMM_Default();
					CONTROL_SetDeviceState(DS_None);
				}
			}
			else if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
			{
				if(PMXU_ClearFault() && PMXU_Disable())
				{
					CONTROL_SetDeviceState(DS_None);
					CONTROL_SetDeviceSubState(STS_None);
					DataTable[REG_FAULT_REASON] = DF_NONE;
				}
			}
			break;

		case ACT_CLR_WARNING:
			PMXU_ClearWarning();
			DataTable[REG_WARNING] = WARNING_NONE;
			break;

		case ACT_SET_ACTIVE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive)
			{
				if(PMXU_SafetyActivate())
				{
					LL_SetStateSFRedLed(true);
					LL_SetStateSFGreenLed(false);
					CONTROL_SetDeviceState(DS_SafetyActive);
				}
			}
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_SET_INACTIVE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
			{
				if(PMXU_SafetyDeactivate())
				{
					LL_SetStateSFRedLed(false);
					LL_SetStateSFGreenLed(true);
					CONTROL_SetDeviceState(DS_Enabled);
				}
			}
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_SELFT_TEST:
			if(CONTROL_State == DS_Enabled)
			{
				if(PMXU_IsReady())
				{
					if(PMXU_StartSelfTest())
					{
						DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_NONE;
						CONTROL_SetDeviceState(DS_InSelfTest);
						CONTROL_SetDeviceSubState(STS_InputBoard);
					}
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			else if(CONTROL_State != DS_Enabled)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_COMM_IGES_POS_PULSE:
		case ACT_COMM_IGES_NEG_PULSE:
		case ACT_COMM_UGE_TH:
		case ACT_COMM_QG:
		case ACT_COMM_UCE_SAT:
		case ACT_COMM_UFW_CHOPPER_DIODE:
		case ACT_COMM_ICES:
		case ACT_COMM_THERMISTOR:
		case ACT_COMM_NO_PE:
		case ACT_COMM_NONE:
			if (CONTROL_State == DS_Fault)
				*pUserError = ERR_OPERATION_BLOCKED;
			else if(CONTROL_State == DS_None || !PMXU_IsReady())
			{
				if(PMXU_InFault())
					CONTROL_SwitchToFault(DF_PMXU);

				*pUserError = ERR_DEVICE_NOT_READY;
			}
			else
				if(CONTROL_DevCaseCheck(DataTable[REG_DEV_CASE]) || ActionID == ACT_COMM_NONE || ActionID == ACT_COMM_NO_PE)
					COMM_Commutate(ActionID);
				else
					*pUserError = ERR_OPERATION_BLOCKED;
			break;

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
	}
	return true;
}
//-----------------------------------------------

bool CONTROL_DevCaseCheck(DevType DevCase)
{
	for(int i = 0; i < sizeof(AllowedCases) / 2; i++)
	{
		if(DevCase == AllowedCases[i])
			return true;
	}

	return false;
}
//-----------------------------------------------

void CONTROL_SafetyCheck()
{
	static Int64U SafetyTimer = 0;

	if(DataTable[REG_SAFETY_ACTIVE])
	{
		if(LL_IsSafetyTrig())
		{
			LL_SetStateSF_EN(false);
			SafetyTimer = CONTROL_TimeCounter + DataTable[REG_SAFETY_DELAY];

			if(CONTROL_State == DS_SafetyActive)
				CONTROL_SetDeviceState(DS_SafetyTrig);

			if(COMM_State != COMM_Def)
				COMM_Default();
		}
		else
			if(CONTROL_TimeCounter >= SafetyTimer)
				LL_SetStateSF_EN(true);
	}
}
//-----------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

void CONTROL_ResetOutputRegisters()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	//
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//------------------------------------------

void CONTROL_HandleFrontPanelLamp(CommutationState Commutation)
{
	static Int64U FPLampCounter = 0;
	bool Forced = false;
	static CommutationState LastCommutation = 0;

	if(LastCommutation != Commutation)
	{
		LastCommutation = Commutation;
		Forced = true;
	}

	if(CONTROL_State == DS_Fault)
	{
		if(++FPLampCounter > TIME_FP_LED_FAULT_BLINK)
		{
			LL_ToggleFPLed();
			FPLampCounter = 0;
		}
	}
	else
	{
		if(CONTROL_State == DS_InSelfTest)
			LL_SetStateFPLed(true);
		else
		{
			if(CONTROL_State != DS_SafetyTrig)
			{
				if(CONTROL_State == DS_None && FPLampCounter)
				{
					LL_SetStateFPLed(false);
					FPLampCounter = 0;
				}

				if(CONTROL_State != DS_None)
				{
					if(Forced)
					{
						LL_SetStateFPLed(true);
						FPLampCounter = CONTROL_TimeCounter + TIME_FP_LED_ON_STATE;
					}
					else
					{
						if(CONTROL_TimeCounter >= FPLampCounter)
							LL_SetStateFPLed(false);
					}
				}
			}
		}
	}
}
//-----------------------------------------------
