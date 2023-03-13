#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
//
#define REG_SFTST_V_ALLOWED_VOLTAGE_MIN		150		//	в мВ
#define REG_SFTST_V_ALLOWED_VOLTAGE_MAX		200		//	в мВ
#define PS_FIRST_START_TIME					10
//
#define NO									0
#define YES									1
//

// Types
typedef struct __TableItemConstraint
{
	float Min;
	float Max;
	float Default;
} TableItemConstraint;

// Variables
extern const TableItemConstraint Constraint[];

#endif // __CONSTRAINTS_H
