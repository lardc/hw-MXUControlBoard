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
	DS_InProcess = 4,
	DS_SelfTest = 5
} DeviceState;

typedef enum __DeviceSubState
{
	SS_None = 0,

	SS_ST_StartPrepare,
	SS_ST_InputRelayCheck_1,
	SS_ST_InputRelayCheck_2,
	SS_ST_InputRelayCheck_3,
	SS_ST_InputRelayCheck_4,
	SS_ST_MCRelayCheck_1,
	SS_ST_MCRelayCheck_2,
	SS_ST_MCRelayCheck_3,
	SS_ST_MCRelayCheck_4,
	SS_ST_CurrentMeasure
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
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState);
void CONTROL_SetDeviceSubState(DeviceSubState NewSubState);

#endif // __CONTROLLER_H
