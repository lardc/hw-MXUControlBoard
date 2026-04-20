#ifndef CONTROLLER_SELFTEST_H_
#define CONTROLLER_SELFTEST_H_

// Include
#include "Board.h"
#include "stdinc.h"

// Types
//
typedef enum __CheckRelayStages
{
	CRS_Init = 0,
	CRS_StageConfig,
	CRS_RelaySwitching,
	CRS_IncStage,
	CRS_Finish

} CheckRelayStages;

typedef enum __SelfTestProcess
{
	STP_None = 0,
	STP_InProcess,
	STP_Finish,
	STP_Fault
}SelfTestProcess;

// Variables
//
extern CheckRelayStages RelayStages;

// Functions
//
void SELFTEST_Process();

#endif // CONTROLLER_SELFTEST_H_
