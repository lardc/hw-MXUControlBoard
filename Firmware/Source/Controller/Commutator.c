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
static Int16U OldActionID = ACT_COMM_NONE;
static Int16U OldPostion = 0;

// Functions
//
void COMM_DisconnectPE()
{
	ZcRD_OutputValuesCompose(C_POT_PE_1, TRUE);
	ZcRD_OutputValuesCompose(G_PE_1, TRUE);
	ZcRD_OutputValuesCompose(GE_PE_1, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE_1, TRUE);
	ZcRD_OutputValuesCompose(C_POT_PE_2, TRUE);
	ZcRD_OutputValuesCompose(G_PE_2, TRUE);
	ZcRD_OutputValuesCompose(GE_PE_2, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE_2, TRUE);
	ZcRD_OutputValuesCompose(T_PE_1, TRUE);
	ZcRD_OutputValuesCompose(T_PE_2, TRUE);
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID)
{
	if (ActionID == OldActionID && \
			(DataTable[REG_DUT_POSITION] == OldPostion || \
					OldActionID == ACT_COMM_NONE || OldActionID == ACT_COMM_NO_PE || OldActionID == ACT_COMM_THERMISTOR))
		return;

	switch(ActionID)
	{
		case ACT_COMM_NONE:
			OldPostion = 0;
			ZcRD_RegisterReset();

			PMXU_SwitchCommutation(ACT_PMXU_COMM_PE);
			break;

		case ACT_COMM_IGES_POS_PULSE:
			{
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();
					OldPostion = DUT_POSITION_1;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM_1, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP_1, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP_1, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_G_1, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_GE_1, TRUE);
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

					OldPostion = DUT_POSITION_2;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM_2, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP_2, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP_2, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_G_2, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_GE_2, TRUE);
					//
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
					//

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_IGES_NEG_PULSE:
			{
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = DUT_POSITION_1;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM_1, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP_1, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP_1, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_GE_1, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_G_1, TRUE);
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

					OldPostion = DUT_POSITION_2;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM_2, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP_2, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP_2, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_GE_2, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_G_2, TRUE);
					//
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
					//

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_UGE_TH:
			{
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = DUT_POSITION_1;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM_1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM_1, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_G_C_POT_1, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_G_GT_G_1, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_GE_1, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_GT_GE_POT_1, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_G_POT_1, TRUE);
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

					OldPostion = DUT_POSITION_2;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM_2, TRUE);
					ZcRD_OutputValuesCompose(MC_G_C_POT_2, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_G_GT_G_2, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_GE_2, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_GT_GE_POT_2, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_G_POT_2, TRUE);
					//
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_POT_COMM, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_POT_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_QG:
			{
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_QG_POS1))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_COMM_1, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM_1, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GT_G_1, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_GT_GE_1, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

						ZcRD_RegisterFlushWrite();

						OldPostion = DUT_POSITION_1;
					}
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_QG_POS2))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_COMM_2, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM_2, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GT_G_2, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_GT_GE_2, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();

						OldPostion = DUT_POSITION_2;
					}
				}
			}
			break;

		case ACT_COMM_UCE_SAT:
			{
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_VCESAT_POS1))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_COMM_1, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM_1, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM_1, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM_1, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_LSL_G_1, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_LSL_GE_1, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP_1, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTN_1, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();

						OldPostion = DUT_POSITION_1;
					}
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_VCESAT_POS2))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_COMM_2, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM_2, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM_2, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM_2, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_LSL_G_2, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_LSL_GE_2, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP_2, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTN_2, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();

						OldPostion = DUT_POSITION_2;
					}
				}
			}
			break;

		case ACT_COMM_UFW_CHOPPER_DIODE:
			{
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_VF_POS1))
					{
						ZcRD_OutputValuesReset();

						COMM_DisconnectPE();

						OldPostion = DUT_POSITION_1;

						ZcRD_OutputValuesCompose(OL_C_POT_COMM_1, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM_1, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GE_1, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTN_1, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP_1, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_VF_POS2))
					{
						ZcRD_OutputValuesReset();

						COMM_DisconnectPE();

						OldPostion = DUT_POSITION_2;

						ZcRD_OutputValuesCompose(OL_C_POT_COMM_2, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM_2, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GE_2, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTN_2, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP_2, TRUE);
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
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_ICES_POS1))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						ZcRD_OutputValuesCompose(MC_G_GE_1, TRUE);
						ZcRD_RegisterFlushWrite();

						OldPostion = DUT_POSITION_1;
					}
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_ICES_POS2))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						ZcRD_OutputValuesCompose(MC_G_GE_2, TRUE);
						ZcRD_RegisterFlushWrite();

						OldPostion = DUT_POSITION_2;
					}
				}
			}
			break;

		case ACT_COMM_THERMISTOR:
			{
				ZcRD_OutputValuesReset();

				COMM_DisconnectPE();

				OldPostion = 0;

				ZcRD_OutputValuesCompose(OL_T_COMM_1, TRUE);
				ZcRD_OutputValuesCompose(OL_T_COMM_2, TRUE);
				//
				ZcRD_OutputValuesCompose(MC_T_GT_G_2, TRUE);
				ZcRD_OutputValuesCompose(MC_T_GT_GE_1, TRUE);
				ZcRD_OutputValuesCompose(MC_T_GT_G_POT_2, TRUE);
				ZcRD_OutputValuesCompose(MC_T_GT_GE_POT_1, TRUE);
				//
				ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
				ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
				ZcRD_OutputValuesCompose(IL_GT_G_POT_COMM, TRUE);
				ZcRD_OutputValuesCompose(IL_GT_GE_POT_COMM, TRUE);
				//

				ZcRD_RegisterFlushWrite();
			}
			break;

		case ACT_COMM_NO_PE:
			{
				OldPostion = 0;
				ZcRD_OutputValuesReset();
				COMM_DisconnectPE();
				ZcRD_RegisterFlushWrite();
			}
			break;

		default:
			break;
	}

	DELAY_MS(COMM_DELAY_MS);

	OldActionID = ActionID;
}
// ----------------------------------------
