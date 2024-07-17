// Header
//
#include "SelfTestRelaysArrays.h"

// Arrays
//
const SelfTestTableItem SelfTestInputBoard[ST_INPUT_BOARD_COMM] =
{
		{ST_STAGE0, ST_TI_GT_G, RT_NormalOpened},				// 0
		{ST_STAGE0, IL_GT_G_COMM, RT_NormalOpened},				// 1
		{ST_STAGE0, IL_GT_GE_COMM, RT_NormalOpened},			// 2
		{ST_STAGE0, IL_GT_G_GE, RT_NormalOpened},				// 3
		{ST_STAGE0, ST_TO_GT_GE, RT_NormalOpened},				// 4
		//
		{ST_STAGE1, IL_GT_G_POT_COMM, RT_NormalOpened},			// 5
		{ST_STAGE1, IL_GT_GE_POT_COMM, RT_NormalOpened},		// 6
		{ST_STAGE1, ST_TI_GT_G_POT, RT_NormalOpened},			// 7
		{ST_STAGE1, ST_TO_GT_GE_POT, RT_NormalOpened},			// 8
		{ST_STAGE1, IL_GT_G_GE_POT, RT_NormalOpened},			// 9
		//
		{ST_STAGE2, IL_LSL_G_COMM, RT_NormalOpened},			// 10
		{ST_STAGE2, IL_LSL_GE_COMM, RT_NormalOpened},			// 11
		{ST_STAGE2, ST_TI_LSL_G, RT_NormalOpened},				// 12
		{ST_STAGE2, ST_TO_LSL_GE, RT_NormalOpened},				// 13
		{ST_STAGE2, IL_LSL_G_GE, RT_NormalOpened},				// 14
		//
		{ST_STAGE3, IL_LSL_POTP_COMM, RT_NormalOpened},			// 15
		{ST_STAGE3, IL_LSL_POTN_COMM, RT_NormalOpened},			// 16
		{ST_STAGE3, ST_TI_LSL_POTP, RT_NormalOpened},			// 17
		{ST_STAGE3, ST_TO_LSL_POTN, RT_NormalOpened},			// 18
		{ST_STAGE3, IL_LSL_POTS, RT_NormalOpened},				// 19
};
//------------------------

const SelfTestTableItem SelfTestThermBoard[ST_THERM_BOARD_COMM] =
{
		{ST_STAGE0, OL_T1_COMM, RT_NormalOpened},				// 0
		{ST_STAGE0, OL_T2_COMM, RT_NormalOpened},				// 1
		{ST_STAGE0, T1_PE, RT_NormalClosed},					// 2
		{ST_STAGE0, T2_PE, RT_NormalClosed},					// 3
		{ST_STAGE0, MC_T2_GT_G, RT_NormalOpened},				// 4
		{ST_STAGE0, MC_T1_GT_GE, RT_NormalOpened},				// 5
		{ST_STAGE0, ST_TI_GT_G, RT_NormalOpened},				// 6
		{ST_STAGE0, ST_TO_GT_GE, RT_NormalOpened},				// 7

		{ST_STAGE1, OL_T1_COMM, RT_NormalOpened},				// 8
		{ST_STAGE1, OL_T2_COMM, RT_NormalOpened},				// 9
		{ST_STAGE1, T1_PE, RT_NormalClosed},					// 10
		{ST_STAGE1, T2_PE, RT_NormalClosed},					// 11
		{ST_STAGE1, MC_T2_GT_G_POT, RT_NormalOpened},			// 12
		{ST_STAGE1, MC_T1_GT_GE_POT, RT_NormalOpened},			// 13
		{ST_STAGE1, ST_TI_GT_G_POT, RT_NormalOpened},			// 14
		{ST_STAGE1, ST_TO_GT_GE_POT, RT_NormalOpened},			// 15
};
//------------------------

