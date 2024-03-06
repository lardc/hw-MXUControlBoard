#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
#include "stdinc.h"
#include "Global.h"
#include "Commutator.h"

// Types
//
typedef enum __DeviceState
{
	DS_None				= 0,
	DS_Fault			= 1,
	DS_Disabled			= 2,
	DS_Enabled			= 3,
	DS_SafetyActive		= 4,
	DS_SafetyTrig		= 5,
	DS_InSelfTest		= 6
} DeviceState;

typedef enum __DeviceSelfTestState
{
	STS_None = 0,
	STS_InputBoard,
	STS_ThermBoard,
	STS_HVBoard1,
	STS_HVBoard2

} DeviceSelfTestState;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSelfTestState CONTROL_SubState;
extern Int64U CONTROL_LEDTimeout;

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SaveTestResult();
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_SetDeviceSubState(DeviceSelfTestState NewSubState);
void CONTROL_ResetToDefaultState();
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_LogicProcess();
void CONTROL_UpdateWatchDog();
void CONTROL_ResetOutputRegisters();
void CONTROL_HandleFrontPanelLamp(CommutationState Commutation);

#endif // __CONTROLLER_H
