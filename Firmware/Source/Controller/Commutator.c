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
static void COMM_SaveLastRequest(Int16U ActionID);
static void COMM_DischargeBeforeIcesOrIrrm();

// Functions
//
void COMM_Default()
{
	ZcRD_RegisterReset();

	COMM_State = COMM_Def;
}
// ----------------------------------------

void COMM_DisconnectPE() // После окончания переименовать в Connect to GND
{
	ZcRD_OutputValuesCompose(GND_TO_EPOT1, TRUE);
	ZcRD_OutputValuesCompose(GND_TO_EPOT2, TRUE);
	ZcRD_OutputValuesCompose(GND_TO_CPOT1, TRUE);
	ZcRD_OutputValuesCompose(GND_TO_CPOT2, TRUE);
}
// ----------------------------------------

static bool COMM_IsDiodeModule(Int16U CaseUnderTest)
{
	return (CaseUnderTest == SC_Type_MDAA ||
			CaseUnderTest == SC_Type_MDFA_MDF2_DD ||
			CaseUnderTest == SC_Type_MDSM ||
			CaseUnderTest == SC_Type_MDSV ||
			CaseUnderTest == SC_Type_MDFA_MDF2_SD ||
			CaseUnderTest == SC_Type_MDA2);
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID)
{
	Int16U DUTPosition = DataTable[REG_DUT_POSITION];
	Int16U DUTCase = DataTable[REG_DUT_CASE];
	Int16U DUTScheme = DataTable[REG_DUT_SCHEME];
	ModuleType ModuleType = DUTCase + DUTScheme;

	COMM_SaveLastRequest(ActionID);

	// У прибора MISM-DS позиции 1 и 2 меняются местами, чтобы задаваемая позиция 1
	// соответствала транзистору VT1 в документации
	if(DUTCase == SC_Type_MISM)
		DUTPosition = (DataTable[REG_DUT_POSITION] == DUT_POSITION_1) ? DUT_POSITION_2 : DUT_POSITION_1;

	// Разряд после ICES/IRRM: перед любой следующей коммутацией обнуляем выходы
	// сдвиговых регистров с удержанием SFT_ENABLE=true ~10 мс, чтобы «стекло»
	// остаточное напряжение на DUT.
	if(COMM_State == COMM_IcesOrIrrm && ActionID != ACT_COMM_ICES_OR_IRRM)
		COMM_DischargeBeforeIcesOrIrrm();

	switch(ActionID)
	{
		case ACT_COMM_NONE:
			if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_PE))
				COMM_Default();
			break;

		case ACT_COMM_IGES_POS_PULSE:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_NO_PE))
				{
					COMM_State = COMM_Iges_Pos;

					ZcRD_OutputValuesReset();
					COMM_DisconnectPE();
					ZcRD_OutputValuesCompose(GT_G_TO_G, TRUE);
					ZcRD_OutputValuesCompose(GT_GE_TO_GE, TRUE);
					ZcRD_OutputValuesCompose(GT_G_COMM, TRUE);
					ZcRD_OutputValuesCompose(GT_G_COMM, TRUE);

					if (DUTPosition == DUT_POSITION_1)
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
								ZcRD_OutputValuesCompose(EPOT_TO_CPOT1, TRUE);
								ZcRD_OutputValuesCompose(EPOT_TO_EPOT1, TRUE);
								ZcRD_OutputValuesCompose(G_TO_G1, TRUE);
								ZcRD_OutputValuesCompose(GE_TO_GE1, TRUE);
								ZcRD_OutputValuesCompose(GE1_TO_G1, TRUE);
								ZcRD_RegisterFlushWrite();
								break;
							default:
								break;
						}
					}
					else if (DUTPosition == DUT_POSITION_2)
					{
						switch(ModuleType)
						{
							case MIAA_CE:
								ZcRD_OutputValuesCompose(EPOT_TO_EPOT1, TRUE);
								ZcRD_OutputValuesCompose(GE_TO_GE2, TRUE);
								ZcRD_OutputValuesCompose(G_TO_G2, TRUE);
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
								ZcRD_OutputValuesCompose(EPOT_TO_CPOT2, TRUE);
								ZcRD_OutputValuesCompose(EPOT_TO_EPOT2, TRUE);
								ZcRD_OutputValuesCompose(G_TO_G2, TRUE);
								ZcRD_OutputValuesCompose(GE_TO_GE2, TRUE);
								ZcRD_OutputValuesCompose(GE2_TO_G2, TRUE);
								break;
							default:
								break;
						}
						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_IGES_NEG_PULSE:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_NO_PE))
				{
					COMM_State = COMM_Iges_Neg;

					if(COMM_IsDiodeModule(DUTCase))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						break;
					}
					if (DUTPosition == DUT_POSITION_2	||
						DUTCase == SC_Type_MIHV			||
						DUTCase == SC_Type_MIHM			||
						DUTCase == SC_Type_MISV			||
						DUTCase == SC_Type_MISM2_SS_SD)
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
					else if (DUTPosition == DUT_POSITION_1)
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
				}
			}
			break;

		case ACT_COMM_UGE_TH:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_NO_PE))
				{
					COMM_State = COMM_Ugeth;

					if(COMM_IsDiodeModule(DUTCase))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						break;
					}
					if (DUTPosition == DUT_POSITION_2	||
						DUTCase == SC_Type_MIHV			||
						DUTCase == SC_Type_MIHM			||
						DUTCase == SC_Type_MISV			||
						DUTCase == SC_Type_MISM2_SS_SD)
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
					else if (DUTPosition == DUT_POSITION_1)
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
				}
			}
			break;

		case ACT_COMM_UCE_SAT:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_VCESAT))
				{
					COMM_State = COMM_Ucesat;

					if(COMM_IsDiodeModule(DUTCase))
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						break;
					}
					if (DUTPosition == DUT_POSITION_2	||
						DUTCase == SC_Type_MIHV			||
						DUTCase == SC_Type_MIHM			||
						DUTCase == SC_Type_MISV			||
						DUTCase == SC_Type_MISM2_SS_SD)
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
					else if (DUTPosition == DUT_POSITION_1)
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
				}
			}
			break;

		case ACT_COMM_UFW_CHOPPER_DIODE:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_VF))
				{
					COMM_State = COMM_Uf;

					if(DUTPosition == DUT_POSITION_2 && DUTCase == SC_Type_MDSM)
					{
						// Выполнение коммутации по аналогии COMM_Ucesat
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();

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
						COMM_DisconnectPE();

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
				}
			}
			break;

		case ACT_COMM_ICES_OR_IRRM:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_ICES))
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
						COMM_DisconnectPE();
						ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);
						ZcRD_RegisterFlushWrite();
					}
					else if (DUTPosition == DUT_POSITION_1)
					{
						ZcRD_OutputValuesReset();
						COMM_DisconnectPE();
						ZcRD_OutputValuesCompose(MC_G_GE, TRUE);
						ZcRD_RegisterFlushWrite();
					}
				}
			}
			break;

		case ACT_COMM_THERMISTOR:
			{
				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_NO_PE))
				{
					COMM_State = COMM_Thermistor;

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
				COMM_State = COMM_NoPE;

				if(PMXU_SwitchCommutation(DUTPosition, DUTCase, ACT_PMXU_COMM_NO_PE))
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

	// TODO: после уточнения datasheet реле IORelayBoard перенести задержку внутрь
	// ZcRD_RegisterFlushWrite или минимизировать (сейчас — грубая 20 мс страховка).
	DELAY_MS(COMM_DELAY_MS);
}
// ----------------------------------------

