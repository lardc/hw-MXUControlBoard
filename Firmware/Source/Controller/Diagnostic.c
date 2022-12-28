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
	case ACT_DBG_FP_LED:
		DBACT_ToggleFPLed();
		break;

	case ACT_DBG_SF_RED_LED:
		DBACT_ToggleSFRedLed();
		break;

	case ACT_DBG_SF_GRN_LED:
		DBACT_ToggleSFGreenLed();
		break;

	case ACT_DBG_WRITE_SPI:
		DBACT_WriteSPI();
		break;

	case ACT_DBG_SPI_PE_OFF:
		DBACT_SPI_PE_OFF();
		break;

	case ACT_DGB_SPI_ILEAK_G_EMIT_POS:
		DBACT_SPI_Ileak_Gate_Emit_Pos();
		break;

	case ACT_DGB_SPI_ILEAK_G_EMIT_NEG:
		DBACT_SPI_Ileak_Gate_Emit_Neg();
		break;

	case ACT_DBG_STOP_SPI:
		DBACT_StopSPI();
		break;

	case ACT_DBG_SPI_OE_ON:
		DBACT_SPITurnOnOE();
		break;

	case ACT_DBG_SPI_OE_OFF:
		DBACT_SPITurnOffOE();
		break;

	case ACT_DBG_SPI_SS_ON:
		DBACT_SPITurnOnSS();
		break;

	case ACT_DBG_SPI_SS_OFF:
		DBACT_SPITurnOffSS();
		break;

	case ACT_DBG_SPI_RST:
		DBACT_SPIReset();
		break;

	case ACT_SF_EN_ON:
		DBACT_TurnONSF_EN();
		break;

	case ACT_SF_EN_OFF:
		DBACT_TurnOFFSF_EN();
		break;

	case ACT_DBG_SD_EN_OFF:
		DBACT_TurnOFFSD_EN();
		break;

	case ACT_DBG_SD_EN_ON:
		DBACT_TurnONSD_EN();
		break;

	case ACT_DBG_SELF_TEST_MEASURE:
		DBACT_SelfTestMeasure();
		break;

		default:
			return false;
	}

	return true;
}
//-------------------------------------
