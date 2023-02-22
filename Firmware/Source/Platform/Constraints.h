#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
//
#define SFTST_V_ALLOWED_ERR_MIN		0		//	(%)
#define SFTST_V_ALLOWED_ERR_MAX		20		//	(%)
#define SFTST_V_ALLOWED_ERR_DEF		10		//	(%)
#define PS_FIRST_START_TIME			10
//
#define NO							0
#define YES							1
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
