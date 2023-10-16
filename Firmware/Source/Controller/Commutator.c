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
	ZcRD_OutputValuesCompose(C_POT_PE1, TRUE);
	ZcRD_OutputValuesCompose(C_POT_PE2, TRUE);
	ZcRD_OutputValuesCompose(C_POT_PE3, TRUE);
	ZcRD_OutputValuesCompose(C_POT_PE4, TRUE);

	ZcRD_OutputValuesCompose(G_PE1, TRUE);
	ZcRD_OutputValuesCompose(G_PE2, TRUE);
	ZcRD_OutputValuesCompose(G_PE3, TRUE);
	ZcRD_OutputValuesCompose(G_PE4, TRUE);

	ZcRD_OutputValuesCompose(GE_PE1, TRUE);
	ZcRD_OutputValuesCompose(GE_PE2, TRUE);
	ZcRD_OutputValuesCompose(GE_PE3, TRUE);
	ZcRD_OutputValuesCompose(GE_PE4, TRUE);

	ZcRD_OutputValuesCompose(E_POT_PE1, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE2, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE3, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE4, TRUE);

	ZcRD_OutputValuesCompose(C_POT_2_PE1, TRUE);
	ZcRD_OutputValuesCompose(C_POT_2_PE2, TRUE);
	ZcRD_OutputValuesCompose(C_POT_2_PE3, TRUE);
	ZcRD_OutputValuesCompose(C_POT_2_PE4, TRUE);

	ZcRD_OutputValuesCompose(G_2_PE1, TRUE);
	ZcRD_OutputValuesCompose(G_2_PE2, TRUE);
	ZcRD_OutputValuesCompose(G_2_PE3, TRUE);
	ZcRD_OutputValuesCompose(G_2_PE4, TRUE);

	ZcRD_OutputValuesCompose(GE_2_PE1, TRUE);
	ZcRD_OutputValuesCompose(GE_2_PE2, TRUE);
	ZcRD_OutputValuesCompose(GE_2_PE3, TRUE);
	ZcRD_OutputValuesCompose(GE_2_PE4, TRUE);

	ZcRD_OutputValuesCompose(E_POT_2_PE1, TRUE);
	ZcRD_OutputValuesCompose(E_POT_2_PE2, TRUE);
	ZcRD_OutputValuesCompose(E_POT_2_PE3, TRUE);
	ZcRD_OutputValuesCompose(E_POT_2_PE4, TRUE);

	ZcRD_OutputValuesCompose(T1_PE1, TRUE);
	ZcRD_OutputValuesCompose(T1_PE2, TRUE);
	ZcRD_OutputValuesCompose(T1_PE3, TRUE);
	ZcRD_OutputValuesCompose(T1_PE4, TRUE);

	ZcRD_OutputValuesCompose(T2_PE1, TRUE);
	ZcRD_OutputValuesCompose(T2_PE2, TRUE);
	ZcRD_OutputValuesCompose(T2_PE3, TRUE);
	ZcRD_OutputValuesCompose(T2_PE4, TRUE);
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

					ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
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

					OldPostion = DUT_POSITION_2;

					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
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

					ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
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

					OldPostion = DUT_POSITION_2;

					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_2_GT_G, TRUE);
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

					ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_G_C_POT1, TRUE);
					ZcRD_OutputValuesCompose(MC_G_C_POT2, TRUE);
					ZcRD_OutputValuesCompose(MC_G_C_POT3, TRUE);
					ZcRD_OutputValuesCompose(MC_G_C_POT4, TRUE);
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

					OldPostion = DUT_POSITION_2;

					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					//
					ZcRD_OutputValuesCompose(MC_G_2_C_POT1, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_C_POT2, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_C_POT3, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_C_POT4, TRUE);
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
			break;

		case ACT_COMM_QG:
			{
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_QG_POS1))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);
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

						ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
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

						ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
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

						OldPostion = DUT_POSITION_1;
					}
				}
				else if (DataTable[REG_DUT_POSITION] == DUT_POSITION_2)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_VCESAT_POS2))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

						ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
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

						OldPostion = DUT_POSITION_2;
					}
				}
			}
			break;

		case ACT_COMM_UFW_CHOPPER_DIODE:
			{
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_VF_POS1_REV))
					{
						ZcRD_OutputValuesReset();

						COMM_DisconnectPE();

						OldPostion = DUT_POSITION_1;

						ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
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
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_VF_POS2_REV))
					{
						ZcRD_OutputValuesReset();

						COMM_DisconnectPE();

						OldPostion = DUT_POSITION_2;

						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
						//
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
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
				if (DataTable[REG_DUT_POSITION] == DUT_POSITION_1)
				{
					if(PMXU_SwitchCommutation(ACT_PMXU_COMM_ICES_POS1))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						ZcRD_OutputValuesCompose(MC_G_GE, TRUE);
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
						ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);
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

				ZcRD_OutputValuesCompose(OL_T1_COMM1, TRUE);
				ZcRD_OutputValuesCompose(OL_T1_COMM2, TRUE);
				ZcRD_OutputValuesCompose(OL_T1_COMM3, TRUE);
				ZcRD_OutputValuesCompose(OL_T1_COMM4, TRUE);
				//
				ZcRD_OutputValuesCompose(OL_T2_COMM1, TRUE);
				ZcRD_OutputValuesCompose(OL_T2_COMM2, TRUE);
				ZcRD_OutputValuesCompose(OL_T2_COMM3, TRUE);
				ZcRD_OutputValuesCompose(OL_T2_COMM4, TRUE);
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
