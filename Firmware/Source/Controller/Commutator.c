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
#include "LowLevel.h"

// Variables
//
CommutationState COMM_State = COMM_Def;

// Forward declarations
//
void COMM_SaveLastRequest(Int16U ActionID);
static void COMM_DischargeBeforeIcesOrIrrm();
bool COMM_ValidateIGBT(Int16U Position, ModuleTypes Module);

// Functions
//
void COMM_Default()
{
	ZcRD_RegisterReset();

	COMM_State = COMM_Def;
}
// ----------------------------------------

void COMM_ConnectToGND()
{
	ZcRD_OutputValuesCompose(GND_TO_EPOT1, TRUE);
	ZcRD_OutputValuesCompose(GND_TO_EPOT2, TRUE);
	ZcRD_OutputValuesCompose(GND_TO_CPOT1, TRUE);
	ZcRD_OutputValuesCompose(GND_TO_CPOT2, TRUE);
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID)
{
	Int16U DUTPosition = DataTable[REG_DUT_POSITION];
	Int16U DUTCase = DataTable[REG_DUT_CASE];
	Int16U DUTScheme = DataTable[REG_DUT_SCHEME];

	ModuleTypes ModuleType = COMM_CalcModuleType();

	// Разряд после ICES/IRRM: перед любой следующей коммутацией обнуляем выходы
	// сдвиговых регистров с удержанием SFT_ENABLE=true ~10 мс, чтобы «стекло»
	// остаточное напряжение на DUT.
	if(COMM_State == COMM_IcesOrIrrm && ActionID != ACT_COMM_ICES_OR_IRRM)
		COMM_DischargeBeforeIcesOrIrrm();

	switch(ActionID)
	{
		case ACT_COMM_NONE:
			if(PMXU_SwitchCommutation(DUTPosition, DUTCase, DUTScheme, ACT_PMXU_COMM_PE))
				COMM_Default();
			break;

		case ACT_COMM_IGES_POS_PULSE:
		case ACT_COMM_IGES_NEG_PULSE:
		case ACT_COMM_UGE_TH:
		case ACT_COMM_UCE_SAT:
			{
				PMXU_ProcessState = PP_CheckReadyAndFault;

				ZcRD_OutputValuesReset();
				COMM_ConnectToGND();
				switch(ActionID)
				{
					case ACT_COMM_IGES_POS_PULSE:
						COMM_State = COMM_Iges_Pos;
						ZcRD_OutputValuesCompose(GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(GT_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(GT_G_TO_G, TRUE);
						ZcRD_OutputValuesCompose(GT_GE_TO_GE, TRUE);
						break;
					case ACT_COMM_IGES_NEG_PULSE:
						COMM_State = COMM_Iges_Neg;
						ZcRD_OutputValuesCompose(GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(GT_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(GT_G_TO_GE, TRUE);
						ZcRD_OutputValuesCompose(GT_GE_TO_G, TRUE);
						break;
					case ACT_COMM_UGE_TH:
						COMM_State = COMM_Ugeth;
						ZcRD_OutputValuesCompose(GT_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(GT_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(GT_GPOT_COMM, TRUE);
						ZcRD_OutputValuesCompose(GT_GEPOT_COMM, TRUE);
						ZcRD_OutputValuesCompose(GT_G_TO_G, TRUE);
						ZcRD_OutputValuesCompose(GT_GE_TO_GE, TRUE);
						ZcRD_OutputValuesCompose(GT_GPOT_TO_G, TRUE);
						ZcRD_OutputValuesCompose(GT_GEPOT_TO_EPOT, TRUE);
						ZcRD_OutputValuesCompose(G_TO_CPOT, TRUE);
						break;
					case ACT_COMM_UCE_SAT:
						COMM_State = COMM_Ucesat;
						ZcRD_OutputValuesCompose(SV_G_COMM, TRUE);
						ZcRD_OutputValuesCompose(SV_GE_COMM, TRUE);
						ZcRD_OutputValuesCompose(SV_POT_POS_COMM, TRUE);
						ZcRD_OutputValuesCompose(SV_POT_NEG_COMM, TRUE);
						ZcRD_OutputValuesCompose(SV_G_TO_G, TRUE);
						ZcRD_OutputValuesCompose(SV_GE_TO_GE, TRUE);
						ZcRD_OutputValuesCompose(SV_POT_POS_TO_CPOT, TRUE);
						ZcRD_OutputValuesCompose(SV_POT_NEG_TO_EPOT, TRUE);
						break;

				}
				if(DUTPosition == DUT_POSITION_1)
				{
					switch(ModuleType)
					{
						case MIAA_CE:
						case MIAA_HB:
						case MIAA_LC:
						case MIDA_HB:
						case MIFA_HB:
						case MIFA_LC:
						case MIHA_HB:
						case MIHA_LC:
						case MIHM_SS:
						case MIHV_SS:
						case MISM_CH:
						case MISM_DS:
						case MISM_SS:
						case MISV_SS:
						case MIXM_HB:
						case MIXM_LR_LRD:
						case MIXV_HB:
							if(ActionID == ACT_COMM_UGE_TH || ActionID == ACT_COMM_UCE_SAT)
								ZcRD_OutputValuesCompose(CPOT_TO_CPOT1, TRUE);
							else
								ZcRD_OutputValuesCompose(EPOT_TO_CPOT1, TRUE);
							ZcRD_OutputValuesCompose(EPOT_TO_EPOT1, TRUE);
							ZcRD_OutputValuesCompose(G_TO_G1, TRUE);
							ZcRD_OutputValuesCompose(GE_TO_GE1, TRUE);
							ZcRD_OutputValuesCompose(GE1_TO_G1, TRUE);
							break;
						default:
							break;
					}
				}
				else if(DUTPosition == DUT_POSITION_2)
				{
					switch(ModuleType)
					{
						case MIAA_CE:
							ZcRD_OutputValuesCompose(EPOT_TO_EPOT1, TRUE);
							ZcRD_OutputValuesCompose(GE_TO_GE2, TRUE);
							ZcRD_OutputValuesCompose(G_TO_G2, TRUE);
							if(ActionID == ACT_COMM_UGE_TH || ActionID == ACT_COMM_UCE_SAT)
								ZcRD_OutputValuesCompose(CPOT_TO_CPOT2, TRUE);
							else
								ZcRD_OutputValuesCompose(EPOT_TO_CPOT2, TRUE);
							break;
						case MIAA_HB:
						case MIAA_HC:
						case MIDA_HB:
						case MIFA_HB:
						case MIFA_HC:
						case MIHA_HB:
						case MIHA_HC:
						case MISM_DS:
						case MIXM_HB:
						case MIXV_HB:
							if(ActionID == ACT_COMM_UGE_TH || ActionID == ACT_COMM_UCE_SAT)
								ZcRD_OutputValuesCompose(CPOT_TO_CPOT2, TRUE);
							else
								ZcRD_OutputValuesCompose(EPOT_TO_CPOT2, TRUE);
							ZcRD_OutputValuesCompose(EPOT_TO_EPOT2, TRUE);
							ZcRD_OutputValuesCompose(G_TO_G2, TRUE);
							ZcRD_OutputValuesCompose(GE_TO_GE2, TRUE);
							ZcRD_OutputValuesCompose(GE2_TO_G2, TRUE);
							break;
						default:
							break;
					}
				}
				ZcRD_RegisterFlushWrite();
			}
			break;

		case ACT_COMM_UFW_CHOPPER_DIODE:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, DUTScheme, ACT_PMXU_COMM_VF))
				{
					COMM_State = COMM_Uf;

					if(DUTPosition == DUT_POSITION_2 && DUTCase == SC_Type_MDSM)
					{
						// Выполнение коммутации по аналогии COMM_Ucesat
						ZcRD_OutputValuesReset();
						COMM_ConnectToGND();

						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_LSL_G, TRUE);
						ZcRD_OutputValuesCompose(MC_GE_2_LSL_GE, TRUE);
						ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
						ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTN, TRUE);
						//
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);

						ZcRD_RegisterFlushWrite();
						break;
					}
					if (DUTPosition == DUT_POSITION_2	||
						DUTCase == SC_Type_MIHV			||
						DUTCase == SC_Type_MIHM			||
						DUTCase == SC_Type_MISV			||
						DUTCase == SC_Type_MISM2_SS_SD	||
						DUTCase ==  SC_Type_MDFA_MDF2_SD		||
						DUTCase ==  SC_Type_MDA2)
					{
						ZcRD_OutputValuesReset();
						COMM_ConnectToGND();

						ZcRD_OutputValuesCompose(OL_C_POT_2_COMM, TRUE);
						ZcRD_OutputValuesCompose(OL_E_POT_2_COMM, TRUE);
						//
						ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);
						if(DUTCase ==  SC_Type_MDFA_MDF2_SD || DUTCase ==  SC_Type_MDA2)
						{
							ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
							ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTN, TRUE);
						}
						else
						{
							ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTN, TRUE);
							ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
						}
						//
						ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
						ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
						//

						ZcRD_RegisterFlushWrite();
					}
					else if (DUTPosition == DUT_POSITION_1)
					{
						ZcRD_OutputValuesReset();
						COMM_ConnectToGND();

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
				}
			}
			break;

		case ACT_COMM_ICES_OR_IRRM:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, DUTScheme, ACT_PMXU_COMM_ICES))
				{
					COMM_State = COMM_IcesOrIrrm;

					if (DUTPosition == DUT_POSITION_2	||
						DUTCase == SC_Type_MIHV			||
						DUTCase == SC_Type_MIHM			||
						DUTCase == SC_Type_MISV			||
						DUTCase == SC_Type_MISM2_SS_SD	||
						DUTCase ==  SC_Type_MDFA_MDF2_SD		||
						DUTCase ==  SC_Type_MDA2)
					{
						ZcRD_OutputValuesReset();
						COMM_ConnectToGND();
						ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);
						ZcRD_RegisterFlushWrite();
					}
					else if (DUTPosition == DUT_POSITION_1)
					{
						ZcRD_OutputValuesReset();
						COMM_ConnectToGND();
						ZcRD_OutputValuesCompose(MC_G_GE, TRUE);
						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_THERMISTOR:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, DUTScheme, ACT_PMXU_COMM_NO_PE))
				{
					COMM_State = COMM_Thermistor;

					ZcRD_OutputValuesReset();
					COMM_ConnectToGND();

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
				COMM_State = COMM_NoPE;

				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, DUTScheme, ACT_PMXU_COMM_NO_PE))
				{
					ZcRD_OutputValuesReset();
					COMM_ConnectToGND();
					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		default:
			break;
	}

	// TODO: после уточнения datasheet реле IORelayBoard перенести задержку внутрь
	// ZcRD_RegisterFlushWrite или минимизировать (сейчас — грубая 20 мс страховка).
	DELAY_MS(COMM_DELAY_MS);
}
// ----------------------------------------

