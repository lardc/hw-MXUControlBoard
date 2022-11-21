// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"


// Constants
//
#define COMMUTATION_EXT_BOARDS	4
#define COMMUTATION_TABLE_SIZE	((COMMUTATION_EXT_BOARDS * 16) + 52)

//
// Commutation
// Out lines to PE Commutation
#define G_PE					0
#define C_POT_PE				1
#define E_POT_PE				20
#define GE_PE					21
#define G_2_PE					22
#define C_POT_2_PE				23
#define E_POT_2_PE				42
#define GE_2_PE					43
#define T2_PE					44
#define T1_PE					51
//
// Out Lines Self-Commutation
#define OL_C_POT_COMM			4
#define OL_G_COMM				9
#define OL_GE_COMM				13
#define OL_E_POT_COMM			19
#define OL_C_POT_2_COMM			26
#define OL_G_2_COMM				31
#define OL_GE_2_COMM			35
#define OL_E_POT_2_COMM			41
#define OL_T2_COMM				47
#define OL_T1_COMM				50
//
// In Lines Self-Commutation
#define IL_GT_G_COMM			54
#define IL_GT_GE_COMM			55
#define IL_GT_G_POT_COMM		59
#define IL_GT_GE_POT_COMM		60
#define IL_LSL_G_COMM			64
#define IL_LSL_GE_COMM			65
#define IL_LSL_POTP_COMM		69
#define IL_LSL_POTN_COMM		70

//
// Self-Test Commutation
#define ST_TI_GT_G				52
#define ST_TI_GT_G_POT			57
#define ST_TI_LSL_G				62
#define ST_TI_LSL_POTP			67
#define ST_TO_GT_GE				53
#define ST_TO_GT_GE_POT			58
#define ST_TO_LSL_GE			63
#define ST_TO_LSL_POTN			68
//
// In Lines Commutation
#define IL_GT_G_GE				56
#define IL_GT_G_GE_POT			61
#define IL_LSL_G_GE				66
#define IL_LSL_POTS				71
//
// Main Commutation
#define MC_C_POT_LSL_POTN		2
#define MC_G_C_POT				3
#define MC_C_POT_LSL_POTP		5
#define MC_G_GT_G_POT			6
#define MC_G_GT_G				7
#define MC_G_GT_GE				8
#define MC_G_LSL_G				10
#define MC_GE_GT_G				11
#define MC_GE_GT_GE				12
#define MC_G_GE					14
#define MC_GE_LSL_GE			15
#define MC_E_POT_GT_GE_POT		16
#define MC_E_POT_LSL_POTP		17
#define MC_E_POT_LSL_POTN		18
#define MC_C_POT_2_LSL_POTN		24
#define MC_G_2_C_POT			25
#define MC_C_POT_2_LSL_POTP		27
#define MC_G_2_GT_G_POT			28
#define MC_G_2_GT_G				29
#define MC_G_2_GT_GE			30
#define MC_G_2_LSL_G			32
#define MC_GE_2_GT_G			33
#define MC_GE_2_GT_GE			34
#define MC_G_2_GE				36
#define MC_GE_2_LSL_GE			37
#define MC_E_POT_2_GT_GE_POT	38
#define MC_E_POT_2_LSL_POTP		39
#define MC_E_POT_2_LSL_POTN		40
#define MC_T2_GT_G_POT			45
#define MC_T2_GT_G				46
#define MC_T1_GT_GE_POT			48
#define MC_T1_GT_GE				49
//

// Types
//
typedef struct __CommutationTableItem
{
	Int16U BoardNum;
	Int16U Bit;
} CommutationTableItem;


// Variables
//
extern const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE];


#endif // __COMMTABLE_H
