#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
#include "stdinc.h"
#include "Global.h"

// Types
//
typedef enum __DeviceState
{
	DS_None = 0,
	DS_Fault = 1,
	DS_Disabled = 2,
	DS_Ready = 3,
	DS_SelfTest = 4,
	DS_InProcess = 5
} DeviceState;

typedef enum __DeviceSubState
{
	SS_None = 0,
	SS_StartUp = 1,
	SS_WaitDelay = 2,
	SS_StartSelfTest = 3,
	SS_SelfTestCheck = 4,

	SS_ST_StartPrepare = 5,
	SS_ST_InputRelayCheck_1 = 6,
	SS_ST_InputRelayCheck_2 = 7,
	SS_ST_InputRelayCheck_3 = 8,
	SS_ST_InputRelayCheck_4 = 9,
	SS_ST_MCRelayCheck_1 = 10,
	SS_ST_MCRelayCheck_2 = 11,
	SS_ST_MCRelayCheck_3 = 12,
	SS_ST_MCRelayCheck_4 = 13,
	SS_ST_CurrentMeasure = 14,
	SS_ST_InputRelayOpenCheck_1 = 15,
	SS_ST_InputRelayOpenCheck_2 = 16,
	SS_ST_InputRelayOpenCheck_3	= 17,
	SS_ST_InputRelayOpenCheck_4	= 18,
	SS_ST_MCRelayOpenCheck_1 = 19,
	SS_ST_MCRelayOpenCheck_2 = 20,
	SS_ST_MCRelayOpenCheck_3 = 21,
	SS_ST_MCRelayOpenCheck_4 = 22,
	SS_ST_Get_ArrayLenght = 25,
	SS_ST_OpenRelayCheck = 26

} DeviceSubState;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSubState CONTROL_SubState;
extern Int64U CONTROL_LEDTimeout;


// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SaveTestResult();
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState);
void CONTROL_SetDeviceSubState(DeviceSubState NewSubState);
void CONTROL_ResetToDefaultState();
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_LogicProcess();
void CONTROL_UpdateWatchDog();
void CONTROL_ResetOutputRegisters();
void CONTROL_CommutateNone();
void CONTROL_ResetSFSystem();

#endif // __CONTROLLER_H
