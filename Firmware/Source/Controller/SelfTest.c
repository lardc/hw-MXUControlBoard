// Header
//
#include "SelfTest.h"

// Includes
//
#include "Math.h"
#include "Logic.h"
#include "Controller.h"
#include "DataTable.h"
#include "Delay.h"
#include "LowLevel.h"
#include "CommutationTable.h"
#include "ZcRegistersDriver.h"

// Defines
//
#define ST_V_ALLOWED_ERR_DEF			 10	//	(%)

// Functions
//
void SELFTEST_Process()
{
	float MeasuredVoltage, Error;
	int ST_State = 0;

	switch(CONTROL_SubState)
	{
		case SS_ST_StartPrepare:
			ST_State = 0;
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_InputRelayCheck_1);
			break;

		case SS_ST_InputRelayCheck_1:
			ST_State = 1;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_G_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_CurrentMeasure);
			break;

		case SS_ST_InputRelayCheck_2:
			ST_State = 2;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_GT_G_POT_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_GE_POT_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_GT_G_GE_POT, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G_POT, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE_POT, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_CurrentMeasure);
			break;

		case SS_ST_InputRelayCheck_3:
			ST_State = 3;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_G_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_LSL_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_LSL_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_CurrentMeasure);
			break;

		case SS_ST_InputRelayCheck_4:
			ST_State = 4;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);
			ZcRD_OutputValuesCompose(IL_LSL_POTS, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_LSL_POTP, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_LSL_POTN, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_CurrentMeasure);
			break;

		case SS_ST_MCRelayCheck_1:
			ST_State = 5;

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
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_CurrentMeasure);
			break;

		case SS_ST_MCRelayCheck_2:
			ST_State = 6;

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
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_CurrentMeasure);
			break;

		case SS_ST_MCRelayCheck_3:
			ST_State = 7;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
			ZcRD_OutputValuesCompose(MC_G_GT_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_CurrentMeasure);
			break;

		case SS_ST_MCRelayCheck_4:
			ST_State = 8;

			ZcRD_OutputValuesReset();

			ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
			ZcRD_OutputValuesCompose(MC_G_2_GT_GE, TRUE);

			ZcRD_OutputValuesCompose(ST_TI_GT_G, TRUE);
			ZcRD_OutputValuesCompose(ST_TO_GT_GE, TRUE);

			ZcRD_RegisterFlushWrite();
			CONTROL_SetDeviceState(DS_SelfTest, SS_ST_CurrentMeasure);
			break;

		case SS_ST_CurrentMeasure:
			MeasuredVoltage = LL_SelfTestMeasure();

			Error = (MeasuredVoltage - ADC_V_CC) / ADC_V_CC * 100;

			if (Error >= ST_V_ALLOWED_ERR_DEF)
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				CONTROL_SwitchToFault(DF_VOLTAGE_MEASURING);
			}
			else
			{
				if (ST_State == 1)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_SelfTest, SS_ST_InputRelayCheck_2);
				}
				else if (ST_State == 2)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_SelfTest, SS_ST_InputRelayCheck_3);
				}
				else if (ST_State == 3)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_SelfTest, SS_ST_InputRelayCheck_4);
				}
				else if (ST_State == 4)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_SelfTest, SS_ST_MCRelayCheck_1);
				}
				else if (ST_State == 5)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_SelfTest, SS_ST_MCRelayCheck_2);
				}
				else if (ST_State == 6)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_SelfTest, SS_ST_MCRelayCheck_3);
				}
				else if (ST_State == 7)
				{
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
					CONTROL_SetDeviceState(DS_SelfTest, SS_ST_MCRelayCheck_4);
				}
			}

			break;

		default:
			break;
	}
}
//-----------------------------------------------