const SelfTestTableItem SelfTestHV1Board[ST_HV_BOARD_COMM] =
{
		{ST_STAGE0, E_POT_PE, RT_NormalClosed},					// 0
		{ST_STAGE0, GE_PE, RT_NormalClosed},					// 1
		{ST_STAGE0, OL_E_POT_COMM, RT_NormalOpened},			// 2
		{ST_STAGE0, OL_GE_COMM, RT_NormalOpened},				// 3
		{ST_STAGE0, MC_G_C_POT, RT_NormalOpened},				// 4
		{ST_STAGE0, MC_GE_GT_GE, RT_NormalOpened},				// 5
		{ST_STAGE0, MC_G_LSL_G, RT_NormalOpened},				// 6
		{ST_STAGE0, MC_E_POT_LSL_POTN, RT_NormalOpened},		// 7
		{ST_STAGE0, MC_C_POT_LSL_POTN, RT_NormalOpened},		// 8
		{ST_STAGE0, ST_TI_GT_G, RT_NormalOpened},				// 9
		{ST_STAGE0, ST_TO_LSL_GE, RT_NormalOpened},				// 10
		{ST_STAGE0, IL_GT_G_COMM, RT_NormalOpened},				// 11
		{ST_STAGE0, IL_GT_GE_COMM, RT_NormalOpened},			// 12
		{ST_STAGE0, IL_LSL_G_COMM, RT_NormalOpened},			// 13
		{ST_STAGE0, IL_LSL_GE_COMM, RT_NormalOpened},			// 14
		{ST_STAGE0, IL_GT_G_GE, RT_NormalOpened},				// 15
		{ST_STAGE0, IL_LSL_G_GE, RT_NormalOpened},				// 16
		//
		{ST_STAGE1, MC_E_POT_GT_GE_POT, RT_NormalOpened},		// 17
		{ST_STAGE1, MC_E_POT_LSL_POTP, RT_NormalOpened},		// 18
		{ST_STAGE1, OL_GE_COMM, RT_NormalOpened},				// 19
		{ST_STAGE1, MC_GE_GT_G, RT_NormalOpened},				// 20
		{ST_STAGE1, MC_G_GE, RT_NormalOpened},					// 21
		{ST_STAGE1, MC_G_GT_G, RT_NormalOpened},				// 22
		{ST_STAGE1, MC_G_GT_GE, RT_NormalOpened},				// 23
		{ST_STAGE1, OL_C_POT_COMM, RT_NormalOpened},			// 24
		{ST_STAGE1, MC_C_POT_LSL_POTP, RT_NormalOpened},		// 25
		{ST_STAGE1, G_PE, RT_NormalClosed},						// 26
		{ST_STAGE1, C_POT_PE, RT_NormalClosed},					// 27
		{ST_STAGE1, ST_TI_GT_G_POT, RT_NormalOpened},			// 28
		{ST_STAGE1, ST_TO_GT_GE, RT_NormalOpened},				// 29
		{ST_STAGE1, IL_GT_G_POT_COMM, RT_NormalOpened},			// 30
		{ST_STAGE1, IL_GT_GE_POT_COMM, RT_NormalOpened},		// 31
		{ST_STAGE1, IL_GT_G_GE_POT, RT_NormalOpened},			// 32
		{ST_STAGE1, IL_GT_G_GE_POT, RT_NormalOpened},			// 33
		//
		{ST_STAGE2, MC_E_POT_GT_GE_POT, RT_NormalOpened},		// 34
		{ST_STAGE2, MC_E_POT_LSL_POTN, RT_NormalOpened},		// 35
		{ST_STAGE2, ST_TI_LSL_POTP, RT_NormalOpened},			// 36
		{ST_STAGE2, ST_TO_GT_GE_POT, RT_NormalOpened},			// 37
		{ST_STAGE2, IL_LSL_POTP_COMM, RT_NormalOpened},			// 38
		{ST_STAGE2, IL_LSL_POTN_COMM, RT_NormalOpened},			// 39
		{ST_STAGE2, IL_LSL_POTS, RT_NormalOpened},				// 40
		//
		{ST_STAGE3, MC_E_POT_GT_GE_POT, RT_NormalOpened},		// 41
		{ST_STAGE3, MC_E_POT_LSL_POTN, RT_NormalOpened},		// 42
		{ST_STAGE3, OL_GE_COMM, RT_NormalOpened},				// 43
		{ST_STAGE3, MC_GE_LSL_GE, RT_NormalOpened},				// 44
		{ST_STAGE3, MC_G_GE, RT_NormalOpened},					// 45
		{ST_STAGE3, OL_G_COMM, RT_NormalOpened},				// 46
		{ST_STAGE3, MC_G_GT_G_POT, RT_NormalOpened},			// 47
		{ST_STAGE3, ST_TI_LSL_G, RT_NormalOpened},				// 48
		{ST_STAGE3, ST_TO_LSL_POTN, RT_NormalOpened},			// 49
		{ST_STAGE3, IL_GT_G_POT_COMM, RT_NormalOpened},			// 50
		{ST_STAGE3, IL_GT_GE_POT_COMM, RT_NormalOpened},		// 51
		{ST_STAGE3, IL_LSL_G_COMM, RT_NormalOpened},			// 52
		{ST_STAGE3, IL_LSL_GE_COMM, RT_NormalOpened},			// 53
		{ST_STAGE3, IL_GT_G_GE_POT, RT_NormalOpened},			// 54
		{ST_STAGE3, IL_LSL_G_GE, RT_NormalOpened}				// 55
};

