// Header
//
#include "PMXU.h"

// Includes
//
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "BCCIMHighLevel.h"
#include "LowLevel.h"
#include "Delay.h"

// Variables
//
volatile PMXUProcess PMXU_ProcessState = PP_None;

// Function prototypes
//
bool PMXU_CallAction(Int16U Action);
bool PMXU_WriteReg(Int16U RegAddress, Int16U RegData);


// Functions
//
bool PMXU_StartSelfTest()
{
	return PMXU_CallAction(ACT_PMXU_SELFTEST);
}
//--------------------------------------

bool PMXU_Enable()
{
	return PMXU_CallAction(ACT_PMXU_ENABLE_POWER);
}
//--------------------------------------

bool PMXU_Disable()
{
	return PMXU_CallAction(ACT_PMXU_DISABLE_POWER);
}
//--------------------------------------

bool PMXU_IsReady()
{
	return (DataTable[REG_PMXU_EMULATED]) ? true : (PMXU_CheckState(PS_Enabled) || PMXU_CheckState(PS_SafetyActive));
}
//--------------------------------------

bool PMXU_InFault()
{
	return (DataTable[REG_PMXU_EMULATED]) ? false : PMXU_CheckState(PS_Fault);
}
//--------------------------------------

bool PMXU_CheckState(PMXUState State)
{
	Int16U PMXU_State = 0;

	if(DataTable[REG_PMXU_EMULATED])
		return true;

	if(BHL_ReadRegister(DataTable[REG_PMXU_CAN_ID], REG_PMXU_DEV_STATE, &PMXU_State))
		return (PMXU_State == State) ? true : false;
	else
		CONTROL_SwitchToFault(DF_PMXU_INTERFACE);

	return false;
}
//--------------------------------------

bool PMXU_SwitchCommutation(Int16U Position, Int16U DevCase, Int16U Scheme,Int16U CommutationNumber)
{
	if(PMXU_WriteReg(REG_PMXU_DUT_POSITION, Position))
		if(PMXU_WriteReg(REG_PMXU_DEV_CASE, DevCase))
			return PMXU_CallAction(CommutationNumber);

	return false;
}
//--------------------------------------

bool PMXU_ClearFault()
{
	return PMXU_CallAction(ACT_PMXU_CLR_FAULT);
}
//--------------------------------------

bool PMXU_ClearWarning()
{
	return PMXU_CallAction(ACT_PMXU_CLR_WARNING);
}
//--------------------------------------

bool PMXU_SafetyActivate()
{
	if(PMXU_CallAction(ACT_PMXU_SET_ACTIVE))
	{
		DELAY_MS(10);

		if(PMXU_CheckState(DS_SafetyActive))
			return true;
	}

	return false;
}
//--------------------------------------

bool PMXU_SafetyDeactivate()
{
	if(PMXU_CallAction(ACT_PMXU_SET_INACTIVE))
	{
		DELAY_MS(10);

		if(PMXU_CheckState(DS_Enabled))
			return true;
	}

	return false;
}
//--------------------------------------

bool PMXU_CallAction(Int16U Action)
{
	if(DataTable[REG_PMXU_EMULATED])
		return true;

	if(BHL_Call(DataTable[REG_PMXU_CAN_ID], Action))
		return true;
	else
	{
		CONTROL_SwitchToFault(DF_PMXU_INTERFACE);
		return false;
	}
}
//--------------------------------------

bool PMXU_WriteReg(Int16U RegAddress, Int16U RegData)
{
	if(DataTable[REG_PMXU_EMULATED])
		return true;

	if(BHL_WriteRegister(DataTable[REG_PMXU_CAN_ID], RegAddress, RegData))
		return true;
	else
	{
		CONTROL_SwitchToFault(DF_PMXU_INTERFACE);
		return false;
	}
}
//--------------------------------------

void PMXU_Process()
{
	switch(PMXU_ProcessState)
	{
		case PP_CheckReadyAndFault:
			if(PMXU_InFault())
			{
				PMXU_ProcessState = PP_None;
				CONTROL_SwitchToFault(DF_PMXU);
			}
			else if(!PMXU_IsReady())
			{
				PMXU_ProcessState = PP_None;
				CONTROL_FinishedWithProblem(PROBLEM_PMXU_NOT_READY);
			}
			else
				PMXU_ProcessState = PP_Commutation;
			break;

		case PP_Commutation:
			{
				Int16U PMXU_Command;
				switch(COMM_State)
				{
					case COMM_Iges_Pos:
					case COMM_Iges_Neg:
					case COMM_Ugeth:
						PMXU_Command = ACT_PMXU_COMM_NO_PE;
						break;
					case COMM_Ucesat:
						PMXU_Command = ACT_PMXU_COMM_VCESAT;
						break;
					case COMM_Uf:
						PMXU_Command = ACT_PMXU_COMM_VF;
					default:
						break;
				}
				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DUT_CASE],
						DataTable[REG_DUT_SCHEME], PMXU_Command))
					PMXU_ProcessState = PP_CheckStatus;
				else
					PMXU_ProcessState = PP_None;
			}
			break;

		case PP_CheckStatus:
			if(PMXU_InFault())
				CONTROL_SwitchToFault(DF_PMXU);
			else if(!PMXU_IsReady())
				CONTROL_FinishedWithProblem(PROBLEM_PMXU_FAILED_TO_FINISH);
			else
				DataTable[REG_OP_RESULT] = OPRESULT_OK;

			PMXU_ProcessState = PP_None;
			break;

		default:
			break;
	}
}
//--------------------------------------
