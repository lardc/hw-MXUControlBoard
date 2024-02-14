// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"
#include "Global.h"
#include "DataTable.h"

// Functions
//
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_SetStateFPLed(bool State)
{
	GPIO_SetState(GPIO_FP_LED, State);
}
//-----------------------------

void LL_ToggleFPLed()
{
	GPIO_Toggle(GPIO_FP_LED);
}
//-----------------------------

void LL_SetStateSFRedLed(bool State)
{
	GPIO_SetState(GPIO_SF_RED_LED, State);
}
//-----------------------------

void LL_SetStateSFGreenLed(bool State)
{
	GPIO_SetState(GPIO_SF_GRN_LED, State);
}
//-----------------------------

void LL_WriteSPI(uint8_t SPI_Data[], uint8_t Data_Length)
{
	// Turn outputs OFF
	GPIO_SetState(GPIO_SPI_OE, true);

	// Shift-registers reset
	LL_SPIReset();

	GPIO_SetState(GPIO_SPI_SS, false);

	for (int i = 0; i <= Data_Length; i++)
	{
		LL_SPI_WriteByte(SPI_Data[i]);
		GPIO_SetState(GPIO_SPI_SS, true);
		GPIO_SetState(GPIO_SPI_SS, false);
	}

	// Turn outputs ON
	GPIO_SetState(GPIO_SPI_OE, false);
}
//-----------------------------

void LL_SPI_WriteByte(Int8U Data)
{
	for (int i = 7; i >= 0; i--)
	{
		GPIO_SetState(GPIO_SPI_DAT, (Data >> i) & 0x1);
		DELAY_US(TIME_SPI_DELAY);
		GPIO_SetState(GPIO_SPI_CLK, true);
		DELAY_US(TIME_SPI_DELAY);
		GPIO_SetState(GPIO_SPI_CLK, false);
	}
}
//-----------------------------

void LL_SPIReset()
{
	GPIO_SetState(GPIO_SPI_RST, false);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI_RST, true);
}
//-----------------------------

void LL_SetStateSF_EN(bool State)
{
	GPIO_SetState(GPIO_SF_EN, !State);
}
//-----------------------------

void LL_SetStateSD_EN(bool State)
{
	GPIO_SetState(GPIO_SD_EN, State);
}
//-----------------------------

bool IsTestCurrent()
{
	float MeasuredTestVoltage = (float)ADC_Measure(ADC1, ADC_V_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
	DataTable[REG_DBG2] = MeasuredTestVoltage;
	return (MeasuredTestVoltage < DataTable[REG_SFTST_V_ALLOWED_VOLTAGE]) ? true : false;
}
//-----------------------------

bool LL_IsSafetyTrig()
{
	return !GPIO_GetState(GPIO_SF_TRIG);
}
//-----------------------------
