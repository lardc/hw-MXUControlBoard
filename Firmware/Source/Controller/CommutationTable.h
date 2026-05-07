// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"


// Constants
//
// MXU303: три физические платы за отдельными CS (SS1/SS2/SS3).
// IORelayBoard объединяет функционал прежних OutHVRelayBoard-1/2 в одной плате.
#define NUM_REGS_INPUT_BOARD	3	// InputRelayBoard — 3 сдвиговых регистра (24 бита) на SS1
#define NUM_REGS_THERM_BOARD	1	// OutThermRelayBoard — 1 сдвиговый регистр (8 бит) на SS2
#define NUM_REGS_IO_BOARD		4	// IORelayBoard — 4 сдвиговых регистра (32 бита) на SS3

#define NUM_REGS_TOTAL			(NUM_REGS_IO_BOARD + NUM_REGS_THERM_BOARD + NUM_REGS_INPUT_BOARD)

#define COMMUTATION_TABLE_SIZE	(NUM_REGS_TOTAL * 8)

//
// Commutation ID (индекс в CommutationTable[]).
// Распределение 64 слотов: 0..31 — IORelayBoard, 32..39 — OutThermRelayBoard,
// 40..63 — InputRelayBoard.
//
// ===== InputRelayBoard =====
#define GT_G_COMM				0	// BNC (wire) input gate
#define GT_GE_COMM				0	// BNC (shield) input control emmiter

// ===== IORelayBoard =====
// Main
#define GT_G_TO_G				0
#define GT_GE_TO_GE				0

// OutHVRelayBoard-1
#define EPOT_TO_EPOT1			0
#define GE_TO_GE1				0
#define G_TO_G1					0
#define EPOT_TO_CPOT1			0

#define GE1_TO_G1				0	// Through 1kOhm resitor

#define GND_TO_EPOT1			0
#define GND_TO_CPOT1			0

// OutHVRelayBoard-2
#define EPOT_TO_EPOT2			0
#define GE_TO_GE2				0
#define G_TO_G2					0
#define EPOT_TO_CPOT2			0

#define GE2_TO_G2				0	// Through 1kOhm resitor

#define GND_TO_EPOT2			0
#define GND_TO_CPOT2			0

// ===== OutThermRelayBoard =====



//Старые коммутации
// сигналы исходной 301-й прошивки и служат заглушкой до финализации матрицы.
// ===== IORelayBoard — DUT Position 1 =====
//
#define OL_C_POT_COMM			4	// Out lines self-commutation
#define OL_G_COMM				5
#define OL_GE_COMM				6
#define OL_E_POT_COMM			7
//
#define MC_G_C_POT				8	// Main Commutation — Position 1
#define MC_G_GE					9
#define MC_GE_GT_G				10
#define MC_GE_GT_GE				11
#define MC_GE_LSL_GE			12
#define MC_G_GT_G				13
#define MC_G_GT_GE				14
#define MC_G_GT_G_POT			15
#define MC_E_POT_GT_GE_POT		16
#define MC_E_POT_LSL_POTP		17
#define MC_E_POT_LSL_POTN		18
#define MC_G_LSL_G				19
#define MC_C_POT_LSL_POTP		20
#define MC_C_POT_LSL_POTN		21

