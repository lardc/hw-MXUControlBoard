// -----------------------------------------
// Commutation logic
// ----------------------------------------

// Header
#include "Commutator.h"
//
#include "ZcRegistersDriver.h"
#include "DeviceObjectDictionary.h"
#include "CommutationTable.h"
#include "Global.h"
#include "DataTable.h"
#include "Delay.h"
#include "PMXU.h"
#include "Constraints.h"

// Variables
//
CommutationState COMM_State = COMM_Def;

// Functions
//
void COMM_Default()
{
	ZcRD_RegisterReset();

	COMM_State = COMM_Def;
}
// ----------------------------------------

void COMM_DisconnectPE()
{
	ZcRD_OutputValuesCompose(C_POT_PE, TRUE);
	ZcRD_OutputValuesCompose(G_PE, TRUE);
	ZcRD_OutputValuesCompose(GE_PE, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE, TRUE);
	ZcRD_OutputValuesCompose(C_POT_2_PE, TRUE);
	ZcRD_OutputValuesCompose(G_2_PE, TRUE);
	ZcRD_OutputValuesCompose(GE_2_PE, TRUE);
	ZcRD_OutputValuesCompose(E_POT_2_PE, TRUE);
	ZcRD_OutputValuesCompose(T1_PE, TRUE);
	ZcRD_OutputValuesCompose(T2_PE, TRUE);

	COMM_State = COMM_NoPE;
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID)
{
	switch(ActionID)
	{
		case ACT_COMM_NONE:
			if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_PE))
				COMM_Default();
			break;

		case ACT_COMM_IGES_POS_PULSE:
			{
				COMM_State = COMM_Iges_Pos;

				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_NO_PE))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1	||
						DataTable[REG_DEV_CASE] == SC_Type_MIHV			||
						DataTable[REG_DEV_CASE] == SC_Type_MIHM			||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_CH 	||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_SS_SD)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
					else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_IGES_NEG_PULSE:
			{
				COMM_State = COMM_Iges_Neg;

				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_NO_PE))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1	||
						DataTable[REG_DEV_CASE] == SC_Type_MIHV			||
						DataTable[REG_DEV_CASE] == SC_Type_MIHM			||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_CH 	||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_SS_SD)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_G_GT_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_GT_G, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
					else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_G_2_GT_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_GT_G, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_UGE_TH:
			{
				COMM_State = COMM_Ugeth;

				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_NO_PE))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1	||
						DataTable[REG_DEV_CASE] == SC_Type_MIHV			||
						DataTable[REG_DEV_CASE] == SC_Type_MIHM			||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_CH 	||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_SS_SD)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(MC_G_C_POT, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_GT_GE_POT, TRUE);
						ZcRD_OutputValuesCompose(MC_G_GT_G_POT, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_G_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_POT_COMM, TRUE);

						ZcRD_RegisterFlushWrite();
					}
					else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(MC_G_2_C_POT, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_GT_GE_POT, TRUE);
						ZcRD_OutputValuesCompose(MC_G_2_GT_G_POT, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_G_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_POT_COMM, TRUE);

						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_QG:
			{
				COMM_State = COMM_Qg;

				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_QG))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1	||
						DataTable[REG_DEV_CASE] == SC_Type_MIHV			||
						DataTable[REG_DEV_CASE] == SC_Type_MIHM			||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_CH 	||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_SS_SD)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

						ZcRD_RegisterFlushWrite();
					}
					else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_UCE_SAT:
			{
				COMM_State = COMM_Ucesat;

				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_VCESAT))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1	||
						DataTable[REG_DEV_CASE] == SC_Type_MIHV			||
						DataTable[REG_DEV_CASE] == SC_Type_MIHM			||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_CH 	||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_SS_SD)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_LSL_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_LSL_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTN, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
					else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_LSL_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_LSL_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTN, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_UFW_CHOPPER_DIODE:
			{
				COMM_State = COMM_Uf;

				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_VF))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1	||
						DataTable[REG_DEV_CASE] == SC_Type_MIHV			||
						DataTable[REG_DEV_CASE] == SC_Type_MIHM			||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_CH 	||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_SS_SD)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTN, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
					else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTN, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_ICES:
			{
				COMM_State = COMM_Ices;

				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_ICES))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1	||
						DataTable[REG_DEV_CASE] == SC_Type_MIHV			||
						DataTable[REG_DEV_CASE] == SC_Type_MIHM			||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_CH 	||
						DataTable[REG_DEV_CASE] == SC_Type_MISM2_SS_SD)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						ZcRD_OutputValuesCompose(MC_G_GE, TRUE);
						ZcRD_RegisterFlushWrite();
					}
					else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);
						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_THERMISTOR:
			{
				COMM_State = COMM_Thermistor;

				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_NO_PE))
				{
					ZcRD_OutputValuesReset();
					COMM_DisconnectPE();

					ZcRD_OutputValuesCompose(OL_T1_COMM, TRUE);
					ZcRD_OutputValuesCompose(OL_T2_COMM, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_T2_GT_G, TRUE);
					ZcRD_OutputValuesCompose(MC_T1_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(MC_T2_GT_G_POT, TRUE);
					ZcRD_OutputValuesCompose(MC_T1_GT_GE_POT, TRUE);
					//
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_POT_COMM, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_POT_COMM, TRUE);
					//

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_NO_PE:
			{
				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE], ACT_PMXU_COMM_NO_PE))
				{
					ZcRD_OutputValuesReset();
					COMM_DisconnectPE();
					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		default:
			break;
	}

	DELAY_MS(COMM_DELAY_MS);
}
// ----------------------------------------
