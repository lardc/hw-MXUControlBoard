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

// Functions prototypes
//
bool SELFTEST_RelayCheck(const SelfTestTableItem (*RelayArray)[], Int16U Stages, Int16U Commutations, pFloat32 RelayErrorReg);
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

			if(!SELFTEST_RelayCheck(&SelfTestInputBoard, ST_INPUT_BOARD_STAGES, ST_INPUT_BOARD_COMM, (pFloat32)&DataTable[REG_SELF_TEST_FAILED_RELAY]))
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_BOARD] = STS_InputBoard;
				CONTROL_SwitchToFault(DF_SELF_TEST);
			}
			else
				CONTROL_SetDeviceSubState(STS_ThermBoard);
			break;

		case STS_ThermBoard:
			if(!SELFTEST_RelayCheck(&SelfTestThermBoard, ST_THERM_BOARD_STAGES, ST_THERM_BOARD_COMM, (pFloat32)&DataTable[REG_SELF_TEST_FAILED_RELAY]))
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_BOARD] = STS_ThermBoard;
				CONTROL_SwitchToFault(DF_SELF_TEST);
			}
			else
				CONTROL_SetDeviceSubState(STS_HVBoard1);
			break;

		case STS_HVBoard1:
			if(!SELFTEST_RelayCheck(&SelfTestHV1Board, ST_HV_BOARD_STAGES, ST_HV_BOARD_COMM, (pFloat32)&DataTable[REG_SELF_TEST_FAILED_RELAY]))
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_BOARD] = STS_HVBoard1;
				CONTROL_SwitchToFault(DF_SELF_TEST);
			}
			else
				CONTROL_SetDeviceSubState(STS_HVBoard2);
			break;

		case STS_HVBoard2:
			if(!SELFTEST_RelayCheck(&SelfTestHV2Board, ST_HV_BOARD_STAGES, ST_HV_BOARD_COMM, (pFloat32)&DataTable[REG_SELF_TEST_FAILED_RELAY]))
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
				DataTable[REG_SELF_TEST_FAILED_BOARD] = STS_HVBoard2;
				CONTROL_SwitchToFault(DF_SELF_TEST);
			}
			else
			{
				LL_SetStateSD_EN(false);

				CONTROL_SetDeviceState(DS_Enabled);
				CONTROL_SetDeviceSubState(STS_None);
			}
			break;

		default:
			CONTROL_SubState = STS_InputBoard;
			break;
		}
	}
}
//-----------------------------------------------

bool SELFTEST_RelayCheck(const SelfTestTableItem (*RelayArray)[], Int16U Stages, Int16U Commutations, pFloat32 RelayErrorReg)
{
	float RelayClosedTestCurrent = 0, RelayOpenedTestCurrent = 0;

	ZcRD_OutputValuesReset();
	COMM_DisconnectPE();

	for(int i = 0; i < Stages; i++)
	{
		// Open all relays
		for(int j = 0; j < Commutations; j++)
			SELFTEST_RelayClose((*RelayArray)[j], false);

		for(int j = 0; j < Commutations; j++)
		{
			// Close all relays in current stage
			if((*RelayArray)[j].Stage == i)
				SELFTEST_RelayClose((*RelayArray)[j], true);
		}
		DELAY_MS(COMM_DELAY_MS);

		// Switching each relay and checking the test current
		//
		for(int j = 0; j < Commutations; j++)
		{
			if((*RelayArray)[j].Stage == i)
			{
				RelayClosedTestCurrent = GetTestCurrent();

				SELFTEST_RelayClose((*RelayArray)[j], false);
				DELAY_MS(COMM_DELAY_MS);

				RelayOpenedTestCurrent = GetTestCurrent();

				SELFTEST_RelayClose((*RelayArray)[j], true);
				DELAY_MS(COMM_DELAY_MS);

				if(fabs(RelayClosedTestCurrent - RelayOpenedTestCurrent) < DataTable[REG_SFTST_V_ALLOWED_VOLTAGE])
				{
					*RelayErrorReg = j;
					return false;
				}


			}
		}
		ZcRD_OutputValuesReset();
		COMM_DisconnectPE();
	}

	ZcRD_OutputValuesReset();
	ZcRD_RegisterFlushWrite();

	*RelayErrorReg = 0;

	return true;
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
