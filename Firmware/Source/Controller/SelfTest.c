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
#include "SelfTestRelaysArrays.h"
#include "Commutator.h"

// Variables
//
CheckRelayStages RelayStages = CRS_Init;
SelfTestProcess SelfTestState = STP_None;

// Functions prototypes
//
SelfTestProcess SELFTEST_RelayCheck(const SelfTestTableItem (*RelayArray)[], Int16U Stages, Int16U Commutations, pFloat32 RelayErrorReg);
void SELFTEST_RelayClose(SelfTestTableItem Relay, bool State);

// Functions
//
void SELFTEST_Process()
{
	if(CONTROL_State == DS_InSelfTest)
	{
		switch(CONTROL_SubState)
		{
		case STS_InputBoard:
			LL_SetStateSD_EN(true);

			SelfTestState = SELFTEST_RelayCheck(&SelfTestInputBoard, ST_INPUT_BOARD_STAGES, ST_INPUT_BOARD_COMM, (pFloat32)&DataTable[REG_SELF_TEST_FAILED_RELAY]);

			if(SelfTestState == STP_Fault)
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_BOARD] = STS_InputBoard;
				CONTROL_SwitchToFault(DF_SELF_TEST);
			}
			else
				if(SelfTestState == STP_Finish)
					CONTROL_SetDeviceSubState(STS_ThermBoard);
			break;

		case STS_ThermBoard:
			SelfTestState = SELFTEST_RelayCheck(&SelfTestThermBoard, ST_THERM_BOARD_STAGES, ST_THERM_BOARD_COMM, (pFloat32)&DataTable[REG_SELF_TEST_FAILED_RELAY]);

			if(SelfTestState == STP_Fault)
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_BOARD] = STS_ThermBoard;
				CONTROL_SwitchToFault(DF_SELF_TEST);
			}
			else
				if(SelfTestState == STP_Finish)
					CONTROL_SetDeviceSubState(STS_HVBoard1);
			break;

		case STS_HVBoard1:
			SelfTestState = SELFTEST_RelayCheck(&SelfTestHV1Board, ST_HV_BOARD_STAGES, ST_HV_BOARD_COMM, (pFloat32)&DataTable[REG_SELF_TEST_FAILED_RELAY]);

			if(SelfTestState == STP_Fault)
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_BOARD] = STS_HVBoard1;
				CONTROL_SwitchToFault(DF_SELF_TEST);
			}
			else
				if(SelfTestState == STP_Finish)
					CONTROL_SetDeviceSubState(STS_HVBoard2);
			break;

		case STS_HVBoard2:
			SelfTestState = SELFTEST_RelayCheck(&SelfTestHV2Board, ST_HV_BOARD_STAGES, ST_HV_BOARD_COMM, (pFloat32)&DataTable[REG_SELF_TEST_FAILED_RELAY]);

			if(SelfTestState == STP_Fault)
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_BOARD] = STS_HVBoard2;
				CONTROL_SwitchToFault(DF_SELF_TEST);
			}
			else
			{
				if(SelfTestState == STP_Finish)
				{
					LL_SetStateSD_EN(false);

					CONTROL_SetDeviceState(DS_Enabled);
					CONTROL_SetDeviceSubState(STS_None);
				}
			}
			break;

		default:
			CONTROL_SubState = STS_InputBoard;
			break;
		}
	}
}
//-----------------------------------------------

SelfTestProcess SELFTEST_RelayCheck(const SelfTestTableItem (*RelayArray)[], Int16U Stages, Int16U Commutations, pFloat32 RelayErrorReg)
{
	float RelayClosedTestCurrent = 0, RelayOpenedTestCurrent = 0;
	static Int16U StageCounter = 0, CommutationCounter = 0;

	switch(RelayStages)
	{
		case CRS_Init:
			ZcRD_OutputValuesReset();
			COMM_DisconnectPE();

			RelayStages = CRS_StageConfig;
			break;

		case CRS_StageConfig:
			// Open all relays
			for(int j = 0; j < Commutations; j++)
				SELFTEST_RelayClose((*RelayArray)[j], false);

			for(int j = 0; j < Commutations; j++)
			{
				// Close all relays in current stage
				if((*RelayArray)[j].Stage == StageCounter)
					SELFTEST_RelayClose((*RelayArray)[j], true);
			}
			DELAY_MS(COMM_DELAY_MS);

			RelayStages = CRS_RelaySwitching;
			break;

		case CRS_RelaySwitching:
			// Switching each relay and checking the test current
			//
			if((*RelayArray)[CommutationCounter].Stage == StageCounter)
			{
				RelayClosedTestCurrent = GetTestCurrent();

				SELFTEST_RelayClose((*RelayArray)[CommutationCounter], false);
				DELAY_MS(COMM_DELAY_MS);

				RelayOpenedTestCurrent = GetTestCurrent();

				SELFTEST_RelayClose((*RelayArray)[CommutationCounter], true);
				DELAY_MS(COMM_DELAY_MS);

				if(fabs(RelayClosedTestCurrent - RelayOpenedTestCurrent) < DataTable[REG_SFTST_V_ALLOWED_VOLTAGE])
				{
					*RelayErrorReg = CommutationCounter;
					return STP_Fault;
				}
			}

			CommutationCounter++;

			if(CommutationCounter >= Commutations)
			{
				CommutationCounter = 0;
				RelayStages = CRS_IncStage;
			}
			break;

		case CRS_IncStage:
			ZcRD_OutputValuesReset();
			COMM_DisconnectPE();

			StageCounter++;

			if(StageCounter >= Stages)
				RelayStages = CRS_Finish;
			else
				RelayStages = CRS_StageConfig;
			break;

		case CRS_Finish:
			ZcRD_OutputValuesReset();
			ZcRD_RegisterFlushWrite();
			StageCounter = 0;
			CommutationCounter = 0;
			*RelayErrorReg = 0;
			RelayStages = CRS_Init;

			return STP_Finish;
			break;
	}

	return STP_InProcess;
}
//-----------------------------------------------

void SELFTEST_RelayClose(SelfTestTableItem Relay, bool State)
{
	if(Relay.Type == RT_NormalClosed)
		ZcRD_OutputValuesCompose(Relay.Relay, !State);
	else
		ZcRD_OutputValuesCompose(Relay.Relay, State);
	ZcRD_RegisterFlushWrite();
}
//-----------------------------------------------
