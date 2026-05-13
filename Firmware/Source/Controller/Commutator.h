// -----------------------------------------
// Commutation controller
// ----------------------------------------

#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Include
#include "stdinc.h"

// Types
//
typedef enum __CommutationState
{
	COMM_Def		= 0,
	COMM_NoPE,
	COMM_Iges_Pos,
	COMM_Iges_Neg,
	COMM_Ugeth,
	COMM_Ucesat,
	COMM_Uf,
	COMM_IcesOrIrrm,
	COMM_Thermistor

} CommutationState;

// Variables
//
extern CommutationState COMM_State;

// Functions
//
void COMM_ConnectToGND();
void COMM_Commutate(Int16U ActionID);
void COMM_Default();
bool COMM_ValidateRequest(Int16U ActionID, Int16U Position);
Int16U COMM_CalcModuleType();

#endif // __COMMUTATOR_H
