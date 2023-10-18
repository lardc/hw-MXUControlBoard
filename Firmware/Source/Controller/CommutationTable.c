// -----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "CommutationTable.h"

// Output pins bindings
// PIN_XY -> where X = number of shift-register, Y = number of pin
#define PIN_A1	BIT0
#define PIN_A2	BIT1
#define PIN_A3	BIT2
#define PIN_A4	BIT3
#define	PIN_A5	BIT4
#define	PIN_A6	BIT5
#define	PIN_A7	BIT6
#define	PIN_A8	BIT7
//
#define PIN_B1	BIT0
#define PIN_B2	BIT1
#define PIN_B3	BIT2
#define PIN_B4	BIT3
#define	PIN_B5	BIT4
#define	PIN_B6	BIT5
#define	PIN_B7	BIT6
#define	PIN_B8	BIT7
//
#define PIN_C1	BIT0
#define PIN_C2	BIT1
#define PIN_C3	BIT2
#define PIN_C4	BIT3
#define	PIN_C5	BIT4
#define	PIN_C6	BIT5
#define	PIN_C7	BIT6
#define	PIN_C8	BIT7
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
						{BOARD1, PIN_A1, REG1},			// 0	// Collector (C_POT) to PE
						{BOARD1, PIN_A2, REG1},			// 1	// Gate (G) to PE
						{BOARD1, PIN_A3, REG1},			// 2	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_A4, REG1},			// 3	// Emitter (E_POT) to PE
						{BOARD1, PIN_A5, REG1},			// 4	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_A6, REG1},			// 5	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_A7, REG1},			// 6	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_A8, REG1},			// 7	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_B1, REG2},			// 8	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B2, REG2},			// 9	// Gate (G) to Gate-Emitter (GE)
						{BOARD1, PIN_B3, REG2},			// 10	// Gate-Emitter (GE) to GT_G
						{BOARD1, PIN_B4, REG2},			// 11	// Gate-Emitter (GE) to GT_GE
						{BOARD1, PIN_B5, REG2},			// 12	// Gate-Emitter (GE) to LSL_GE
						{BOARD1, PIN_B6, REG2},			// 13	// Gate (G) to GT_G
						{BOARD1, PIN_B7, REG2},			// 14	// Gate (G) to GT_GE
						{BOARD1, PIN_B8, REG2},			// 15	// Gate (G) to GT_G_POT
						{BOARD1, PIN_C1, REG3},			// 16	// Emitter (E_POT) to GT_GE_POT
						{BOARD1, PIN_C2, REG3},			// 17	// Emitter (E_POT) to LSL_POT+
						{BOARD1, PIN_C3, REG3},			// 18	// Emitter (E_POT) to LSL_POT-
						{BOARD1, PIN_C4, REG3},			// 19	// Gate (G) to LSL_G
						{BOARD1, PIN_C5, REG3},			// 20	// Collector (C_POT) to LSL_POT+
						{BOARD1, PIN_C6, REG3},			// 21	// Collector (C_POT) to LSL_POT-
						{BOARD1, PIN_C7, REG3},			// 22	//
						{BOARD1, PIN_C8, REG3},			// 23	//
						{BOARD2, PIN_A1, REG4},			// 24	// Collector (C_POT) to PE
						{BOARD2, PIN_A2, REG4},			// 25	// Gate (G) to PE
						{BOARD2, PIN_A3, REG4},			// 26	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_A4, REG4},			// 27	// Emitter (E_POT) to PE
						{BOARD2, PIN_A5, REG4},			// 28	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_A6, REG4},			// 29	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_A7, REG4},			// 30	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_A8, REG4},			// 31	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_B1, REG5},			// 32	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B2, REG5},			// 33	// Gate (G) to Gate-Emitter (GE)
						{BOARD2, PIN_B3, REG5},			// 34	// Gate-Emitter (GE) to GT_G
						{BOARD2, PIN_B4, REG5},			// 35	// Gate-Emitter (GE) to GT_GE
						{BOARD2, PIN_B5, REG5},			// 36	// Gate-Emitter (GE) to LSL_GE
						{BOARD2, PIN_B6, REG5},			// 37	// Gate (G) to GT_G
						{BOARD2, PIN_B7, REG5},			// 38	// Gate (G) to GT_GE
						{BOARD2, PIN_B8, REG5},			// 39	// Gate (G) to GT_G_POT
						{BOARD2, PIN_C1, REG6},			// 40	// Emitter (E_POT) to GT_GE_POT
						{BOARD2, PIN_C2, REG6},			// 41	// Emitter (E_POT) to LSL_POT+
						{BOARD2, PIN_C3, REG6},			// 42	// Emitter (E_POT) to LSL_POT-
						{BOARD2, PIN_C4, REG6},			// 43	// Gate (G) to LSL_G
						{BOARD2, PIN_C5, REG6},			// 44	// Collector (C_POT) to LSL_POT+
						{BOARD2, PIN_C6, REG6},			// 45	// Collector (C_POT) to LSL_POT-
						{BOARD2, PIN_C7, REG6},			// 46	//
						{BOARD2, PIN_C8, REG6},			// 47	//
						{BOARD3, PIN_A1, REG7},			// 48	// Thermistor_1 (T1) to PE
						{BOARD3, PIN_A2, REG7},			// 49	// Thermistor_2 (T2) to PE
						{BOARD3, PIN_A3, REG7},			// 50	// Thermistor_1: Commutation of T1 (Open/Close)
						{BOARD3, PIN_A4, REG7},			// 51	// Thermistor_2: Commutation of T2 (Open/Close)
						{BOARD3, PIN_A5, REG7},			// 52	// T2 to GT_G
						{BOARD3, PIN_A6, REG7},			// 53	// T2 to GT_G_POT
						{BOARD3, PIN_A7, REG7},			// 54	// T1 to GT_GE
						{BOARD3, PIN_A8, REG7},			// 55	// T1 to GT_GE_POT
						{BOARD4, PIN_A1, REG8},			// 136	// GT_G to TEST-IN
						{BOARD4, PIN_A2, REG8},			// 137	// GT_GE to TEST-OUT
						{BOARD4, PIN_A3, REG8},			// 138	// GT_G: Commutation of GT_G (Open/Close)
						{BOARD4, PIN_A4, REG8},			// 139	// GT_GE: Commutation of GT_GE (Open/Close)
						{BOARD4, PIN_A5, REG8},			// 140	// GT_G to GT_GE
						{BOARD4, PIN_A6, REG8},			// 141	// GT_G_POT to TEST-IN
						{BOARD4, PIN_A7, REG8},			// 142	// GT_GE_POT to TEST-OUT
						{BOARD4, PIN_A8, REG8},			// 143	// GT_G_POT: Commutation of GT_G_POT (Open/Close)
						{BOARD4, PIN_B1, REG9},			// 144	// GT_GE_POT: Commutation of GT_GE_POT (Open/Close)
						{BOARD4, PIN_B2, REG9},			// 145	// GT_G_POT to GT_GE_POT
						{BOARD4, PIN_B3, REG9},			// 146	// LSL_G to TEST-IN
						{BOARD4, PIN_B4, REG9},			// 147	// LSL_GE to TEST-OUT
						{BOARD4, PIN_B5, REG9},			// 148	// LSL_G: Commutation of LSL_G (Open/Close)
						{BOARD4, PIN_B6, REG9},			// 149	// LSL_GE: Commutation of LSL_GE (Open/Close)
						{BOARD4, PIN_B7, REG9},			// 150	// LSL_G to LSL_GE
						{BOARD4, PIN_B8, REG9},			// 151	// LSL_POT+ to TEST-IN
						{BOARD4, PIN_C1, REG10},		// 152	// LSL_POT- to TEST-OUT
						{BOARD4, PIN_C2, REG10},		// 153	// LSL_POT+: Commutation of LSL_POT+ (Open/Close)
						{BOARD4, PIN_C3, REG10},		// 154	// LSL_POT-: Commutation of LSL_POT- (Open/Close)
						{BOARD4, PIN_C4, REG10},		// 155	// LSL_POT+ to LSL_POT-
						{BOARD4, PIN_C5, REG10},		// 156	//
						{BOARD4, PIN_C6, REG10},		// 157	//
						{BOARD4, PIN_C7, REG10},		// 158	//
						{BOARD4, PIN_C8, REG10}			// 159	//
				};
// No more
