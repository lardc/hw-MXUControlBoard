#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
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
	STS_IOBoard

} DeviceSelfTestState;

typedef enum __DevType
{
	SC_Type_MIAA = 3001,
	SC_Type_MIDA = 3002,
	SC_Type_MIFA = 3003,
	SC_Type_MIHA = 3004,
	SC_Type_MIHM = 3005,
	SC_Type_MIHV = 3006,
	SC_Type_MISM = 3007,
	SC_Type_MISV = 3008,
	SC_Type_MIXM = 3009,
	SC_Type_MIXV = 3010,
	// 2011
	SC_Type_MISM2_CH = 3012,
	// 2013
	SC_Type_MISM2_SS_SD = 3014,
	SC_Type_MIADAP = 3015,
	SC_Type_MDAA = 3016,
	SC_Type_MDFA_MDF2_DD = 3017,
	SC_Type_MDSM = 3018,
	SC_Type_MDSV = 3019,
	SC_Type_MDFA_MDF2_SD = 3020,
	SC_Type_MDA2 = 3021
} DevType;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSelfTestState CONTROL_SubState;
extern Int64U CONTROL_LEDTimeout;
extern volatile Int16U CONTROL_DiagCounter;
//
extern volatile float CONTROL_DiagData[VALUES_DIAG_SIZE];

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
void CONTROL_SafetyIrqTick();

#endif // __CONTROLLER_H
