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
#define GT_G_COMM				0 // Затвор
#define GT_GE_COMM				0 // Эмиттер управления
#define GT_GPOT_COMM			0 // Потенциальный затвор
#define GT_GEPOT_COMM			0 // Потенциальный эмиттер управления

#define SV_G_COMM				0 // Затвор
#define SV_GE_COMM				0 // Эмиттер Управления
#define SV_POT_POS_COMM			0 // Потенциальный +
#define SV_POT_NEG_COMM			0 // Потенциальный -

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
#define GT_G_T2						0
#define GT_G_AND_GT_GPOT_TO_T2		0
#define GT_GPOT_TO_GT_G_T2			0
#define GT_GE_T1					0
#define GT_GE_AND_GT_GEPOT_TO_T1	0
#define GT_GEPOT_TO_GT_GE_T1		0

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
