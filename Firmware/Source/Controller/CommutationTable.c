// -----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "CommutationTable.h"

// Output pins bindings
// PIN_XY -> where X = number of shift-register, Y = number of pin
#define PIN_RC0		BIT0
#define PIN_RC1		BIT1
#define PIN_RC2		BIT2
#define PIN_RC3		BIT3
#define	PIN_RC4		BIT4
#define	PIN_RC5		BIT5
#define	PIN_RC6		BIT6
#define	PIN_RC7		BIT7

// Extension board indexes — совпадают с индексами CS у LL_SPI_LatchBoard
// и с порядком выгрузки в ZcRD_RegisterFlushWrite.
//---------------------------------
#define BOARD_INPUT		0		// InputRelayBoard (SS1)
#define BOARD_THERM		1		// OutThermRelayBoard (SS2)
#define BOARD_IO		2		// IORelayBoard (SS3, объединение прежних OutHVRelayBoard-1/2)

// Номера регистров в физическом буфере CurrentOutputValues[NUM_REGS_TOTAL].
// Порядок — IO → Therm → Input, согласуется с ZCRD_*_REG_FIRST в ZcRegistersDriver.
#define REG_IO_1		0
#define REG_IO_2		1
#define REG_IO_3		2
#define REG_IO_4		3
#define REG_THERM_1		4
#define REG_INPUT_1		5
#define REG_INPUT_2		6
#define REG_INPUT_3		7

// Variables
//
Int64U CT_SaveTimer = 0;

// Constants
//
Int32U CycleCounters[COMMUTATION_TABLE_SIZE] = {0};

