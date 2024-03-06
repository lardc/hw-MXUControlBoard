#ifndef CONTROLLER_SELFTESTRELAYSARRAYS_H_
#define CONTROLLER_SELFTESTRELAYSARRAYS_H_

// Include
//
#include "CommutationTable.h"

// Types
//
typedef enum __RelayTypes
{
	RT_NormalClosed		= 0,
	RT_NormalOpened		= 1
} RelayTypes;

typedef struct __SelfTestTableItem
{
	Int16U Stage;
	Int16U Relay;
	RelayTypes Type;
} SelfTestTableItem;

// Definitions
//
#define ST_INPUT_BOARD_STAGES	4
#define ST_THERM_BOARD_STAGES	2
#define ST_HV_BOARD_STAGES		4

//
#define ST_INPUT_BOARD_COMM		20
#define ST_THERM_BOARD_COMM		16
#define ST_HV_BOARD_COMM		56
//

#define ST_STAGE0				0
#define ST_STAGE1				1
#define ST_STAGE2				2
#define ST_STAGE3				3

// Arrays
//
extern const SelfTestTableItem SelfTestInputBoard[ST_INPUT_BOARD_COMM];
extern const SelfTestTableItem SelfTestThermBoard[ST_THERM_BOARD_COMM];
extern const SelfTestTableItem SelfTestHV1Board[ST_HV_BOARD_COMM];
extern const SelfTestTableItem SelfTestHV2Board[ST_HV_BOARD_COMM];

#endif /* CONTROLLER_SELFTESTRELAYSARRAYS_H_ */
