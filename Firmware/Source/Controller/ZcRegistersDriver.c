// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

// Header
#include "ZcRegistersDriver.h"
//
#include "SysConfig.h"
#include "CommutationTable.h"
#include "LowLevel.h"
#include "Delay.h"
#include "DataTable.h"

// Variables
//
static uint8_t CurrentOutputValues[NUM_REGS_TOTAL] = {0};

// Functions
//
void ZcRD_RegisterReset()
{
	// Set values to zero
	ZcRD_OutputValuesReset();
	ZcRD_RegisterFlushWrite();

	DELAY_US(COMM_DELAY_MS * 1000L);
}
// ----------------------------------------

void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn)
{
	if (TurnOn)
		CurrentOutputValues[CommutationTable[TableID].RegNum] |= CommutationTable[TableID].Bit;
	else
		CurrentOutputValues[CommutationTable[TableID].RegNum] &= ~CommutationTable[TableID].Bit;
}
// ----------------------------------------

void ZcRD_OutputValuesReset()
{
	for (uint8_t i = 0; i < NUM_REGS_TOTAL; ++i)
		CurrentOutputValues[i] = 0;
}
// ----------------------------------------

void ZcRD_RegisterFlushWrite()
{
	static uint8_t PrevCurrentOutputValues[NUM_REGS_TOTAL] = {0};
	for (Int16U i = 0; i < NUM_REGS_TOTAL; ++i)
	{
		PrevCurrentOutputValues[i] = CurrentOutputValues[i];
	}

	GPIO_SetState(GPIO_SPI_OE, false);
	for(int8_t i = NUM_REGS_TOTAL - 1; i >= 0; i--)
		LL_SPI_WriteByte(CurrentOutputValues[i]);

	DELAY_US(TIME_SPI_DELAY);
	GPIO_SetState(GPIO_SPI_SS, true);
	DELAY_US(TIME_SPI_DELAY);
	GPIO_SetState(GPIO_SPI_SS, false);
	DELAY_US(TIME_SPI_DELAY);
	GPIO_SetState(GPIO_SPI_OE, true);
}
// ----------------------------------------
