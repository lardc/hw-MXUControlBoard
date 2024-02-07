// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"
#include "ZcRegistersDriver.h"
#include "CommutationTable.h"

// Functions
//
// Send pulse to Front Panel LED
void DBACT_ToggleFPLed()
{
	LL_SetStateFPLed(true);
	DELAY_MS(1000);
	LL_SetStateFPLed(false);
}
//-----------------------

// Send pulse to Safety Subsystem Red LED
void DBACT_ToggleSFRedLed()
{
	LL_SetStateSFRedLed(true);
	DELAY_MS(1000);
	LL_SetStateSFRedLed(false);
}
//-----------------------

// Send pulse to Safety Subsystem Green LED
void DBACT_ToggleSFGreenLed()
{
	LL_SetStateSFGreenLed(true);
	DELAY_MS(1000);
	LL_SetStateSFGreenLed(false);
}
//-----------------------

void DBACT_WriteSPI()
{
	// Чтение номера таблицы коммутации из отладочного регистра
	//ZcRD_OutputValuesCompose(DataTable[REG_DBG], TRUE);
	// Коммутация выбранной комбинации
	//ZcRD_RegisterFlushWrite();

	Int16U RegData[NUM_REGS_TOTAL] = {0};
	Int16U RegNum = ((Int16U)DataTable[REG_DBG]) >> 8;

	RegData[RegNum] = (Int16U)DataTable[REG_DBG] & 0xFF;

	for(int i = NUM_REGS_TOTAL - 1; i >= 0; i--)
		LL_SPI_WriteByte(RegData[i]);

	DELAY_US(TIME_SPI_DELAY);

	GPIO_SetState(GPIO_SPI_SS, true);
	DELAY_US(TIME_SPI_DELAY);
	GPIO_SetState(GPIO_SPI_SS, false);
}
//-----------------------

// Turn self-test current ON, measure voltage with ADC, compare result with DataTable constant
void DBACT_SelfTestMeasure()
{
	DataTable[REG_SELF_TEST_OP_RESULT] = IsTestCurrent() ? OPRESULT_OK : OPRESULT_FAIL;
}
//-----------------------