// Текущая таблица — заглушка под матрицу Trello 7A6GZMVv.
// Сигналы Position 2 на IORelayBoard пока aliased на одноимённые Position 1
// (см. CommutationTable.h), поэтому в таблице явно присутствуют только
// Position 1, Therm и Input. Resные слоты IO (22..31) и Input (60..63) помечены как резерв.
const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE] =
{
		// ===== IORelayBoard (BOARD_IO, SS3) — Position 1 =====
		{BOARD_IO, PIN_RC0, REG_IO_1},		// 0  C_POT_PE
		{BOARD_IO, PIN_RC1, REG_IO_1},		// 1  G_PE
		{BOARD_IO, PIN_RC2, REG_IO_1},		// 2  GE_PE
		{BOARD_IO, PIN_RC3, REG_IO_1},		// 3  E_POT_PE
		{BOARD_IO, PIN_RC4, REG_IO_1},		// 4  OL_C_POT_COMM
		{BOARD_IO, PIN_RC5, REG_IO_1},		// 5  OL_G_COMM
		{BOARD_IO, PIN_RC6, REG_IO_1},		// 6  OL_GE_COMM
		{BOARD_IO, PIN_RC7, REG_IO_1},		// 7  OL_E_POT_COMM
		//
		{BOARD_IO, PIN_RC0, REG_IO_2},		// 8  MC_G_C_POT
		{BOARD_IO, PIN_RC1, REG_IO_2},		// 9  MC_G_GE
		{BOARD_IO, PIN_RC2, REG_IO_2},		// 10 MC_GE_GT_G
		{BOARD_IO, PIN_RC3, REG_IO_2},		// 11 MC_GE_GT_GE
		{BOARD_IO, PIN_RC4, REG_IO_2},		// 12 MC_GE_LSL_GE
		{BOARD_IO, PIN_RC5, REG_IO_2},		// 13 MC_G_GT_G
		{BOARD_IO, PIN_RC6, REG_IO_2},		// 14 MC_G_GT_GE
		{BOARD_IO, PIN_RC7, REG_IO_2},		// 15 MC_G_GT_G_POT
		//
		{BOARD_IO, PIN_RC0, REG_IO_3},		// 16 MC_E_POT_GT_GE_POT
		{BOARD_IO, PIN_RC1, REG_IO_3},		// 17 MC_E_POT_LSL_POTP
		{BOARD_IO, PIN_RC2, REG_IO_3},		// 18 MC_E_POT_LSL_POTN
		{BOARD_IO, PIN_RC3, REG_IO_3},		// 19 MC_G_LSL_G
		{BOARD_IO, PIN_RC4, REG_IO_3},		// 20 MC_C_POT_LSL_POTP
		{BOARD_IO, PIN_RC5, REG_IO_3},		// 21 MC_C_POT_LSL_POTN
		//
		// IO слоты 22..31 — резерв под финализацию матрицы Trello 7A6GZMVv.
		{BOARD_IO, PIN_RC6, REG_IO_3},		// 22 reserved
		{BOARD_IO, PIN_RC7, REG_IO_3},		// 23 reserved
		{BOARD_IO, PIN_RC0, REG_IO_4},		// 24 reserved
		{BOARD_IO, PIN_RC1, REG_IO_4},		// 25 reserved
		{BOARD_IO, PIN_RC2, REG_IO_4},		// 26 reserved
		{BOARD_IO, PIN_RC3, REG_IO_4},		// 27 reserved
		{BOARD_IO, PIN_RC4, REG_IO_4},		// 28 reserved
		{BOARD_IO, PIN_RC5, REG_IO_4},		// 29 reserved
		{BOARD_IO, PIN_RC6, REG_IO_4},		// 30 reserved
		{BOARD_IO, PIN_RC7, REG_IO_4},		// 31 reserved

		// ===== OutThermRelayBoard (BOARD_THERM, SS2) =====
		{BOARD_THERM, PIN_RC0, REG_THERM_1},	// 32 T1_PE
		{BOARD_THERM, PIN_RC1, REG_THERM_1},	// 33 T2_PE
		{BOARD_THERM, PIN_RC2, REG_THERM_1},	// 34 OL_T1_COMM
		{BOARD_THERM, PIN_RC3, REG_THERM_1},	// 35 OL_T2_COMM
		{BOARD_THERM, PIN_RC4, REG_THERM_1},	// 36 MC_T2_GT_G
		{BOARD_THERM, PIN_RC5, REG_THERM_1},	// 37 MC_T2_GT_G_POT
		{BOARD_THERM, PIN_RC6, REG_THERM_1},	// 38 MC_T1_GT_GE
		{BOARD_THERM, PIN_RC7, REG_THERM_1},	// 39 MC_T1_GT_GE_POT

		// ===== InputRelayBoard (BOARD_INPUT, SS1) =====
		{BOARD_INPUT, PIN_RC0, REG_INPUT_1},	// 40 ST_TI_GT_G
		{BOARD_INPUT, PIN_RC1, REG_INPUT_1},	// 41 ST_TO_GT_GE
		{BOARD_INPUT, PIN_RC2, REG_INPUT_1},	// 42 IL_GT_G_COMM
		{BOARD_INPUT, PIN_RC3, REG_INPUT_1},	// 43 IL_GT_GE_COMM
		{BOARD_INPUT, PIN_RC4, REG_INPUT_1},	// 44 IL_GT_G_GE
		{BOARD_INPUT, PIN_RC5, REG_INPUT_1},	// 45 ST_TI_GT_G_POT
		{BOARD_INPUT, PIN_RC6, REG_INPUT_1},	// 46 ST_TO_GT_GE_POT
		{BOARD_INPUT, PIN_RC7, REG_INPUT_1},	// 47 IL_GT_G_POT_COMM
		//
		{BOARD_INPUT, PIN_RC0, REG_INPUT_2},	// 48 IL_GT_GE_POT_COMM
		{BOARD_INPUT, PIN_RC1, REG_INPUT_2},	// 49 IL_GT_G_GE_POT
		{BOARD_INPUT, PIN_RC2, REG_INPUT_2},	// 50 ST_TI_LSL_G
		{BOARD_INPUT, PIN_RC3, REG_INPUT_2},	// 51 ST_TO_LSL_GE
		{BOARD_INPUT, PIN_RC4, REG_INPUT_2},	// 52 IL_LSL_G_COMM
		{BOARD_INPUT, PIN_RC5, REG_INPUT_2},	// 53 IL_LSL_GE_COMM
		{BOARD_INPUT, PIN_RC6, REG_INPUT_2},	// 54 IL_LSL_G_GE
		{BOARD_INPUT, PIN_RC7, REG_INPUT_2},	// 55 ST_TI_LSL_POTP
		//
		{BOARD_INPUT, PIN_RC0, REG_INPUT_3},	// 56 ST_TO_LSL_POTN
		{BOARD_INPUT, PIN_RC1, REG_INPUT_3},	// 57 IL_LSL_POTP_COMM
		{BOARD_INPUT, PIN_RC2, REG_INPUT_3},	// 58 IL_LSL_POTN_COMM
		{BOARD_INPUT, PIN_RC3, REG_INPUT_3},	// 59 IL_LSL_POTS
		{BOARD_INPUT, PIN_RC4, REG_INPUT_3},	// 60 reserved
		{BOARD_INPUT, PIN_RC5, REG_INPUT_3},	// 61 reserved
		{BOARD_INPUT, PIN_RC6, REG_INPUT_3},	// 62 reserved
		{BOARD_INPUT, PIN_RC7, REG_INPUT_3}		// 63 reserved
};
// No more
