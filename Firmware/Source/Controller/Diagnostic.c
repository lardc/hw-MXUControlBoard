// Header
#include "Diagnostic.h"

// Includes
#include "DataTable.h"
#include "LowLevel.h"
#include "Controller.h"
#include "DebugActions.h"

// Functions
bool DIAG_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
{
	switch (ActionID)
	{
	case ACT_DBG_BOARD_LED:
		DBACT_ToggleBoardLED();
		break;

	case ACT_DBG_FP_LED:
		DBACT_SetStateFP_LED();
		break;

	case ACT_DBG_SF_RED_LED:
		DBACT_SF_RED_LED();
		break;

	case ACT_DBG_SF_GRN_LED:
		DBACT_SF_GRN_LED();
		break;

	case ACT_DBG_SPI_WRITE:
		DBACT_SPI_WRITE();
		break;

	case ACT_DBG_STOP_COMMUTATION:
		DBACT_SPI_STOP_COMMUTATION();
		break;

	case ACT_DBG_ADC_MEASURE_OC:
		DBACT_ADC_MEASURE_OPEN_CURCUIT();
		break;

		default:
			return false;
	}

	return true;
}
//-------------------------------------
