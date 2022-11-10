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

void LL_SetStateFP_LED(bool State)
{
	GPIO_SetState(GPIO_FP_LED, State);
}
//-----------------------------

void LL_SetStateSF_RED_LED(bool State)
{
	GPIO_SetState(GPIO_SF_RED_LED, State);
}
//-----------------------------

void LL_SetStateSF_GRN_LED(bool State)
{
	GPIO_SetState(GPIO_SF_GRN_LED, State);
}
//-----------------------------

void LL_SetStateSPI_SS(bool State)
{
	GPIO_SetState(GPIO_SPI_SS, State);
}
//-----------------------------

void LL_SetStateSPI_RST(bool State)
{
	GPIO_SetState(GPIO_SPI_RST, State);
}
//-----------------------------

void LL_SetStateSPI_OE(bool State)
{
	GPIO_SetState(GPIO_SPI_OE, State);
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

float LL_ADC_Measure()
{
	float MeasuredTestVoltage;
	MeasuredTestVoltage = (float)ADC_Measure(ADC1, ADC_V_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
	return MeasuredTestVoltage;
}
