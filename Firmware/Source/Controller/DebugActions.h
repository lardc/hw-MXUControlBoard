#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"

// Functions
//
void DBACT_ToggleFPLed();
void DBACT_WriteSPI();
void DBACT_SelfTestMeasure();
void DBACT_SDEN();
// Импульс SFT_ENABLE (перевод OE сдвиговых регистров в high-Z на 1 с)
void DBACT_SftEnablePulse();
// Прочитать состояние входа SFT_IN в REG_DBG (1 = сработала аппаратная защита)
void DBACT_ReadSftIn();

#endif //__DEBUGACTIONS_H