const SelfTestTableItem SelfTestHV2Board[ST_HV_BOARD_COMM] =
{
		{ST_STAGE0, E_POT_2_PE, RT_NormalClosed},				// 0
		{ST_STAGE0, GE_2_PE, RT_NormalClosed},					// 1
		{ST_STAGE0, OL_E_POT_2_COMM, RT_NormalOpened},			// 2
		{ST_STAGE0, OL_GE_2_COMM, RT_NormalOpened},				// 3
		{ST_STAGE0, MC_G_2_C_POT, RT_NormalOpened},				// 4
		{ST_STAGE0, MC_GE_2_GT_GE, RT_NormalOpened},			// 5
		{ST_STAGE0, MC_G_2_LSL_G, RT_NormalOpened},				// 6
		{ST_STAGE0, MC_E_POT_2_LSL_POTN, RT_NormalOpened},		// 7
		{ST_STAGE0, MC_C_POT_2_LSL_POTN, RT_NormalOpened},		// 8
		{ST_STAGE0, ST_TI_GT_G, RT_NormalOpened},				// 9
		{ST_STAGE0, ST_TO_LSL_GE, RT_NormalOpened},				// 10
		{ST_STAGE0, IL_GT_G_COMM, RT_NormalOpened},				// 11
		{ST_STAGE0, IL_GT_GE_COMM, RT_NormalOpened},			// 12
		{ST_STAGE0, IL_LSL_G_COMM, RT_NormalOpened},			// 13
		{ST_STAGE0, IL_LSL_GE_COMM, RT_NormalOpened},			// 14
		{ST_STAGE0, IL_GT_G_GE, RT_NormalOpened},				// 15
		{ST_STAGE0, IL_LSL_G_GE, RT_NormalOpened},				// 16
		//
		{ST_STAGE1, MC_E_POT_2_GT_GE_POT, RT_NormalOpened},		// 17
		{ST_STAGE1, MC_E_POT_2_LSL_POTP, RT_NormalOpened},		// 18
		{ST_STAGE1, OL_GE_2_COMM, RT_NormalOpened},				// 19
		{ST_STAGE1, MC_GE_2_GT_G, RT_NormalOpened},				// 20
		{ST_STAGE1, MC_G_2_GE, RT_NormalOpened},				// 21
		{ST_STAGE1, MC_G_2_GT_G, RT_NormalOpened},				// 22
		{ST_STAGE1, MC_G_2_GT_GE, RT_NormalOpened},				// 23
		{ST_STAGE1, OL_C_POT_2_COMM, RT_NormalOpened},			// 24
		{ST_STAGE1, MC_C_POT_2_LSL_POTP, RT_NormalOpened},		// 25
		{ST_STAGE1, G_2_PE, RT_NormalClosed},					// 26
		{ST_STAGE1, C_POT_2_PE, RT_NormalClosed},				// 27
		{ST_STAGE1, ST_TI_GT_G_POT, RT_NormalOpened},			// 28
		{ST_STAGE1, ST_TO_GT_GE, RT_NormalOpened},				// 29
		{ST_STAGE1, IL_GT_G_POT_COMM, RT_NormalOpened},			// 30
		{ST_STAGE1, IL_GT_GE_POT_COMM, RT_NormalOpened},		// 31
		{ST_STAGE1, IL_GT_G_GE_POT, RT_NormalOpened},			// 32
		{ST_STAGE1, IL_GT_G_GE_POT, RT_NormalOpened},			// 33
		//

		{ST_STAGE2, MC_E_POT_2_GT_GE_POT, RT_NormalOpened},		// 34
		{ST_STAGE2, MC_E_POT_2_LSL_POTN, RT_NormalOpened},		// 35
		{ST_STAGE2, ST_TI_LSL_POTP, RT_NormalOpened},			// 36
		{ST_STAGE2, ST_TO_GT_GE_POT, RT_NormalOpened},			// 37
		{ST_STAGE2, IL_LSL_POTP_COMM, RT_NormalOpened},			// 38
		{ST_STAGE2, IL_LSL_POTN_COMM, RT_NormalOpened},			// 39
		{ST_STAGE2, IL_LSL_POTS, RT_NormalOpened},				// 40
		//
		{ST_STAGE3, MC_E_POT_2_GT_GE_POT, RT_NormalOpened},		// 41
		{ST_STAGE3, MC_E_POT_2_LSL_POTN, RT_NormalOpened},		// 42
		{ST_STAGE3, OL_GE_2_COMM, RT_NormalOpened},				// 43
		{ST_STAGE3, MC_GE_2_LSL_GE, RT_NormalOpened},			// 44
		{ST_STAGE3, MC_G_2_GE, RT_NormalOpened},				// 45
		{ST_STAGE3, OL_G_2_COMM, RT_NormalOpened},				// 46
		{ST_STAGE3, MC_G_2_GT_G_POT, RT_NormalOpened},			// 47
		{ST_STAGE3, ST_TI_LSL_G, RT_NormalOpened},				// 48
		{ST_STAGE3, ST_TO_LSL_POTN, RT_NormalOpened},			// 49
		{ST_STAGE3, IL_GT_G_POT_COMM, RT_NormalOpened},			// 50
		{ST_STAGE3, IL_GT_GE_POT_COMM, RT_NormalOpened},		// 51
		{ST_STAGE3, IL_LSL_G_COMM, RT_NormalOpened},			// 52
		{ST_STAGE3, IL_LSL_GE_COMM, RT_NormalOpened},			// 53
		{ST_STAGE3, IL_GT_G_GE_POT, RT_NormalOpened},			// 54
		{ST_STAGE3, IL_LSL_G_GE, RT_NormalOpened}				// 55
};
