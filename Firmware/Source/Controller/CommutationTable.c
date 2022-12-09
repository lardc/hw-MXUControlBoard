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
						{BOARD1, PIN_A2},			// 1	// Gate (G) to PE
						{BOARD1, PIN_A3},			// 2	// Gate (G) to PE
						{BOARD1, PIN_A4},			// 3	// Collector (C_POT) to PE
						{BOARD1, PIN_A5},			// 4	// Collector (C_POT) to PE
						{BOARD1, PIN_A6},			// 5	// Collector (C_POT) to PE
						{BOARD1, PIN_A7},			// 6	// Collector (C_POT) to LSL_POT-
						{BOARD1, PIN_A8},			// 7	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B1},			// 8	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B2},			// 9	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B3},			// 10	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_B4},			// 11	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_B5},			// 12	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_B6},			// 13	// Collector (C_POT) to LSL_POT+
						{BOARD1, PIN_B7},			// 14	// Gate (G) to GT_G_POT
						{BOARD1, PIN_B8},			// 15	// Gate (G) to GT_G
						{BOARD1, PIN_C1},			// 16	// Gate (G) to GT_GE
						{BOARD1, PIN_C2},			// 17	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C3},			// 18	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C4},			// 19	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C5},			// 20	// Gate (G) to LSL_G
						{BOARD1, PIN_C6},			// 21	// Gate-Emitter (GE) to GT_G
						{BOARD1, PIN_C7},			// 22	// Gate-Emitter (GE) to GT_GE
						{BOARD1, PIN_C8},			// 23	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_D1},			// 24	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_D2},			// 25	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_D3},			// 26	// Gate (G) to Gate-Emitter (GE)
						{BOARD1, PIN_D4},			// 27	// Gate-Emitter (GE) to LSL_GE
						{BOARD1, PIN_D5},			// 28	// Emitter (E_POT) to GT_GE_POT
						{BOARD1, PIN_D6},			// 29	// Emitter (E_POT) to LSL_POT+
						{BOARD1, PIN_D7},			// 30	// Emitter (E_POT) to LSL_POT-
						{BOARD1, PIN_D8},			// 31	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_E1},			// 32	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_E2},			// 33	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_E3},			// 34	// Emitter (E_POT) to PE
						{BOARD1, PIN_E4},			// 35	// Emitter (E_POT) to PE
						{BOARD1, PIN_E5},			// 36	// Emitter (E_POT) to PE
						{BOARD1, PIN_E6},			// 37	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_E7},			// 38	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_E8},			// 39	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_A1},			// 40	// Gate (G) to PE
						{BOARD2, PIN_A2},			// 41	// Gate (G) to PE
						{BOARD2, PIN_A3},			// 42	// Gate (G) to PE
						{BOARD2, PIN_A4},			// 43	// Collector (C_POT) to PE
						{BOARD2, PIN_A5},			// 44	// Collector (C_POT) to PE
						{BOARD2, PIN_A6},			// 45	// Collector (C_POT) to PE
						{BOARD2, PIN_A7},			// 46	// Collector (C_POT) to LSL_POT-
						{BOARD2, PIN_A8},			// 47	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B1},			// 48	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B2},			// 49	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B3},			// 50	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_B4},			// 51	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_B5},			// 52	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_B6},			// 53	// Collector (C_POT) to LSL_POT+
						{BOARD2, PIN_B7},			// 54	// Gate (G) to GT_G_POT
						{BOARD2, PIN_B8},			// 55	// Gate (G) to GT_G
						{BOARD2, PIN_C1},			// 56	// Gate (G) to GT_GE
						{BOARD2, PIN_C2},			// 57	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C3},			// 58	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C4},			// 59	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C5},			// 60	// Gate (G) to LSL_G
						{BOARD2, PIN_C6},			// 61	// Gate-Emitter (GE) to GT_G
						{BOARD2, PIN_C7},			// 62	// Gate-Emitter (GE) to GT_GE
						{BOARD2, PIN_C8},			// 63	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_D1},			// 64	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_D2},			// 65	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_D3},			// 66	// Gate (G) to Gate-Emitter (GE)
						{BOARD2, PIN_D4},			// 67	// Gate-Emitter (GE) to LSL_GE
						{BOARD2, PIN_D5},			// 68	// Emitter (E_POT) to GT_GE_POT
						{BOARD2, PIN_D6},			// 69	// Emitter (E_POT) to LSL_POT+
						{BOARD2, PIN_D7},			// 70	// Emitter (E_POT) to LSL_POT-
						{BOARD2, PIN_D8},			// 71	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_E1},			// 72	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_E2},			// 73	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_E3},			// 74	// Emitter (E_POT) to PE
						{BOARD2, PIN_E4},			// 75	// Emitter (E_POT) to PE
						{BOARD2, PIN_E5},			// 76	// Emitter (E_POT) to PE
						{BOARD2, PIN_E6},			// 77	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_E7},			// 78	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_E8},			// 79	// Gate-Emitter (GE) to PE
						{BOARD3, PIN_A1},			// 80	// Thermistor pin 2 (T2) to PE
						{BOARD3, PIN_A2},			// 81	// Thermistor pin 2 (T2) to PE
						{BOARD3, PIN_A3},			// 82	// Thermistor pin 2 (T2) to PE
						{BOARD3, PIN_A4},			// 83	// Thermistor pin 2 (T2) to GT_G_POT
						{BOARD3, PIN_A5},			// 84	// Thermistor pin 2 (T2) to GT_G
						{BOARD3, PIN_A6},			// 85	// Thermistor pin 2: Commutation of T2 (Open/Close)
						{BOARD3, PIN_A7},			// 86	// Thermistor pin 2: Commutation of T2 (Open/Close)
						{BOARD3, PIN_A8},			// 87	// Thermistor pin 2: Commutation of T2 (Open/Close)
						{BOARD3, PIN_B1},			// 88	// Thermistor pin 1 (T1) to GT_GE_POT
						{BOARD3, PIN_B2},			// 89	// Thermistor pin 1 (T1) to GT_GE
						{BOARD3, PIN_B3},			// 90	// Thermistor pin 1: Commutation of T1 (Open/Close)
						{BOARD3, PIN_B4},			// 91	// Thermistor pin 1: Commutation of T1 (Open/Close)
						{BOARD3, PIN_B5},			// 92	// Thermistor pin 1: Commutation of T1 (Open/Close)
						{BOARD3, PIN_B6},			// 93	// Thermistor pin 1 (T2) to PE
						{BOARD3, PIN_B7},			// 94	// Thermistor pin 1 (T2) to PE
						{BOARD3, PIN_B8},			// 95	// Thermistor pin 1 (T2) to PE
						{BOARD4, PIN_A1},			// 96	// Test-In (TI) to GT_G
						{BOARD4, PIN_A2},			// 97	// Test-Out (TO) to GT_GE
						{BOARD4, PIN_A3},			// 98	// GT_G: Commutation of GT_G (Open/Close)
						{BOARD4, PIN_A4},			// 99	// GT_GE: Commutation of GT_GE (Open/Close)
						{BOARD4, PIN_A5},			// 100	// GT_G to GT_GE
						{BOARD4, PIN_A6},			// 101	// Test-In (TI) to GT_G_POT
						{BOARD4, PIN_A7},			// 102	// Test-Out (TO) to GT_GE_POT
						{BOARD4, PIN_A8},			// 103	// GT_G_POT: Commutation of GT_G_POT (Open/Close)
						{BOARD4, PIN_B1},			// 104	// GT_GE_POT: Commutation of GT_GE_POT (Open/Close)
						{BOARD4, PIN_B2},			// 105	// GT_G_POT to GT_GE_POT
						{BOARD4, PIN_B3},			// 106	// Test-In (TI) to LSL_G
						{BOARD4, PIN_B4},			// 107	// Test-Out (TO) to LSL_GE
						{BOARD4, PIN_B5},			// 108	// LSL_G: Commutation of LSL_G (Open/Close)
						{BOARD4, PIN_B6},			// 109	// LSL_GE: Commutation of LSL_GE (Open/Close)
						{BOARD4, PIN_B7},			// 110	// LSL_G to LSL_GE
						{BOARD4, PIN_B8},			// 111	// Test-In (TI) to LSL_POT+
						{BOARD4, PIN_C1},			// 112	// Test-Out (TO) to LSL_POT-
						{BOARD4, PIN_C2},			// 113	// LSL_POT+: Commutation of LSL_POT+ (Open/Close)
						{BOARD4, PIN_C3},			// 114	// LSL_POT-: Commutation of LSL_POT- (Open/Close)
						{BOARD4, PIN_C4},			// 115	// LSL_POT+ to LSL_POT-
				};

// No more
