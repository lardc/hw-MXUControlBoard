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
#include "SelfTest.h"
#include "CommutationTable.h"
#include "Commutator.h"
#include "ZcRegistersDriver.h"

// Definitions
//


// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
//
volatile Int64U CONTROL_TimeCounter = 0;
//

// Forward functions
//
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_LogicProcess();
void CONTROL_SaveTestResult();

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
	//CONTROL_LogicProcess();

	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_SaveTestResult()
{
	DataTable[REG_OP_RESULT] = OPRESULT_OK;
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;

	CONTROL_SetDeviceSubState(NewSubState);
}
//------------------------------------------

void CONTROL_SetDeviceSubState(DeviceSubState NewSubState)
{
	CONTROL_SubState = NewSubState;
	DataTable[REG_SUB_STATE] = NewSubState;
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	CONTROL_ResetOutputRegisters();
	CONTROL_SetDeviceState(DS_None, SS_None);
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
				CONTROL_ResetOutputRegisters();
				CONTROL_SetDeviceState(DS_None, SS_None);
			}
			else if(CONTROL_State != DS_Ready)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_None, SS_None);
			}
			else if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
			{
				CONTROL_SetDeviceState(DS_None, SS_None);
				DataTable[REG_FAULT_REASON] = DF_NONE;
			}
			break;

		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = WARNING_NONE;
			break;

		case ACT_SF_DEACTIVATE:
			CONTROL_ResetSFSystem();
			break;

		case ACT_COMM_ILEAK_GATE_EMITTER_POS_PULSE:
		case ACT_COMM_ILEAK_GATE_EMITTER_NEG_PULSE:
		case ACT_COMM_UTH_GATE_EMITTER:
		case ACT_COMM_Q_GATE:
		case ACT_COMM_USAT_COLLECTOR_EMITTER:
		case ACT_COMM_UFW_CHOPPER_DIODE:
		case ACT_COMM_ILEAK_COLLECTOR_EMITTER:
		case ACT_COMM_THERMISTOR:
		case ACT_COMM_NO_PE:
		case ACT_COMM_NONE:
			if (CONTROL_State == DS_Fault)
				*pUserError = ERR_OPERATION_BLOCKED;
			//else if(CONTROL_State == DS_None)
				//*pUserError = ERR_DEVICE_NOT_READY;
			else
			{
				COMM_Commutate(ActionID);
				if (CONTROL_State == DS_Fault)
				{
					CONTROL_CommutateNone();
					CONTROL_SetDeviceState(DS_None, SS_None);
				}
			}
			break;

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);

	}
	return true;
}
//-----------------------------------------------

void CONTROL_LogicProcess()
{
	static Int64U Delay = 0;

	if(CONTROL_State == DS_InProcess)
	{
		switch(CONTROL_SubState)
		{
			case SS_StartUp:
				Delay = CONTROL_TimeCounter + DataTable[REG_PS_FIRST_START_TIME];
				CONTROL_SetDeviceState(DS_InProcess, SS_WaitDelay);
				break;

			case SS_WaitDelay:
				if (CONTROL_TimeCounter >= Delay)
					CONTROL_SetDeviceState(DS_InProcess, SS_StartSelfTest);
				break;

			case SS_StartSelfTest:
				if(DataTable[REG_SELF_TEST_ACTIVE])
				{
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_StartPrepare);
				}
				else
					CONTROL_SetDeviceState(DS_InProcess, SS_InProcess);
				break;

			case SS_InProcess:
					if(REG_SELF_TEST_OP_RESULT == 1)
					{
						CONTROL_SetDeviceState(DS_InProcess, SS_InProcess);
					}
					else
						CONTROL_SetDeviceState(DS_Fault, SS_None);
				break;

			default:
				break;

		}
	}
	else if(CONTROL_State == DS_InProcess)
	{
		SELFTEST_Process();
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

void CONTROL_CommutateNone()
{
	COMM_CommutateNone();
}
// ----------------------------------------

void CONTROL_ResetSFSystem()
{
	LL_SetStateSF_EN(false);
}
//------------------------------------------