static void COMM_DischargeBeforeIcesOrIrrm()
{
	LL_SetStateSFT_ENABLE(true);
	ZcRD_OutputValuesReset();
	ZcRD_RegisterFlushWrite();
	DELAY_MS(10);
	LL_SetStateSFT_ENABLE(false);
}
// ----------------------------------------

Int16U COMM_CalcModuleType()
{
	Int16U CaseShift = 100;

	return (DataTable[REG_DUT_CASE] * CaseShift + DataTable[REG_DUT_SCHEME]);
}
// ----------------------------------------

bool COMM_ValidateRequest(Int16U ActionID, Int16U Position)
{
	if(Position != DUT_POSITION_1 && Position != DUT_POSITION_2)
	{
		CONTROL_FinishedWithProblem(PROBLEM_INCORRECT_DUT);
		return false;
	}

	ModuleTypes ModuleType = COMM_CalcModuleType();

	switch(ActionID)
	{
		case ACT_COMM_NONE:
		case ACT_COMM_NO_PE:
			return true;	// допустимо без проверки корпуса

		case ACT_COMM_IGES_POS_PULSE:
		case ACT_COMM_IGES_NEG_PULSE:
		case ACT_COMM_UGE_TH:
		case ACT_COMM_UCE_SAT:
			return COMM_ValidateIGBT(Position,ModuleType);

		case ACT_COMM_UFW_CHOPPER_DIODE:
		case ACT_COMM_ICES_OR_IRRM:
		case ACT_COMM_THERMISTOR:
			break;
	}

	CONTROL_FinishedWithProblem(PROBLEM_INCORRECT_COMMAND);
	return false;
}
// ----------------------------------------

