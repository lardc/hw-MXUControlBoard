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
	COMM_Qg,
	COMM_Ucesat,
	COMM_Uf,
	COMM_Ices,
	COMM_Thermistor

} CommutationState;

// Variables
//
extern CommutationState COMM_State;

// Functions
//
void COMM_DisconnectPE();
void COMM_Commutate(Int16U ActionID);
void COMM_Default();

#endif // __COMMUTATOR_H
