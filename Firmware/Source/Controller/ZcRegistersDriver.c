// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

// Header
#include "ZcRegistersDriver.h"
//
#include "SysConfig.h"
#include "CommutationTable.h"
#include "LowLevel.h"


// Constants
//
#define IOE_OUT_CL					16
#define IO_REGISTER_WRITE_DELAY_US	10


// Variables
//
static Int16U CurrentOutputValues[COMMUTATION_EXT_BOARDS];

void ZcRD_RegisterReset()
{
	// Set values to zero
	ZcRD_OutputValuesReset();
	// Reset physical register
	LL_ResetRegisters();
}
// ----------------------------------------

void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn)
{
	if (TurnOn)
		CurrentOutputValues[CommutationTable[TableID].BoardNum] |= CommutationTable[TableID].Bit;
	else
		CurrentOutputValues[CommutationTable[TableID].BoardNum] &= ~CommutationTable[TableID].Bit;
}
// ----------------------------------------

void ZcRD_OutputValuesReset()
{
	Int16U i;

	for (i = 0; i < COMMUTATION_EXT_BOARDS; ++i)
		CurrentOutputValues[i] = 0;
}
// ----------------------------------------

void ZcRD_RegisterFlushWrite()
{
	Int16U CurrentOutputValuesCopy[COMMUTATION_EXT_BOARDS];

	for (int i = 0; i<=COMMUTATION_EXT_BOARDS; i++)
			SPI_WriteByte(SPI3, CurrentOutputValuesCopy[i]);
}
// ----------------------------------------

// No more.
