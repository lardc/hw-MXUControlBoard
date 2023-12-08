// Header
//
#include "PMXU.h"

// Includes
//
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "BCCIMHighLevel.h"
#include "LowLevel.h"

// Function prototypes
//
bool PMXU_CheckState(PMXUState State);
bool PMXU_CallAction(Int16U Action);


// Functions
//
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
	return (DataTable[REG_PMXU_EMULATED]) ? true : PMXU_CheckState(PS_Ready);
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

	if(BHL_ReadRegister(DataTable[REG_PMXU_CAN_ID], REG_PMXU_DEV_STATE, &PMXU_State))
		return (PMXU_State == State) ? true : false;
	else
		CONTROL_SwitchToFault(DF_PMXU_INTERFACE);

	return false;
}
//--------------------------------------

bool PMXU_SwitchCommutation(Int16U CommutationNumber)
{
	return PMXU_CallAction(CommutationNumber);
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
