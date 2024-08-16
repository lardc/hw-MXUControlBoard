// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"


// Constants
//
#define NUM_HV_BOARD			2
#define NUM_THERM_BOARD			1
#define NUM_INPUT_BOARD			1
#define COMMUTATION_EXT_BOARDS	(NUM_HV_BOARD + NUM_THERM_BOARD + NUM_INPUT_BOARD)

#define NUM_REGS_HV_BOARD			3
#define NUM_REGS_THERM_BOARD		1
#define NUM_REGS_INPUT_BOARD		3
#define NUM_REGS_TOTAL ((NUM_REGS_HV_BOARD * 2) + NUM_REGS_THERM_BOARD + NUM_REGS_INPUT_BOARD)

#define COMMUTATION_TABLE_SIZE (((NUM_REGS_HV_BOARD * NUM_HV_BOARD) + NUM_REGS_THERM_BOARD + NUM_REGS_INPUT_BOARD) * 8)

//
// Commutation
// Out lines to PE Commutation
#define G_PE					1
#define C_POT_PE				0
#define E_POT_PE				3
#define GE_PE					2
#define G_2_PE					25
#define C_POT_2_PE				24
#define E_POT_2_PE				27
#define GE_2_PE					26
#define T2_PE					49
#define T1_PE					48
//
// Out Lines Self-Commutation
#define OL_C_POT_COMM			4
#define OL_G_COMM				5
#define OL_GE_COMM				6
#define OL_E_POT_COMM			7
#define OL_C_POT_2_COMM			28
#define OL_G_2_COMM				29
#define OL_GE_2_COMM			30
#define OL_E_POT_2_COMM			31
#define OL_T2_COMM				51
#define OL_T1_COMM				50
//
// In Lines Self-Commutation
#define IL_GT_G_COMM			58
#define IL_GT_GE_COMM			59
#define IL_GT_G_POT_COMM		63
#define IL_GT_GE_POT_COMM		64
#define IL_LSL_G_COMM			68
#define IL_LSL_GE_COMM			69
#define IL_LSL_POTP_COMM		73
#define IL_LSL_POTN_COMM		74

//
// Self-Test Commutation
#define ST_TI_GT_G				56
#define ST_TI_GT_G_POT			61
#define ST_TI_LSL_G				66
#define ST_TI_LSL_POTP			71
#define ST_TO_GT_GE				57
#define ST_TO_GT_GE_POT			62
#define ST_TO_LSL_GE			67
#define ST_TO_LSL_POTN			72
//
// In Lines Commutation
#define IL_GT_G_GE				60
#define IL_GT_G_GE_POT			65
#define IL_LSL_G_GE				70
#define IL_LSL_POTS				75
//
// Main Commutation
#define MC_C_POT_LSL_POTN		21
#define MC_G_C_POT				8
#define MC_C_POT_LSL_POTP		20
#define MC_G_GT_G_POT			15
#define MC_G_GT_G				13
#define MC_G_GT_GE				14
#define MC_G_LSL_G				19
#define MC_GE_GT_G				10
#define MC_GE_GT_GE				11
#define MC_G_GE					9
#define MC_GE_LSL_GE			12
#define MC_E_POT_GT_GE_POT		16
#define MC_E_POT_LSL_POTP		17
#define MC_E_POT_LSL_POTN		18
#define MC_C_POT_2_LSL_POTN		45
#define MC_G_2_C_POT			32
#define MC_C_POT_2_LSL_POTP		44
#define MC_G_2_GT_G_POT			39
#define MC_G_2_GT_G				37
#define MC_G_2_GT_GE			38
#define MC_G_2_LSL_G			43
#define MC_GE_2_GT_G			34
#define MC_GE_2_GT_GE			35
#define MC_G_2_GE				33
#define MC_GE_2_LSL_GE			36
#define MC_E_POT_2_GT_GE_POT	40
#define MC_E_POT_2_LSL_POTP		41
#define MC_E_POT_2_LSL_POTN		42
#define MC_T2_GT_G_POT			53
#define MC_T2_GT_G				52
#define MC_T1_GT_GE_POT			55
#define MC_T1_GT_GE				54

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
