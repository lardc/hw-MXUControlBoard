﻿// Header
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
	ZcRD_OutputValuesCompose(DataTable[REG_DBG], TRUE);
	// Коммутация выбранной комбинации
	ZcRD_RegisterFlushWrite();
}
//-----------------------

// Turn self-test current ON, measure voltage with ADC, compare result with DataTable constant
void DBACT_SelfTestMeasure()
{
	LL_SetStateSD_EN(true);
	DELAY_MS(100);
	DataTable[REG_SELF_TEST_OP_RESULT] = IsTestCurrent() ? OPRESULT_OK : OPRESULT_FAIL;
	DELAY_MS(100);
	LL_SetStateSD_EN(false);
}
//-----------------------
void DBACT_SDEN()

{
	LL_SetStateSD_EN(true);
	DELAY_MS(100);
	LL_SetStateSD_EN(false);
}
