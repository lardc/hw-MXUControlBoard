// Header
//
#include "SelfTest.h"

// Includes
//
#include "Controller.h"
#include "DataTable.h"
#include "Delay.h"
#include "LowLevel.h"
#include "CommutationTable.h"
#include "ZcRegistersDriver.h"
#include "Commutator.h"

// Types
typedef enum __CheckRelayStages
{
	CRS_Init,
	CRS_CheckClosedCircuit,
	CRS_RelaySwitch,
	CRS_Finish
} CheckRelayStages;
typedef enum __SelfTestProcess
{
	STP_InProcess,
	STP_Finished,
	STP_FailedClosedCheck,
	STP_FailedOpenedCheck
} SelfTestProcess;

// Macro
#define SELFTEST_RelayCheck_macro(arr, failed_pointer) \
	SELFTEST_RelayCheck((arr), sizeof(arr) / sizeof((arr)[0]), failed_pointer)

// Variables
//
CheckRelayStages RelayStages = CRS_Init;

const Int8U SelfTestInputBoard[] = {GT_G_COMM, GT_G_COMM};

// Functions prototypes
//
SelfTestProcess SELFTEST_RelayCheck(const Int8U *RelaysArray, Int8U RelaysArrayCounter, pInt8U FailedIndex);
void SELFTEST_HandleFail(SelfTestProcess State, Int8U FailedIndex);
void SELFTEST_SwitchToNextState(SelfTestProcess CheckState, DeviceSelfTestState NextState, Int8U FailedIndex);

// Functions
//
void SELFTEST_Process()
{
	Int8U FailedIndex = 0;
	SelfTestProcess SelfTestState;

	if(CONTROL_State == DS_InSelfTest)
	{
		switch(CONTROL_SubState)
		{
			case STS_Start:
				RelayStages = CRS_Init;
				LL_SelfTestCurrentEnable(true);
				CONTROL_SetDeviceSubState(STS_InputBoard);
				break;

			case STS_InputBoard:
				SelfTestState = SELFTEST_RelayCheck_macro(SelfTestInputBoard, &FailedIndex);
				SELFTEST_SwitchToNextState(SelfTestState, STS_ThermBoard, FailedIndex);
				break;

			case STS_ThermBoard:
				/* дописать для этой и других плат */
				break;

			case STS_Finish:
				LL_SelfTestCurrentEnable(false);
				CONTROL_SetDeviceState(DS_Enabled);
				CONTROL_SetDeviceSubState(STS_None);
				break;

			default:
				break;
		}
	}
}
//-----------------------------------------------

void SELFTEST_SwitchToNextState(SelfTestProcess CheckState, DeviceSelfTestState NextState, Int8U FailedIndex)
{
	if(CheckState == STP_Finished)
		CONTROL_SetDeviceSubState(NextState);
	else if(CheckState != STP_InProcess)
		SELFTEST_HandleFail(CheckState, FailedIndex);
}
//-----------------------------------------------

void SELFTEST_HandleFail(SelfTestProcess State, Int8U FailedIndex)
{
	DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
	DataTable[REG_SELF_TEST_FAILED_STATE] = State;
	DataTable[REG_SELF_TEST_FAILED_RELAY] = FailedIndex;
	CONTROL_SwitchToFault(DF_SELF_TEST);
}
//-----------------------------------------------

SelfTestProcess SELFTEST_RelayCheck(const Int8U *RelaysArray, Int8U RelaysArrayCounter, pInt8U FailedIndex)
{
	static Int8U TestCounter = 0;
	static SelfTestProcess Result = STP_Finished;

	switch(RelayStages)
	{
		case CRS_Init:
			ZcRD_OutputValuesReset();
			COMM_ComposeDisconnectPE();
			Result = STP_Finished;

			// Замыкание всех реле контура
			for(int i = 0; i < RelaysArrayCounter; i++)
				ZcRD_OutputValuesCompose(RelaysArray[i], true);
			ZcRD_RegisterFlushWrite();

			RelayStages = CRS_CheckClosedCircuit;
			break;

		case CRS_CheckClosedCircuit:
			if(GetTestVoltage() > DataTable[REG_SFTST_CLOSED_MAX_VOLTAGE])
			{
				Result = STP_FailedClosedCheck;
				RelayStages = CRS_Finish;
				if(FailedIndex)
					*FailedIndex = 0xFF;
			}
			else
			{
				RelayStages = CRS_RelaySwitch;
				TestCounter = 0;
			}
			break;

		case CRS_RelaySwitch:
			if(TestCounter < RelaysArrayCounter)
			{
				ZcRD_OutputValuesCompose(RelaysArray[TestCounter], false);
				ZcRD_RegisterFlushWrite();

				if(GetTestVoltage() < DataTable[REG_SFTST_OPENED_MIN_VOLTAGE])
				{
					Result = STP_FailedOpenedCheck;
					RelayStages = CRS_Finish;
					if(FailedIndex)
						*FailedIndex = RelaysArray[TestCounter];
				}
				else
				{
					ZcRD_OutputValuesCompose(RelaysArray[TestCounter], true);
					TestCounter++;
				}
			}
			else
				RelayStages = CRS_Finish;
			break;

		case CRS_Finish:
			ZcRD_OutputValuesReset();
			ZcRD_RegisterFlushWrite();
			return Result;
	}

	return STP_InProcess;
}
//-----------------------------------------------
