// Includes
#include "Board.h"
#include "Logic.h"
#include "DataTable.h"
#include "LowLevel.h"
#include "Math.h"
#include "Delay.h"
#include "Controller.h"


// Variables
Int16U MeasurementPosition = 1;
//

// Functions prototypes


// Functions
//
void LOGIC_ResetOutputRegisters()
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

void LOGIC_UpdatePosition()
{
	MeasurementPosition = DataTable[REG_MEASUREMENT_POSITION];
}

void LOGIC_ResetSFSystem()
{
	LL_SetStateSF_EN(false);
}