// ===== IORelayBoard — DUT Position 2 =====
// TODO Trello 7A6GZMVv: уточнить распределение бит Position 2.
// Сейчас сигналы Position 2 aliased на одноимённые Position 1 — при коммутации
// Position 2 выполняется та же физическая коммутация, что и Position 1.
// Это сознательная заглушка; корректный вариант появится после финализации
// схемы IORelayBoard.
//
#define OL_C_POT_2_COMM			OL_C_POT_COMM
#define OL_G_2_COMM				OL_G_COMM
#define OL_GE_2_COMM			OL_GE_COMM
#define OL_E_POT_2_COMM			OL_E_POT_COMM
//
#define MC_G_2_C_POT			MC_G_C_POT
#define MC_G_2_GE				MC_G_GE
#define MC_GE_2_GT_G			MC_GE_GT_G
#define MC_GE_2_GT_GE			MC_GE_GT_GE
#define MC_GE_2_LSL_GE			MC_GE_LSL_GE
#define MC_G_2_GT_G				MC_G_GT_G
#define MC_G_2_GT_GE			MC_G_GT_GE
#define MC_G_2_GT_G_POT			MC_G_GT_G_POT
#define MC_E_POT_2_GT_GE_POT	MC_E_POT_GT_GE_POT
#define MC_E_POT_2_LSL_POTP		MC_E_POT_LSL_POTP
#define MC_E_POT_2_LSL_POTN		MC_E_POT_LSL_POTN
#define MC_G_2_LSL_G			MC_G_LSL_G
#define MC_C_POT_2_LSL_POTP		MC_C_POT_LSL_POTP
#define MC_C_POT_2_LSL_POTN		MC_C_POT_LSL_POTN

// ===== OutThermRelayBoard =====
#define OL_T1_COMM				34	// Thermistor_1: Commutation of T1 (Open/Close)
#define OL_T2_COMM				35	// Thermistor_2: Commutation of T2 (Open/Close)
#define MC_T2_GT_G				36	// T2 to GT_G
#define MC_T2_GT_G_POT			37	// T2 to GT_G_POT
#define MC_T1_GT_GE				38	// T1 to GT_GE
#define MC_T1_GT_GE_POT			39	// T1 to GT_GE_POT

// ===== InputRelayBoard =====
#define ST_TI_GT_G				40	// GT_G to TEST-IN
#define ST_TO_GT_GE				41	// GT_GE to TEST-OUT
#define IL_GT_G_COMM			42	// GT_G: Commutation of GT_G (Open/Close)
#define IL_GT_GE_COMM			43	// GT_GE: Commutation of GT_GE (Open/Close)
#define IL_GT_G_GE				44	// GT_G to GT_GE
#define ST_TI_GT_G_POT			45	// GT_G_POT to TEST-IN
#define ST_TO_GT_GE_POT			46	// GT_GE_POT to TEST-OUT
#define IL_GT_G_POT_COMM		47	// GT_G_POT: Commutation of GT_G_POT (Open/Close)
#define IL_GT_GE_POT_COMM		48	// GT_GE_POT: Commutation of GT_GE_POT (Open/Close)
#define IL_GT_G_GE_POT			49	// GT_G_POT to GT_GE_POT
#define ST_TI_LSL_G				50	// LSL_G to TEST-IN
#define ST_TO_LSL_GE			51	// LSL_GE to TEST-OUT
#define IL_LSL_G_COMM			52	// LSL_G: Commutation of LSL_G (Open/Close)
#define IL_LSL_GE_COMM			53	// LSL_GE: Commutation of LSL_GE (Open/Close)
#define IL_LSL_G_GE				54	// LSL_G to LSL_GE
#define ST_TI_LSL_POTP			55	// LSL_POT+ to TEST-IN
#define ST_TO_LSL_POTN			56	// LSL_POT- to TEST-OUT
#define IL_LSL_POTP_COMM		57	// LSL_POT+: Commutation of LSL_POT+ (Open/Close)
#define IL_LSL_POTN_COMM		58	// LSL_POT-: Commutation of LSL_POT- (Open/Close)
#define IL_LSL_POTS				59	// LSL_POT+ to LSL_POT-
//	Резервные слоты 60..63 для будущих сигналов InputRelayBoard.

#define CT_SAVE_TIMEOUT			1800000
// Types
//
typedef struct __CommutationTableItem
{
	Int8U BoardNum;
	Int8U Bit;
	Int8U RegNum;
} CommutationTableItem;


// Variables
//
extern Int32U CycleCounters[COMMUTATION_TABLE_SIZE];
extern const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE];

extern Int64U CT_SaveTimer;

#endif // __COMMTABLE_H
