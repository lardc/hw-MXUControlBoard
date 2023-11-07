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

#define NUM_REGS_HV_BOARD			7
#define NUM_REGS_THERM_BOARD		3
#define NUM_REGS_INPUT_BOARD		3
#define NUM_REGS_TOTAL ((NUM_REGS_HV_BOARD * 2) + NUM_REGS_THERM_BOARD + NUM_REGS_INPUT_BOARD)

#define COMMUTATION_TABLE_SIZE (((NUM_REGS_HV_BOARD * NUM_HV_BOARD) + NUM_REGS_THERM_BOARD + NUM_REGS_INPUT_BOARD) * 8)

//
// Commutation
// Out lines to PE Commutation
#define G_PE_1					1
#define G_PE_2					25
#define GE_PE_1					2
#define GE_PE_2					26
#define C_POT_PE_1				0
#define C_POT_PE_2				24
#define E_POT_PE_1				3
#define E_POT_PE_2				27
#define T_PE_1					48
#define T_PE_2					49
//
// Out Lines Self-Commutation
#define OL_C_POT_COMM_1			4
#define OL_C_POT_COMM_2			28
#define OL_G_COMM_1				5
#define OL_G_COMM_2				29
#define OL_GE_COMM_1			6
#define OL_GE_COMM_2			30
#define OL_E_POT_COMM_1			7
#define OL_E_POT_COMM_2			31
#define OL_T_COMM_1				50
#define OL_T_COMM_2				51

//
// In Lines Self-Commutation
#define IL_GT_G_COMM			138
#define IL_GT_GE_COMM			139
#define IL_GT_G_POT_COMM		143
#define IL_GT_GE_POT_COMM		144
#define IL_LSL_G_COMM			148
#define IL_LSL_GE_COMM			149
#define IL_LSL_POTP_COMM		153
#define IL_LSL_POTN_COMM		154

//
// Self-Test Commutation
#define ST_TI_GT_G				136
#define ST_TI_GT_G_POT			141
#define ST_TI_LSL_G				146
#define ST_TI_LSL_POTP			151
#define ST_TO_GT_GE				137
#define ST_TO_GT_GE_POT			142
#define ST_TO_LSL_GE			147
#define ST_TO_LSL_POTN			152
//
// In Lines Commutation
#define IL_GT_G_GE				140
#define IL_GT_G_GE_POT			145
#define IL_LSL_G_GE				150
#define IL_LSL_POTS				155
//
// Main Commutation
#define MC_C_POT_LSL_POTN_1		21
#define MC_C_POT_LSL_POTN_2		45
#define MC_G_C_POT_1			8
#define MC_G_C_POT_2			32
#define MC_C_POT_LSL_POTP_1		20
#define MC_C_POT_LSL_POTP_2		44
#define MC_G_GT_G_POT_1			15
#define MC_G_GT_G_POT_2			39
#define MC_G_GT_G_1				13
#define MC_G_GT_G_2				37
#define MC_G_GT_GE_1			14
#define MC_G_GT_GE_2			38
#define MC_G_LSL_G_1			19
#define MC_G_LSL_G_2			43
#define MC_GE_GT_G_1			10
#define MC_GE_GT_G_2			34
#define MC_GE_GT_GE_1			11
#define MC_GE_GT_GE_2			35
#define MC_G_GE_1				9
#define MC_G_GE_2				33
#define MC_GE_LSL_GE_1			12
#define MC_GE_LSL_GE_2			36
#define MC_E_POT_GT_GE_POT_1	16
#define MC_E_POT_GT_GE_POT_2	40
#define MC_E_POT_LSL_POTP_1		17
#define MC_E_POT_LSL_POTP_2		41
#define MC_E_POT_LSL_POTN_1		18
#define MC_E_POT_LSL_POTN_2		42
#define MC_T_GT_GE_POT_1		55
#define MC_T_GT_GE_1			54
#define MC_T_GT_G_POT_2			53
#define MC_T_GT_G_2				52



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
extern const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE];


#endif // __COMMTABLE_H
