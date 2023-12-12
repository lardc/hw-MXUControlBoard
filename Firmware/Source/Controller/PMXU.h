#ifndef CONTROLLER_PMXU_H_
#define CONTROLLER_PMXU_H_

// Includes
//
#include "stdinc.h"

// Types
//
typedef enum __PMXUState
{
	PS_None				= 0,
	PS_Fault			= 1,
	PS_Disabled			= 2,
	PS_Enabled			= 3,
	PS_SafetyActive		= 4,
	PS_SafetyTrig		= 5,
	PS_InSelfTest		= 6,
	PS_InProcess		= 7
} PMXUState;

// Functions
//
bool PMXU_IsReady();
bool PMXU_InFault();
bool PMXU_ClearFault();
bool PMXU_ClearWarning();
bool PMXU_SwitchCommutation(Int16U Position, Int16U CommutationNumber);
bool PMXU_Enable();
bool PMXU_Disable();
bool PMXU_CheckState(PMXUState State);
bool PMXU_SafetyActivate();
bool PMXU_SafetyDeactivate();

#endif /* CONTROLLER_PMXU_H_ */
