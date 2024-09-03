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

typedef enum __DevType
{
	SC_Type_A2 = 1001,
	SC_Type_B1 = 1006,
	SC_Type_C1 = 1002,
	SC_Type_D0 = 1005,
	SC_Type_E0 = 1003,
	SC_Type_F1 = 1004,
	SC_Type_ADAP = 1007,
	SC_Type_E2M = 1008,
//
	SC_Type_MIAA = 2001,
	SC_Type_MIDA = 2002,
	SC_Type_MIFA = 2003,
	SC_Type_MIHA = 2004,
	SC_Type_MIHM = 2005,
	SC_Type_MIHV = 2006,
	SC_Type_MISM = 2007,
	SC_Type_MISV = 2008,
	SC_Type_MIXM = 2009,
	SC_Type_MIXV = 2010,
	// 2011
	SC_Type_MISM2_CH = 2012,
	SC_Type_MISM2_SS_SD = 2014,
	SC_Type_MIADAP = 2015
} DevType;

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
