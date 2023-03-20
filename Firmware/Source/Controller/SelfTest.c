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

// Variables
//
static const uint8_t TestCommutation_IR1[] = {IL_GT_G_COMM, IL_GT_GE_COMM, IL_GT_G_GE, ST_TI_GT_G, ST_TO_GT_GE};
static const uint8_t TestCommutation_IR2[] = {IL_GT_G_POT_COMM, IL_GT_GE_POT_COMM, IL_GT_G_GE_POT, ST_TI_GT_G_POT, ST_TO_GT_GE_POT};
static const uint8_t TestCommutation_IR3[] = {IL_LSL_G_COMM, IL_LSL_GE_COMM, IL_LSL_G_GE, ST_TI_LSL_G, ST_TO_LSL_GE};
static const uint8_t TestCommutation_IR4[] = {IL_LSL_POTP_COMM, IL_LSL_POTN_COMM, IL_LSL_POTS, ST_TI_LSL_POTP, ST_TO_LSL_POTN};

// Functions
//
void SELFTEST_Process()
{
	static DeviceSelfTestState PrevSubstate = STS_None;
	static uint8_t *SelectedTestArray = NULL;
	static uint8_t SelectedTestArrayLength = 0, TestIndex = 0;

	switch(CONTROL_SubState)
	{
		case STS_InputRelayCheck_1:
			PrevSubstate = STS_InputRelayCheck_1;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_G_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, STS_CurrentMeasure);
			break;

		case STS_InputRelayCheck_2:
			PrevSubstate = STS_InputRelayCheck_2;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_GT_G_POT_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_GE_POT_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_G_GE_POT, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G_POT, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE_POT, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, STS_CurrentMeasure);
			break;

		case STS_InputRelayCheck_3:
			PrevSubstate = STS_InputRelayCheck_3;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_G_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_LSL_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_LSL_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, STS_CurrentMeasure);
			break;

		case STS_InputRelayCheck_4:
			PrevSubstate = STS_InputRelayCheck_4;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_POTS, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_LSL_POTP, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_LSL_POTN, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, STS_CurrentMeasure);
			break;

		case STS_MCRelayCheck_1:
			PrevSubstate = STS_MCRelayCheck_1;

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
			CONTROL_SetDeviceState(DS_InProcess, STS_CurrentMeasure);
			break;

		case STS_MCRelayCheck_2:
			PrevSubstate = STS_MCRelayCheck_2;

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
			CONTROL_SetDeviceState(DS_InProcess, STS_CurrentMeasure);
			break;

		case STS_MCRelayCheck_3:
			PrevSubstate = STS_MCRelayCheck_3;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
			ZcRD_OutputValuesCompose(MC_G_GT_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, STS_CurrentMeasure);
			break;

		case STS_MCRelayCheck_4:
			PrevSubstate = STS_MCRelayCheck_4;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
			ZcRD_OutputValuesCompose(MC_G_2_GT_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_InProcess, STS_CurrentMeasure);
			break;

		case STS_CurrentMeasure:
			if(LL_ClosedRelayFailed())
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_SS] = PrevSubstate;
				ZcRD_RegisterReset();
				CONTROL_SwitchToFault(DF_RELAY_HIGH_RES);
			}
			else
			{
				switch(PrevSubstate)
				{
					case STS_InputRelayCheck_1:
						CONTROL_SetDeviceState(DS_InProcess, STS_InputRelayCheck_2);
						break;
					case STS_InputRelayCheck_2:
						CONTROL_SetDeviceState(DS_InProcess, STS_InputRelayCheck_3);
						break;
					case STS_InputRelayCheck_3:
						CONTROL_SetDeviceState(DS_InProcess, STS_InputRelayCheck_4);
						break;
					case STS_InputRelayCheck_4:
						CONTROL_SetDeviceState(DS_InProcess, STS_MCRelayCheck_1);
						break;

					case STS_MCRelayCheck_1:
						CONTROL_SetDeviceState(DS_InProcess, STS_MCRelayCheck_2);
						break;
					case STS_MCRelayCheck_2:
						CONTROL_SetDeviceState(DS_InProcess, STS_MCRelayCheck_3);
						break;
					case STS_MCRelayCheck_3:
						CONTROL_SetDeviceState(DS_InProcess, STS_MCRelayCheck_4);
						break;
					case STS_MCRelayCheck_4:
						CONTROL_SetDeviceState(DS_InProcess, STS_InputRelayOpenCheck_1);
						break;

					default:
						break;
				}
			}
			break;

		case STS_InputRelayOpenCheck_1:
			PrevSubstate = STS_InputRelayOpenCheck_1;

			TestIndex = 0;
			SelectedTestArray = (uint8_t *)TestCommutation_IR1;
			SelectedTestArrayLength = sizeof(TestCommutation_IR1);

			CONTROL_SetDeviceState(DS_InProcess, STS_OpenRelayCheck);
			break;

		case STS_InputRelayOpenCheck_2:
			PrevSubstate = STS_InputRelayOpenCheck_2;

			TestIndex = 0;
			SelectedTestArray = (uint8_t *)TestCommutation_IR2;
			SelectedTestArrayLength = sizeof(TestCommutation_IR2);

			CONTROL_SetDeviceState(DS_InProcess, STS_OpenRelayCheck);
			break;

		case STS_InputRelayOpenCheck_3:
			PrevSubstate = STS_InputRelayOpenCheck_3;

			TestIndex = 0;
			SelectedTestArray = (uint8_t *)TestCommutation_IR3;
			SelectedTestArrayLength = sizeof(TestCommutation_IR3);

			CONTROL_SetDeviceState(DS_InProcess, STS_OpenRelayCheck);
			break;

		case STS_InputRelayOpenCheck_4:
			PrevSubstate = STS_InputRelayOpenCheck_4;

			TestIndex = 0;
			SelectedTestArray = (uint8_t *)TestCommutation_IR4;
			SelectedTestArrayLength = sizeof(TestCommutation_IR4);

			CONTROL_SetDeviceState(DS_InProcess, STS_OpenRelayCheck);
			break;


		case STS_OpenRelayCheck:
			if(TestIndex < SelectedTestArrayLength)
			{
				// ��������� ���� ����
				for(uint8_t i = 0; i < SelectedTestArrayLength; i++)
					ZcRD_OutputValuesCompose(SelectedTestArray[i], TRUE);

				// ���������� ������������ ����
				ZcRD_OutputValuesCompose(SelectedTestArray[TestIndex], FALSE);
				ZcRD_RegisterFlushWrite();

				// ������������
				if(LL_OpenRelayFailed())
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					DataTable[REG_SELF_TEST_FAILED_SS] = PrevSubstate;
					DataTable[REG_SELF_TEST_FAILED_RELAY] = SelectedTestArray[TestIndex];
					ZcRD_RegisterReset();
					CONTROL_SwitchToFault(DF_RELAY_SHORT);
				}
				TestIndex++;
			}
			else
			{
				switch(PrevSubstate)
				{
					case STS_InputRelayOpenCheck_1:
						CONTROL_SetDeviceState(DS_InProcess, STS_InputRelayOpenCheck_2);
						break;

					case STS_InputRelayOpenCheck_2:
						CONTROL_SetDeviceState(DS_InProcess, STS_InputRelayOpenCheck_3);
						break;

					case STS_InputRelayOpenCheck_3:
						CONTROL_SetDeviceState(DS_InProcess, STS_InputRelayOpenCheck_4);
						break;

					case STS_InputRelayOpenCheck_4:
						DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
						ZcRD_RegisterReset();
						CONTROL_SetDeviceState(DS_Ready, STS_None);
						break;

					default:
						break;
				}
			}
			break;

		default:
			break;
	}
}
//-----------------------------------------------
