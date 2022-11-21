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
#define PIN_D1	BIT0
#define PIN_D2	BIT1
#define PIN_D3	BIT2
#define PIN_D4	BIT3
#define	PIN_D5	BIT4
#define	PIN_D6	BIT5
#define	PIN_D7	BIT6
#define	PIN_D8	BIT7
//
#define PIN_E1	BIT0
#define PIN_E2	BIT1
#define PIN_E3	BIT2
#define PIN_E4	BIT3
#define	PIN_E5	BIT4
#define	PIN_E6	BIT5
#define	PIN_E7	BIT6
#define	PIN_E8	BIT7

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

// Constants
//

const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE] =
				{
						{BOARD1, PIN_A1},			// 0	// Gate (G) to PE
						{BOARD1, PIN_A2},			// 0	// Gate (G) to PE
						{BOARD1, PIN_A3},			// 0	// Gate (G) to PE
						{BOARD1, PIN_A4},			// 1	// Collector (C_POT) to PE
						{BOARD1, PIN_A5},			// 1	// Collector (C_POT) to PE
						{BOARD1, PIN_A6},			// 1	// Collector (C_POT) to PE
						{BOARD1, PIN_A7},			// 2	// Collector (C_POT) to LSL_POT-
						{BOARD1, PIN_A8},			// 3	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B1},			// 3	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B2},			// 3	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B3},			// 4	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_B4},			// 4	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_B5},			// 4	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_B6},			// 5	// Collector (C_POT) to LSL_POT+
						{BOARD1, PIN_B7},			// 6	// Gate (G) to GT_G_POT
						{BOARD1, PIN_B8},			// 7	// Gate (G) to GT_G
						{BOARD1, PIN_C1},			// 8	// Gate (G) to GT_GE
						{BOARD1, PIN_C2},			// 9	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C3},			// 9	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C4},			// 9	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C5},			// 10	// Gate (G) to LSL_G
						{BOARD1, PIN_C6},			// 11	// Gate-Emitter (GE) to GT_G
						{BOARD1, PIN_C7},			// 12	// Gate-Emitter (GE) to GT_GE
						{BOARD1, PIN_C8},			// 13	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_D1},			// 13	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_D2},			// 13	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_D3},			// 14	// Gate (G) to Gate-Emitter (GE)
						{BOARD1, PIN_D4},			// 15	// Gate-Emitter (GE) to LSL_GE
						{BOARD1, PIN_D5},			// 16	// Emitter (E_POT) to GT_GE_POT
						{BOARD1, PIN_D6},			// 17	// Emitter (E_POT) to LSL_POT+
						{BOARD1, PIN_D7},			// 18	// Emitter (E_POT) to LSL_POT-
						{BOARD1, PIN_D8},			// 19	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_E1},			// 19	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_E2},			// 19	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_E3},			// 20	// Emitter (E_POT) to PE
						{BOARD1, PIN_E4},			// 20	// Emitter (E_POT) to PE
						{BOARD1, PIN_E5},			// 20	// Emitter (E_POT) to PE
						{BOARD1, PIN_E6},			// 21	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_E7},			// 21	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_E8},			// 21	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_A1},			// 22	// Gate (G) to PE
						{BOARD2, PIN_A2},			// 22	// Gate (G) to PE
						{BOARD2, PIN_A3},			// 22	// Gate (G) to PE
						{BOARD2, PIN_A4},			// 23	// Collector (C_POT) to PE
						{BOARD2, PIN_A5},			// 23	// Collector (C_POT) to PE
						{BOARD2, PIN_A6},			// 23	// Collector (C_POT) to PE
						{BOARD2, PIN_A7},			// 24	// Collector (C_POT) to LSL_POT-
						{BOARD2, PIN_A8},			// 25	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B1},			// 25	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B2},			// 25	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B3},			// 26	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_B4},			// 26	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_B5},			// 26	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_B6},			// 27	// Collector (C_POT) to LSL_POT+
						{BOARD2, PIN_B7},			// 28	// Gate (G) to GT_G_POT
						{BOARD2, PIN_B8},			// 29	// Gate (G) to GT_G
						{BOARD2, PIN_C1},			// 30	// Gate (G) to GT_GE
						{BOARD2, PIN_C2},			// 31	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C3},			// 31	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C4},			// 31	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C5},			// 32	// Gate (G) to LSL_G
						{BOARD2, PIN_C6},			// 33	// Gate-Emitter (GE) to GT_G
						{BOARD2, PIN_C7},			// 34	// Gate-Emitter (GE) to GT_GE
						{BOARD2, PIN_C8},			// 35	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_D1},			// 35	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_D2},			// 35	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_D3},			// 36	// Gate (G) to Gate-Emitter (GE)
						{BOARD2, PIN_D4},			// 37	// Gate-Emitter (GE) to LSL_GE
						{BOARD2, PIN_D5},			// 38	// Emitter (E_POT) to GT_GE_POT
						{BOARD2, PIN_D6},			// 39	// Emitter (E_POT) to LSL_POT+
						{BOARD2, PIN_D7},			// 40	// Emitter (E_POT) to LSL_POT-
						{BOARD2, PIN_D8},			// 41	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_E1},			// 41	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_E2},			// 41	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_E3},			// 42	// Emitter (E_POT) to PE
						{BOARD2, PIN_E4},			// 42	// Emitter (E_POT) to PE
						{BOARD2, PIN_E5},			// 42	// Emitter (E_POT) to PE
						{BOARD2, PIN_E6},			// 43	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_E7},			// 43	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_E8},			// 43	// Gate-Emitter (GE) to PE
						{BOARD3, PIN_A1},			// 44	// Thermistor pin 2 (T2) to PE
						{BOARD3, PIN_A2},			// 44	// Thermistor pin 2 (T2) to PE
						{BOARD3, PIN_A3},			// 44	// Thermistor pin 2 (T2) to PE
						{BOARD3, PIN_A4},			// 45	// Thermistor pin 2 (T2) to GT_G_POT
						{BOARD3, PIN_A5},			// 46	// Thermistor pin 2 (T2) to GT_G
						{BOARD3, PIN_A6},			// 47	// Thermistor pin 2: Commutation of T2 (Open/Close)
						{BOARD3, PIN_A7},			// 47	// Thermistor pin 2: Commutation of T2 (Open/Close)
						{BOARD3, PIN_A8},			// 47	// Thermistor pin 2: Commutation of T2 (Open/Close)
						{BOARD3, PIN_B1},			// 48	// Thermistor pin 1 (T1) to GT_GE_POT
						{BOARD3, PIN_B2},			// 49	// Thermistor pin 1 (T1) to GT_GE
						{BOARD3, PIN_B3},			// 50	// Thermistor pin 1: Commutation of T1 (Open/Close)
						{BOARD3, PIN_B4},			// 50	// Thermistor pin 1: Commutation of T1 (Open/Close)
						{BOARD3, PIN_B5},			// 50	// Thermistor pin 1: Commutation of T1 (Open/Close)
						{BOARD3, PIN_B6},			// 51	// Thermistor pin 1 (T2) to PE
						{BOARD3, PIN_B7},			// 51	// Thermistor pin 1 (T2) to PE
						{BOARD3, PIN_B8},			// 51	// Thermistor pin 1 (T2) to PE
						{BOARD4, PIN_A1},			// 52	// Test-In (TI) to GT_G
						{BOARD4, PIN_A2},			// 53	// Test-Out (TO) to GT_GE
						{BOARD4, PIN_A3},			// 54	// GT_G: Commutation of GT_G (Open/Close)
						{BOARD4, PIN_A4},			// 55	// GT_GE: Commutation of GT_GE (Open/Close)
						{BOARD4, PIN_A5},			// 56	// GT_G to GT_GE
						{BOARD4, PIN_A6},			// 57	// Test-In (TI) to GT_G_POT
						{BOARD4, PIN_A7},			// 58	// Test-Out (TO) to GT_GE_POT
						{BOARD4, PIN_A8},			// 59	// GT_G_POT: Commutation of GT_G_POT (Open/Close)
						{BOARD4, PIN_B1},			// 60	// GT_GE_POT: Commutation of GT_GE_POT (Open/Close)
						{BOARD4, PIN_B2},			// 61	// GT_G_POT to GT_GE_POT
						{BOARD4, PIN_B3},			// 62	// Test-In (TI) to LSL_G
						{BOARD4, PIN_B4},			// 63	// Test-Out (TO) to LSL_GE
						{BOARD4, PIN_B5},			// 64	// LSL_G: Commutation of LSL_G (Open/Close)
						{BOARD4, PIN_B6},			// 65	// LSL_GE: Commutation of LSL_GE (Open/Close)
						{BOARD4, PIN_B7},			// 66	// LSL_G to LSL_GE
						{BOARD4, PIN_B8},			// 67	// Test-In (TI) to LSL_POT+
						{BOARD4, PIN_C1},			// 68	// Test-Out (TO) to LSL_POT-
						{BOARD4, PIN_C2},			// 69	// LSL_POT+: Commutation of LSL_POT+ (Open/Close)
						{BOARD4, PIN_C3},			// 70	// LSL_POT-: Commutation of LSL_POT- (Open/Close)
						{BOARD4, PIN_C4},			// 71	// LSL_POT+ to LSL_POT-
				};

// No more
