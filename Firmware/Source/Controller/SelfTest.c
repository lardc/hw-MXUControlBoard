// Header
//
#include "SelfTest.h"

// Includes
//
#include "Math.h"
#include "Controller.h"
#include "DataTable.h"
#include "Delay.h"
#include "LowLevel.h"
#include "CommutationTable.h"
#include "ZcRegistersDriver.h"

// Defines
//

// Functions
//
void SELFTEST_Process()
{
	static DeviceSubState PrevSubstate = SS_None;
	uint8_t TestCommutation[] = {};
	uint8_t TestCommutation_IR1[] = {IL_GT_G_COMM, IL_GT_GE_COMM, IL_GT_G_GE, ST_TI_GT_G, ST_TO_GT_GE, INT8U_MAX};
	uint8_t TestCommutation_IR2[] = {IL_GT_G_POT_COMM, IL_GT_GE_POT_COMM, IL_GT_G_GE_POT, ST_TI_GT_G_POT, ST_TO_GT_GE_POT, INT8U_MAX};
	uint8_t TestCommutation_IR3[] = {IL_LSL_G_COMM, IL_LSL_GE_COMM, IL_LSL_G_GE, ST_TI_LSL_G, ST_TO_LSL_GE, INT8U_MAX};
	uint8_t TestCommutation_IR4[] = {IL_LSL_POTP_COMM, IL_LSL_POTN_COMM, IL_LSL_POTS, ST_TI_LSL_POTP, ST_TO_LSL_POTN, INT8U_MAX};
	uint8_t ArrayLength = 0;

	switch(CONTROL_SubState)
	{
		case SS_ST_StartPrepare:
			PrevSubstate = SS_ST_StartPrepare;
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_InputRelayCheck_1);
			break;

		case SS_ST_InputRelayCheck_1:
			PrevSubstate = SS_ST_InputRelayCheck_1;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_G_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_CurrentMeasure);
			break;

		case SS_ST_InputRelayCheck_2:
			PrevSubstate = SS_ST_InputRelayCheck_2;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_GT_G_POT_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_GE_POT_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_G_GE_POT, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G_POT, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE_POT, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_CurrentMeasure);
			break;

		case SS_ST_InputRelayCheck_3:
			PrevSubstate = SS_ST_InputRelayCheck_3;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_G_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_LSL_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_LSL_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_CurrentMeasure);
			break;

		case SS_ST_InputRelayCheck_4:
			PrevSubstate = SS_ST_InputRelayCheck_4;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_POTS, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_LSL_POTP, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_LSL_POTN, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_CurrentMeasure);
			break;

		case SS_ST_MCRelayCheck_1:
			PrevSubstate = SS_ST_MCRelayCheck_1;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
			ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
			ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
			ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
			ZcRD_OutputValuesCompose(MC_G_GE, TRUE);
			ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
			ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
			ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
			ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_CurrentMeasure);
			break;

		case SS_ST_MCRelayCheck_2:
			PrevSubstate = SS_ST_MCRelayCheck_2;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
			ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
			ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
			ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
			ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);
			ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
			ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
			ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
			ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_CurrentMeasure);
			break;

		case SS_ST_MCRelayCheck_3:
			PrevSubstate = SS_ST_MCRelayCheck_3;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
			ZcRD_OutputValuesCompose(MC_G_GT_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_CurrentMeasure);
			break;

		case SS_ST_MCRelayCheck_4:
			PrevSubstate = SS_ST_MCRelayCheck_4;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
			ZcRD_OutputValuesCompose(MC_G_2_GT_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_CurrentMeasure);
			break;

		case SS_ST_CurrentMeasure:
			PrevSubstate = SS_ST_CurrentMeasure;

			if (LL_TestClosedRelay())
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_SS]	= PrevSubstate;
				DataTable[REG_FAULT_RELAY] = PrevSubstate;
				ZcRD_RegisterReset();
				CONTROL_SwitchToFault(DF_VOLTAGE_MEASURING);
			}
			else
			{
				if (PrevSubstate == SS_ST_InputRelayCheck_1)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_InputRelayCheck_2);
				}
				else if (PrevSubstate == SS_ST_InputRelayCheck_2)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_InputRelayCheck_3);
				}
				else if (PrevSubstate == SS_ST_InputRelayCheck_3)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_InputRelayCheck_4);
				}
				else if (PrevSubstate == SS_ST_InputRelayCheck_4)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_MCRelayCheck_1);
				}
				else if (PrevSubstate == SS_ST_MCRelayCheck_1)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_MCRelayCheck_2);
				}
				else if (PrevSubstate == SS_ST_MCRelayCheck_2)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_MCRelayCheck_3);
				}
				else if (PrevSubstate == SS_ST_MCRelayCheck_3)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_MCRelayCheck_4);
				}
				else if (PrevSubstate == SS_ST_MCRelayCheck_4)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_InProcess, SS_ST_InputRelayOpenCheck_1);
				}
			}

			break;

		case SS_ST_InputRelayOpenCheck_1:
			PrevSubstate = SS_ST_InputRelayOpenCheck_1;
			ArrayLength = ST_GetArrayLength(TestCommutation_IR1);
			for (uint8_t i = 0; i < ArrayLength; i++)
			{
				TestCommutation[i] = TestCommutation_IR1[i];
			}
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_OpenRelayCheck);
			break;

		case SS_ST_InputRelayOpenCheck_2:
			PrevSubstate = SS_ST_InputRelayOpenCheck_2;
			ArrayLength = ST_GetArrayLength(TestCommutation_IR2);
			for (uint8_t i = 0; i < ArrayLength; i++)
			{
				TestCommutation[i] = TestCommutation_IR2[i];
			}
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_OpenRelayCheck);
			break;

		case SS_ST_InputRelayOpenCheck_3:
			PrevSubstate = SS_ST_InputRelayOpenCheck_3;
			ArrayLength = ST_GetArrayLength(TestCommutation_IR3);
			for (uint8_t i = 0; i < ArrayLength; i++)
			{
				TestCommutation[i] = TestCommutation_IR3[i];
			}
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_OpenRelayCheck);
			break;

		case SS_ST_InputRelayOpenCheck_4:
			PrevSubstate = SS_ST_InputRelayOpenCheck_4;
			ArrayLength = ST_GetArrayLength(TestCommutation_IR4);
			for (uint8_t i = 0; i < ArrayLength; i++)
			{
				TestCommutation[i] = TestCommutation_IR4[i];
			}
			CONTROL_SetDeviceState(DS_InProcess, SS_ST_OpenRelayCheck);
			break;


		case SS_ST_OpenRelayCheck:
			for(uint8_t i = 0; i < ArrayLength; i++)
			{
				// Включение всех реле
				for(uint8_t j = 0; j < ArrayLength; j++)
					ZcRD_OutputValuesCompose(TestCommutation[j], TRUE);

				// Отключение тестируемого реле
				ZcRD_OutputValuesCompose(TestCommutation[i], FALSE);

				// Тестирование

				if (LL_TestOpenRelay())
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					DataTable[REG_FAULT_RELAY] = TestCommutation[i];
					ZcRD_RegisterReset();
					CONTROL_SwitchToFault(DF_VOLTAGE_MEASURING);
				}
				else
				{
					if (PrevSubstate == SS_ST_InputRelayOpenCheck_1)
					{
						DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
						CONTROL_SetDeviceState(DS_InProcess, SS_ST_InputRelayOpenCheck_2);
					}
					else if (PrevSubstate == SS_ST_InputRelayOpenCheck_2)
					{
						DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
						CONTROL_SetDeviceState(DS_InProcess, SS_ST_InputRelayOpenCheck_3);
					}
					else if (PrevSubstate == SS_ST_InputRelayOpenCheck_3)
					{
						DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
						CONTROL_SetDeviceState(DS_InProcess, SS_ST_InputRelayOpenCheck_4);
					}
					else if (PrevSubstate == SS_ST_InputRelayOpenCheck_4)
					{
						DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
						CONTROL_SetDeviceState(DS_InProcess, SS_ST_MCRelayOpenCheck_1);
					}
				}
			}
			break;

		default:
			break;
	}
}
//-----------------------------------------------

int ST_GetArrayLength(uint8_t Data[])
{
	uint8_t ArrayLen = 0;
	for(uint8_t i = 0; i < INT8U_MAX; i++)
	{
		if(Data[i] == INT8U_MAX)
		{
			ArrayLen = i;
			break;
		}
	}
	return ArrayLen;
}
