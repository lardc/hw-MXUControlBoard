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

void LL_ResetRegisters()
{
	// Reset all shift-registers
	GPIO_SetState(GPIO_SPI_RST, false);
	DELAY_MS(5);
	GPIO_SetState(GPIO_SPI_RST, true);
}

void LL_WriteSPI(uint8_t SPI_Data[], uint8_t Data_Length)
{
	// Reset all shift-registers
	GPIO_SetState(GPIO_SPI_RST, false);
	DELAY_MS(5);
	GPIO_SetState(GPIO_SPI_RST, true);

	// Latch outputs of shift-registers
	GPIO_SetState(GPIO_SPI_SS, false);

	// Send 15 bytes of data
	for (int i = 0; i<=Data_Length; i++)
		SPI_WriteByte(SPI3, SPI_Data[i]);

	// Turn outputs ON
	GPIO_SetState(GPIO_SPI_OE, true);
}
//-----------------------------

void LL_StopSPI()
{
	// Turn outputs OFF
	GPIO_SetState(GPIO_SPI_OE, false);

	GPIO_SetState(GPIO_SPI_SS, true);

	// Reset all shift-registers
	GPIO_SetState(GPIO_SPI_RST, false);
	DELAY_MS(5);
	GPIO_SetState(GPIO_SPI_RST, true);
}
//-----------------------------

void LL_SetStateSF_EN(bool State)
{
	GPIO_SetState(GPIO_SF_EN, State);
}
//-----------------------------

void LL_SetStateSD_EN(bool State)
{
	GPIO_SetState(GPIO_SD_EN, State);
}
//-----------------------------

float LL_SelfTestMeasure()
{
	float MeasuredTestVoltage;

	// Enable self-test current
	LL_SetStateSD_EN(true);
	DELAY_MS(5);
	// Measure test-point and convert value to voltage
	MeasuredTestVoltage = (float)ADC_Measure(ADC1, ADC_V_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
	// Disable self-test current
	LL_SetStateSD_EN(false);

	// Compare measured value of voltage to constant value of closed-circuit (normal operation mode) voltage ADC_V_CC
	// Error = (MeasuredTestVoltage - ADC_V_CC) / ADC_V_CC * 100;
	// return (Error >= DataTable[REG_SFTST_V_ALLOWED_ERR]) ? false : true;
	return MeasuredTestVoltage;
}
