#ifndef CONTROLLER_PMXU_H_
#define CONTROLLER_PMXU_H_

// Includes
//
#include "stdinc.h"

// Types
//
typedef enum __PMXUState
{
	PS_None = 0,
	PS_Fault = 1,
	PS_Disabled = 2,
	PS_Ready = 3,
	PS_InProcess = 4
} PMXUState;

// Functions
//
bool PMXU_IsReady();
bool PMXU_InFault();
bool PMXU_ClearFault();
bool PMXU_ClearWarning();
bool PMXU_SwitchCommutation(Int16U CommutationNumber);
bool PMXU_Enable();
bool PMXU_Disable();

#endif /* CONTROLLER_PMXU_H_ */
