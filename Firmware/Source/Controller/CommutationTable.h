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
#define G_PE1					0
#define G_PE2					1
#define G_PE3					2
#define C_POT_PE1				1
#define C_POT_PE2				2
#define C_POT_PE3				3
#define E_POT_PE1				34
#define E_POT_PE2				35
#define E_POT_PE3				36
#define GE_PE1					37
#define GE_PE2					38
#define GE_PE3					39
#define G_2_PE1					40
#define G_2_PE2					41
#define G_2_PE3					42
#define C_POT_2_PE1				43
#define C_POT_2_PE2				44
#define C_POT_2_PE3				45
#define E_POT_2_PE1				74
#define E_POT_2_PE2				75
#define E_POT_2_PE3				76
#define GE_2_PE1				77
#define GE_2_PE2				78
#define GE_2_PE3				79
#define T2_PE1					80
#define T2_PE2					81
#define T2_PE3					82
#define T1_PE1					93
#define T1_PE2					94
#define T1_PE3					95
//
// Out Lines Self-Commutation
#define OL_C_POT_COMM1			10
#define OL_C_POT_COMM2			11
#define OL_C_POT_COMM3			12

#define OL_G_COMM1				17
#define OL_G_COMM2				18
#define OL_G_COMM3				19

#define OL_GE_COMM1				23
#define OL_GE_COMM2				24
#define OL_GE_COMM3				25

#define OL_E_POT_COMM1			31
#define OL_E_POT_COMM2			32
#define OL_E_POT_COMM3			33

#define OL_C_POT_2_COMM1		50
#define OL_C_POT_2_COMM2		51
#define OL_C_POT_2_COMM3		52

#define OL_G_2_COMM1			57
#define OL_G_2_COMM2			58
#define OL_G_2_COMM3			59

#define OL_GE_2_COMM1			63
#define OL_GE_2_COMM2			64
#define OL_GE_2_COMM3			65

#define OL_E_POT_2_COMM1		71
#define OL_E_POT_2_COMM2		72
#define OL_E_POT_2_COMM3		73

#define OL_T2_COMM1				85
#define OL_T2_COMM2				86
#define OL_T2_COMM3				87

#define OL_T1_COMM1				90
#define OL_T1_COMM2				91
#define OL_T1_COMM3				92
//
// In Lines Self-Commutation
#define IL_GT_G_COMM			98
#define IL_GT_GE_COMM			99
#define IL_GT_G_POT_COMM		103
#define IL_GT_GE_POT_COMM		104
#define IL_LSL_G_COMM			108
#define IL_LSL_GE_COMM			109
#define IL_LSL_POTP_COMM		113
#define IL_LSL_POTN_COMM		114

//
// Self-Test Commutation
#define ST_TI_GT_G				96
#define ST_TI_GT_G_POT			101
#define ST_TI_LSL_G				106
#define ST_TI_LSL_POTP			111
#define ST_TO_GT_GE				97
#define ST_TO_GT_GE_POT			102
#define ST_TO_LSL_GE			107
#define ST_TO_LSL_POTN			112
//
// In Lines Commutation
#define IL_GT_G_GE				100
#define IL_GT_G_GE_POT			105
#define IL_LSL_G_GE				110
#define IL_LSL_POTS				115
//
// Main Commutation
#define MC_C_POT_LSL_POTN		6
#define MC_G_C_POT1				7
#define MC_G_C_POT2				8
#define MC_G_C_POT3				9
#define MC_C_POT_LSL_POTP		13
#define MC_G_GT_G_POT			14
#define MC_G_GT_G				15
#define MC_G_GT_GE				16
#define MC_G_LSL_G				20
#define MC_GE_GT_G				21
#define MC_GE_GT_GE				22
#define MC_G_GE					26
#define MC_GE_LSL_GE			27
#define MC_E_POT_GT_GE_POT		28
#define MC_E_POT_LSL_POTP		29
#define MC_E_POT_LSL_POTN		30
#define MC_C_POT_2_LSL_POTN		46
#define MC_G_2_C_POT1			47
#define MC_G_2_C_POT2			48
#define MC_G_2_C_POT3			49
#define MC_C_POT_2_LSL_POTP		53
#define MC_G_2_GT_G_POT			54
#define MC_G_2_GT_G				55
#define MC_G_2_GT_GE			56
#define MC_G_2_LSL_G			60
#define MC_GE_2_GT_G			61
#define MC_GE_2_GT_GE			62
#define MC_G_2_GE				66
#define MC_GE_2_LSL_GE			67
#define MC_E_POT_2_GT_GE_POT	68
#define MC_E_POT_2_LSL_POTP		69
#define MC_E_POT_2_LSL_POTN		70
#define MC_T2_GT_G_POT			83
#define MC_T2_GT_G				84
#define MC_T1_GT_GE_POT			88
#define MC_T1_GT_GE				89
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