static void COMM_SaveLastRequest(Int16U ActionID)
{
	DataTable[REG_LAST_CMD]  = ActionID;
	DataTable[REG_LAST_POS]  = (Int16U)DataTable[REG_DUT_POSITION];
	DataTable[REG_LAST_CASE] = (Int16U)DataTable[REG_DUT_CASE];
	DataTable[REG_LAST_TYPE] = (Int16U)DataTable[REG_DUT_SCHEME];
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

Int16U COMM_ValidateRequest(Int16U ActionID, Int16U Position, Int16U DevCase, Int16U Scheme)
{
	(void)Scheme;	// TODO: детализировать допустимые тройки «позиция + корпус + схема» после уточнения матриц.

	if(Position != DUT_POSITION_1 && Position != DUT_POSITION_2)
		return ERR_OPERATION_BLOCKED;

	// Команды, которые обрабатывает COMM_Commutate.
	switch(ActionID)
	{
		case ACT_COMM_NONE:
		case ACT_COMM_NO_PE:
			return ERR_NONE;	// допустимо без проверки корпуса

		case ACT_COMM_IGES_POS_PULSE:
		case ACT_COMM_IGES_NEG_PULSE:
		case ACT_COMM_UGE_TH:
		case ACT_COMM_UCE_SAT:
		case ACT_COMM_UFW_CHOPPER_DIODE:
		case ACT_COMM_ICES_OR_IRRM:
		case ACT_COMM_THERMISTOR:
			break;

		default:
			return ERR_OPERATION_BLOCKED;
	}

	// Проверка готовности PMXU и корпуса возложена на вызывающую сторону
	// (CONTROL_DispatchAction), здесь подтверждаем номер команды и позицию.
	(void)DevCase;
	return ERR_NONE;
}
// ----------------------------------------
