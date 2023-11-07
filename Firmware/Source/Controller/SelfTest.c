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


// Functions prototypes
//
bool SELFTEST_InputBoard(pFloat32 RelayCode);
bool SELFTEST_ThermBoard(pFloat32 RelayCode);
bool SELFTEST_HVBoard1(pFloat32 RelayCode);
bool SELFTEST_HVBoard2(pFloat32 RelayCode);
bool SELFTEST_CheckRelays(const Int16U *RelayArray, Int16U ArraySize, pFloat32 RelayCode);

// Functions
//
void SELFTEST_Process()
{
	if(CONTROL_State == DS_InSelfTest)
	{
		DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_NONE;
		DataTable[REG_SELF_TEST_FAILED_RELAY] = 0;
		CONTROL_HandleFrontPanelLamp(true);

		switch(CONTROL_SubState)
		{
		case STS_InputBoard:
			if(SELFTEST_InputBoard((float *)&DataTable[REG_SELF_TEST_FAILED_RELAY]))
				CONTROL_SetDeviceSubState(STS_ThermBoard);
			else
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
			break;

		case STS_ThermBoard:
			if(SELFTEST_ThermBoard((float *)&DataTable[REG_SELF_TEST_FAILED_RELAY]))
				CONTROL_SetDeviceSubState(STS_HVBoard1);
			else
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
			break;

		case STS_HVBoard1:
			if(SELFTEST_HVBoard1((float *)&DataTable[REG_SELF_TEST_FAILED_RELAY]))
				CONTROL_SetDeviceSubState(STS_HVBoard2);
			else
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
			break;

		case STS_HVBoard2:
			if(SELFTEST_HVBoard2((float *)&DataTable[REG_SELF_TEST_FAILED_RELAY]))
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;

				CONTROL_SetDeviceSubState(STS_None);
				CONTROL_SetDeviceState(DS_Enabled);
			}
			else
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
			break;

			default:
				break;
		}

		if(DataTable[REG_SELF_TEST_OP_RESULT] == OPRESULT_FAIL)
		{
			CONTROL_SetDeviceSubState(STS_None);
			CONTROL_SwitchToFault(DF_SELF_TEST);
		}
	}
}
//-----------------------------------------------

bool SELFTEST_InputBoard(pFloat32 RelayCode)
{
	for(int i = 0; i < ST_INPUT_BOARD_STAGES; i++)
	{
		if(!SELFTEST_CheckRelays(&SelfTestInputBoard[i][0], sizeof(SelfTestInputBoard[i]), RelayCode))
				return false;
	}

	return true;
}
//-----------------------------------------------

bool SELFTEST_ThermBoard(pFloat32 RelayCode)
{
	for(int i = 0; i < ST_THERM_BOARD_STAGES; i++)
	{
		if(!SELFTEST_CheckRelays(&SelfTestThermBoard[i][0], sizeof(SelfTestThermBoard[i]), RelayCode))
				return false;
	}

	return true;
}
//-----------------------------------------------

bool SELFTEST_HVBoard1(pFloat32 RelayCode)
{
	for(int i = 0; i < ST_HV_BOARD_STAGES; i++)
	{
		if(!SELFTEST_CheckRelays(&SelfTestHV1Board[i][0], sizeof(SelfTestHV1Board[i]), RelayCode))
				return false;
	}

	return true;
}
//-----------------------------------------------

bool SELFTEST_HVBoard2(pFloat32 RelayCode)
{
	for(int i = 0; i < ST_HV_BOARD_STAGES; i++)
	{
		if(!SELFTEST_CheckRelays(&SelfTestHV2Board[i][0], sizeof(SelfTestHV2Board[i]), RelayCode))
				return false;
	}

	return true;
}
//-----------------------------------------------

bool SELFTEST_CheckRelays(const Int16U *RelayArray, Int16U ArraySize, pFloat32 RelayCode)
{
	ZcRD_RegisterReset();

	// Вкл. все реле
	for(int i = 0; i < ArraySize; i++)
		ZcRD_OutputValuesCompose(*(RelayArray + i), true);
	ZcRD_RegisterFlushWrite();

	DELAY_MS(COMM_DELAY_MS);

	for(int i = 0; i < ArraySize; i++)
	{
		// Выкл. реле
		ZcRD_OutputValuesCompose(*(RelayArray + i), false);
		ZcRD_RegisterFlushWrite();
		DELAY_MS(COMM_DELAY_MS);

		if(LL_SelfTestMeasure() <= DataTable[REG_SFTST_V_ALLOWED_VOLTAGE])
		{
			*RelayCode = *(RelayArray + i);
			return false;
		}

		//Вкл. реле
		ZcRD_OutputValuesCompose(*(RelayArray + i), true);
		ZcRD_RegisterFlushWrite();
		DELAY_MS(COMM_DELAY_MS);

		if(LL_SelfTestMeasure() >= DataTable[REG_SFTST_V_ALLOWED_VOLTAGE])
		{
			*RelayCode = *(RelayArray + i);
			return false;
		}
	}
	return true;
}
//-----------------------------------------------
