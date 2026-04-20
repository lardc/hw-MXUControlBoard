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

// Диапазоны регистров по платам в общем массиве CurrentOutputValues[NUM_REGS_TOTAL].
// Commit 3: прежние две HV-платы каскадированы в одной физической IORelayBoard на SS3,
//           поэтому BOARD1 (REG1..REG3) и BOARD2 (REG4..REG6) выгружаются одной транзакцией.
//           Commit 4 схлопнет таблицу в единый BOARD_IO.
// Порядок индексов соответствует REG1..REGn (младший первый) в CommutationTable.c.
#define ZCRD_IO_REG_FIRST		0
#define ZCRD_IO_REG_COUNT		(2 * NUM_REGS_HV_BOARD)
//
#define ZCRD_THERM_REG_FIRST	(ZCRD_IO_REG_FIRST + ZCRD_IO_REG_COUNT)
#define ZCRD_THERM_REG_COUNT	NUM_REGS_THERM_BOARD
//
#define ZCRD_INPUT_REG_FIRST	(ZCRD_THERM_REG_FIRST + ZCRD_THERM_REG_COUNT)
#define ZCRD_INPUT_REG_COUNT	NUM_REGS_INPUT_BOARD

// Индексы CS для LL_SPI_LatchBoard
#define ZCRD_CS_INPUT			0
#define ZCRD_CS_THERM			1
#define ZCRD_CS_IO				2

// Variables
//
static uint8_t CurrentOutputValues[NUM_REGS_TOTAL] = {0};

// Functions prototypes
//
static void ZcRD_ShiftAndLatch(Int8U CS, Int8U FirstReg, Int8U RegCount);

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

	// Аппаратный SPI1, три независимых CS — каждая плата выгружается отдельной транзакцией.
	// SFT_ENABLE во время штатной выгрузки не трогаем: выход сдвигового регистра меняется
	// только в момент защёлки (CS-импульс). OE управляется аппаратно контуром безопасности.
	ZcRD_ShiftAndLatch(ZCRD_CS_INPUT, ZCRD_INPUT_REG_FIRST, ZCRD_INPUT_REG_COUNT);
	ZcRD_ShiftAndLatch(ZCRD_CS_THERM, ZCRD_THERM_REG_FIRST, ZCRD_THERM_REG_COUNT);
	ZcRD_ShiftAndLatch(ZCRD_CS_IO,    ZCRD_IO_REG_FIRST,    ZCRD_IO_REG_COUNT);

	// Учёт ресурса: инкремент счётчика при каждом изменении состояния бита.
	for (Int16U i = 0; i < COMMUTATION_TABLE_SIZE; ++i)
		if ((PrevCurrentOutputValues[CommutationTable[i].RegNum] & CommutationTable[i].Bit) !=
			(CurrentOutputValues[CommutationTable[i].RegNum] & CommutationTable[i].Bit))
			CycleCounters[i]++;

	for (Int16U i = 0; i < NUM_REGS_TOTAL; ++i)
		PrevCurrentOutputValues[i] = CurrentOutputValues[i];
}
// ----------------------------------------

static void ZcRD_ShiftAndLatch(Int8U CS, Int8U FirstReg, Int8U RegCount)
{
	// Байты выгружаются от последнего регистра к первому — чипы каскадированы,
	// и первая отправленная порция окажется в самом дальнем регистре.
	for (int8_t i = (int8_t)(FirstReg + RegCount) - 1; i >= (int8_t)FirstReg; i--)
		LL_SPI_WriteByte(CurrentOutputValues[i]);

	LL_SPI_LatchBoard(CS);
}
// ----------------------------------------
