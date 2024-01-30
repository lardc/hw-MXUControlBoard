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

// Functions
//
void COMM_Default()
{
	ZcRD_RegisterReset();
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
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID)
{
	switch(ActionID)
	{
		case ACT_COMM_NONE:
			if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_PE))
				COMM_Default();
			break;

		case ACT_COMM_IGES_POS_PULSE:
			{
				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_NO_PE))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_C_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP, TRUE);
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

						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
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
				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_NO_PE))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_C_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP, TRUE);
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

						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
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
				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_NO_PE))
				{
					if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_C_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(MC_G_C_POT, TRUE);
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

						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(MC_G_2_C_POT, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_GT_GE_POT, TRUE);
						ZcRD_OutputValuesCompose(MC_G_2_GT_G_POT, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
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
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_QG))
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
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_QG))
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
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_VCESAT))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_LSL_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_LSL_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTN, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_VCESAT))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_LSL_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_LSL_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
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
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_VF))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_C_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTN, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_VF))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_E_POT_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTN, TRUE);
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
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_ICES))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						ZcRD_OutputValuesCompose(MC_G_GE, TRUE);
						ZcRD_RegisterFlushWrite();
					}
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_ICES))
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
				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_NO_PE))
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
				if(PMXU_SwitchCommutation(DataTable[REG_DUT_POSITION], ACT_PMXU_COMM_NO_PE))
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