bool COMM_ValidateIGBT(Int16U Position, ModuleTypes Module)
{
	if(Position == DUT_POSITION_1)
	{
		switch(Module)
		{
			case MIAA_CE:
			case MIAA_HB:
			case MIAA_LC:
			case MIDA_HB:
			case MIFA_HB:
			case MIFA_LC:
			case MIHA_HB:
			case MIHA_LC:
			case MIHM_SS:
			case MIHV_SS:
			case MISM_CH:
			case MISM_DS:
			case MISM_SS:
			case MISV_SS:
			case MIXM_HB:
			case MIXM_LR_LRD:
			case MIXV_HB:
				return true;
			default:
				CONTROL_FinishedWithProblem(PROBLEM_INCORRECT_DUT);
				return false;
		}
	}
	else if(Position == DUT_POSITION_2)
	{
		switch(Module)
		{
			case MIAA_CE:
			case MIAA_HB:
			case MIAA_HC:
			case MIDA_HB:
			case MIFA_HB:
			case MIFA_HC:
			case MIHA_HB:
			case MIHA_HC:
			case MISM_DS:
			case MIXM_HB:
			case MIXV_HB:
				return true;
			default:
				CONTROL_FinishedWithProblem(PROBLEM_INCORRECT_DUT);
				return false;
		}
	}
	return false;
}
