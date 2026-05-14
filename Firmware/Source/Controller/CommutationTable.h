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
#define GT_G_COMM				0
#define GT_GE_COMM				0
#define GT_GPOT_COMM			0
#define GT_GEPOT_COMM			0

#define SV_G_COMM				0
#define SV_GE_COMM				0
#define SV_POT_POS_COMM			0
#define SV_POT_NEG_COMM			0

// ===== IORelayBoard =====
// Main
#define GT_G_TO_G				0
#define GT_GE_TO_GE				0
#define GT_G_TO_GE				0
#define GT_GE_TO_G				0
#define GT_GEPOT_TO_EPOT		0
#define GT_GPOT_TO_G			0
#define	G_TO_CPOT				0

#define SV_G_TO_G				0
#define SV_GE_TO_GE				0
#define SV_POT_POS_TO_CPOT		0
#define SV_POT_POS_TO_EPOT		0
#define SV_POT_NEG_TO_CPOT		0
#define SV_POT_NEG_TO_EPOT		0

// OutHVRelayBoard-1
#define GE_TO_GE1				0
#define G_TO_G1					0
#define EPOT_TO_EPOT1			0
#define EPOT_TO_CPOT1			0
#define CPOT_TO_CPOT1			0

#define GE1_TO_G1				0	// Through 1kOhm resitor

#define GND_TO_EPOT1			0
#define GND_TO_CPOT1			0

// OutHVRelayBoard-2
#define GE_TO_GE2				0
#define G_TO_G2					0
#define EPOT_TO_EPOT2			0
#define EPOT_TO_CPOT2			0
#define CPOT_TO_EPOT2			0
#define CPOT_TO_CPOT2			0

#define GE2_TO_G2				0	// Through 1kOhm resitor

#define GND_TO_EPOT2			0
#define GND_TO_CPOT2			0

// ===== OutThermRelayBoard =====



//Старые коммутации
// сигналы исходной 301-й прошивки и служат заглушкой до финализации матрицы.

// ===== OutThermRelayBoard =====
#define OL_T1_COMM				34	// Thermistor_1: Commutation of T1 (Open/Close)
#define OL_T2_COMM				35	// Thermistor_2: Commutation of T2 (Open/Close)
#define MC_T2_GT_G				36	// T2 to GT_G
#define MC_T2_GT_G_POT			37	// T2 to GT_G_POT
#define MC_T1_GT_GE				38	// T1 to GT_GE
#define MC_T1_GT_GE_POT			39	// T1 to GT_GE_POT

// ===== InputRelayBoard =====
#define IL_GT_G_COMM			42	// GT_G: Commutation of GT_G (Open/Close)
#define IL_GT_GE_COMM			43	// GT_GE: Commutation of GT_GE (Open/Close)
#define IL_GT_G_POT_COMM		47	// GT_G_POT: Commutation of GT_G_POT (Open/Close)
#define IL_GT_GE_POT_COMM		48	// GT_GE_POT: Commutation of GT_GE_POT (Open/Close)

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
