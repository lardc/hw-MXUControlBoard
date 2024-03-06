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
//
#define PIN_RC8		BIT0
#define PIN_RC9		BIT1
#define PIN_RC10	BIT2
#define PIN_RC11	BIT3
#define	PIN_RC12	BIT4
#define	PIN_RC13	BIT5
#define	PIN_RC14	BIT6
#define	PIN_RC15	BIT7
//
#define PIN_RC16	BIT0
#define PIN_RC17	BIT1
#define PIN_RC18	BIT2
#define PIN_RC19	BIT3
#define	PIN_RC20	BIT4
#define	PIN_RC21	BIT5
#define	PIN_RC22	BIT6
#define	PIN_RC23	BIT7
//

// Extension board indexes
//---------------------------------
// Board 4 is the most distant extension board
// to the control board (in terms of cable length)
//---------------------------------
//
#define BOARD1	0		// OutHVRelayBoard 1
#define BOARD2	1		// OutHVRelayBoard 2
#define BOARD3	2		// OutThermRelayBoard
#define BOARD4	3		// InputRelayBoard

#define REG1	0
#define REG2	1
#define REG3	2
#define REG4	3
#define REG5	4
#define REG6	5
#define REG7	6
#define REG8	7
#define REG9	8
#define REG10	9

// Constants
//
const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE] =
				{
						{BOARD1, PIN_RC0, REG1},			// 0	// Collector (C_POT) to PE
						{BOARD1, PIN_RC1, REG1},			// 1	// Gate (G) to PE
						{BOARD1, PIN_RC2, REG1},			// 2	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_RC3, REG1},			// 3	// Emitter (E_POT) to PE
						{BOARD1, PIN_RC4, REG1},			// 4	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_RC5, REG1},			// 5	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_RC6, REG1},			// 6	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_RC7, REG1},			// 7	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_RC8, REG2},			// 8	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_RC9, REG2},			// 9	// Gate (G) to Gate-Emitter (GE)
						{BOARD1, PIN_RC10, REG2},			// 10	// Gate-Emitter (GE) to GT_G
						{BOARD1, PIN_RC11, REG2},			// 11	// Gate-Emitter (GE) to GT_GE
						{BOARD1, PIN_RC12, REG2},			// 12	// Gate-Emitter (GE) to LSL_GE
						{BOARD1, PIN_RC13, REG2},			// 13	// Gate (G) to GT_G
						{BOARD1, PIN_RC14, REG2},			// 14	// Gate (G) to GT_GE
						{BOARD1, PIN_RC15, REG2},			// 15	// Gate (G) to GT_G_POT
						{BOARD1, PIN_RC16, REG3},			// 16	// Emitter (E_POT) to GT_GE_POT
						{BOARD1, PIN_RC17, REG3},			// 17	// Emitter (E_POT) to LSL_POT+
						{BOARD1, PIN_RC18, REG3},			// 18	// Emitter (E_POT) to LSL_POT-
						{BOARD1, PIN_RC19, REG3},			// 19	// Gate (G) to LSL_G
						{BOARD1, PIN_RC20, REG3},			// 20	// Collector (C_POT) to LSL_POT+
						{BOARD1, PIN_RC21, REG3},			// 21	// Collector (C_POT) to LSL_POT-
						{BOARD1, PIN_RC22, REG3},			// 22	//
						{BOARD1, PIN_RC23, REG3},			// 23	//
						{BOARD2, PIN_RC0, REG4},			// 24	// Collector (C_POT) to PE
						{BOARD2, PIN_RC1, REG4},			// 25	// Gate (G) to PE
						{BOARD2, PIN_RC2, REG4},			// 26	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_RC3, REG4},			// 27	// Emitter (E_POT) to PE
						{BOARD2, PIN_RC4, REG4},			// 28	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_RC5, REG4},			// 29	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_RC6, REG4},			// 30	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_RC7, REG4},			// 31	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_RC8, REG5},			// 32	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_RC9, REG5},			// 33	// Gate (G) to Gate-Emitter (GE)
						{BOARD2, PIN_RC10, REG5},			// 34	// Gate-Emitter (GE) to GT_G
						{BOARD2, PIN_RC11, REG5},			// 35	// Gate-Emitter (GE) to GT_GE
						{BOARD2, PIN_RC12, REG5},			// 36	// Gate-Emitter (GE) to LSL_GE
						{BOARD2, PIN_RC13, REG5},			// 37	// Gate (G) to GT_G
						{BOARD2, PIN_RC14, REG5},			// 38	// Gate (G) to GT_GE
						{BOARD2, PIN_RC15, REG5},			// 39	// Gate (G) to GT_G_POT
						{BOARD2, PIN_RC16, REG6},			// 40	// Emitter (E_POT) to GT_GE_POT
						{BOARD2, PIN_RC17, REG6},			// 41	// Emitter (E_POT) to LSL_POT+
						{BOARD2, PIN_RC18, REG6},			// 42	// Emitter (E_POT) to LSL_POT-
						{BOARD2, PIN_RC19, REG6},			// 43	// Gate (G) to LSL_G
						{BOARD2, PIN_RC20, REG6},			// 44	// Collector (C_POT) to LSL_POT+
						{BOARD2, PIN_RC21, REG6},			// 45	// Collector (C_POT) to LSL_POT-
						{BOARD2, PIN_RC22, REG6},			// 46	//
						{BOARD2, PIN_RC23, REG6},			// 47	//
						{BOARD3, PIN_RC0, REG7},			// 48	// Thermistor_1 (T1) to PE
						{BOARD3, PIN_RC1, REG7},			// 49	// Thermistor_2 (T2) to PE
						{BOARD3, PIN_RC2, REG7},			// 50	// Thermistor_1: Commutation of T1 (Open/Close)
						{BOARD3, PIN_RC3, REG7},			// 51	// Thermistor_2: Commutation of T2 (Open/Close)
						{BOARD3, PIN_RC4, REG7},			// 52	// T2 to GT_G
						{BOARD3, PIN_RC5, REG7},			// 53	// T2 to GT_G_POT
						{BOARD3, PIN_RC6, REG7},			// 54	// T1 to GT_GE
						{BOARD3, PIN_RC7, REG7},			// 55	// T1 to GT_GE_POT
						{BOARD4, PIN_RC0, REG8},			// 56	// GT_G to TEST-IN
						{BOARD4, PIN_RC1, REG8},			// 57	// GT_GE to TEST-OUT
						{BOARD4, PIN_RC2, REG8},			// 58	// GT_G: Commutation of GT_G (Open/Close)
						{BOARD4, PIN_RC3, REG8},			// 59	// GT_GE: Commutation of GT_GE (Open/Close)
						{BOARD4, PIN_RC4, REG8},			// 60	// GT_G to GT_GE
						{BOARD4, PIN_RC5, REG8},			// 61	// GT_G_POT to TEST-IN
						{BOARD4, PIN_RC6, REG8},			// 62	// GT_GE_POT to TEST-OUT
						{BOARD4, PIN_RC7, REG8},			// 63	// GT_G_POT: Commutation of GT_G_POT (Open/Close)
						{BOARD4, PIN_RC8, REG9},			// 64	// GT_GE_POT: Commutation of GT_GE_POT (Open/Close)
						{BOARD4, PIN_RC9, REG9},			// 65	// GT_G_POT to GT_GE_POT
						{BOARD4, PIN_RC10, REG9},			// 66	// LSL_G to TEST-IN
						{BOARD4, PIN_RC11, REG9},			// 67	// LSL_GE to TEST-OUT
						{BOARD4, PIN_RC12, REG9},			// 68	// LSL_G: Commutation of LSL_G (Open/Close)
						{BOARD4, PIN_RC13, REG9},			// 69	// LSL_GE: Commutation of LSL_GE (Open/Close)
						{BOARD4, PIN_RC14, REG9},			// 70	// LSL_G to LSL_GE
						{BOARD4, PIN_RC15, REG9},			// 71	// LSL_POT+ to TEST-IN
						{BOARD4, PIN_RC16, REG10},			// 72	// LSL_POT- to TEST-OUT
						{BOARD4, PIN_RC17, REG10},			// 73	// LSL_POT+: Commutation of LSL_POT+ (Open/Close)
						{BOARD4, PIN_RC18, REG10},			// 74	// LSL_POT-: Commutation of LSL_POT- (Open/Close)
						{BOARD4, PIN_RC19, REG10},			// 75	// LSL_POT+ to LSL_POT-
						{BOARD4, PIN_RC20, REG10},			// 76	//
						{BOARD4, PIN_RC21, REG10},			// 77	//
						{BOARD4, PIN_RC22, REG10},			// 78	//
						{BOARD4, PIN_RC23, REG10}			// 79	//
				};
// No more
