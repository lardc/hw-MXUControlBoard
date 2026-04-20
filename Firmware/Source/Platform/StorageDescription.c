// Header
#include "StorageDescription.h"
#include "Global.h"

// Variables
RecordDescription StorageDescription[] = {};

#define SIZE_OF_POINTERS (sizeof(StorageDescription) / sizeof(StorageDescription[0]))
Int32U TablePointers[SIZE_OF_POINTERS ? SIZE_OF_POINTERS : 1] = {0};
const Int16U StorageSize = SIZE_OF_POINTERS;

// 64 счётчика соответствуют 64-слотной CommutationTable[].
// Расположение: 0..31 — IORelayBoard, 32..39 — OutThermRelayBoard, 40..63 — InputRelayBoard.
CounterDescription CounterStorageDescription[] =
{
	// ===== IORelayBoard (SS3, объединение прежних OutHVRelayBoard-1/2) =====
	{"0. Collector (C_POT) to PE"},
	{"1. Gate (G) to PE"},
	{"2. Gate-Emitter (GE) to PE"},
	{"3. Emitter (E_POT) to PE"},
	{"4. Collector: Commutation of C_POT (Open/Close)"},
	{"5. Gate: Commutation of G (Open/Close)"},
	{"6. Gate-Emitter: Commutation of GE (Open/Close)"},
	{"7. Emitter: Commutation of E_POT (Open/Close)"},
	{"8. Gate (G) to Collector (C_POT)"},
	{"9. Gate (G) to Gate-Emitter (GE)"},
	{"10. Gate-Emitter (GE) to GT_G"},
	{"11. Gate-Emitter (GE) to GT_GE"},
	{"12. Gate-Emitter (GE) to LSL_GE"},
	{"13. Gate (G) to GT_G"},
	{"14. Gate (G) to GT_GE"},
	{"15. Gate (G) to GT_G_POT"},
	{"16. Emitter (E_POT) to GT_GE_POT"},
	{"17. Emitter (E_POT) to LSL_POT+"},
	{"18. Emitter (E_POT) to LSL_POT-"},
	{"19. Gate (G) to LSL_G"},
	{"20. Collector (C_POT) to LSL_POT+"},
	{"21. Collector (C_POT) to LSL_POT-"},
	{"22. IO reserved"},
	{"23. IO reserved"},
	{"24. IO reserved"},
	{"25. IO reserved"},
	{"26. IO reserved"},
	{"27. IO reserved"},
	{"28. IO reserved"},
	{"29. IO reserved"},
	{"30. IO reserved"},
	{"31. IO reserved"},
	// ===== OutThermRelayBoard (SS2) =====
	{"32. Thermistor_1 (T1) to PE"},
	{"33. Thermistor_2 (T2) to PE"},
	{"34. Thermistor_1: Commutation of T1 (Open/Close)"},
	{"35. Thermistor_2: Commutation of T2 (Open/Close)"},
	{"36. T2 to GT_G"},
	{"37. T2 to GT_G_POT"},
	{"38. T1 to GT_GE"},
	{"39. T1 to GT_GE_POT"},
	// ===== InputRelayBoard (SS1) =====
	{"40. GT_G to TEST-IN"},
	{"41. GT_GE to TEST-OUT"},
	{"42. GT_G: Commutation of GT_G (Open/Close)"},
	{"43. GT_GE: Commutation of GT_GE (Open/Close)"},
	{"44. GT_G to GT_GE"},
	{"45. GT_G_POT to TEST-IN"},
	{"46. GT_GE_POT to TEST-OUT"},
	{"47. GT_G_POT: Commutation of GT_G_POT (Open/Close)"},
	{"48. GT_GE_POT: Commutation of GT_GE_POT (Open/Close)"},
	{"49. GT_G_POT to GT_GE_POT"},
	{"50. LSL_G to TEST-IN"},
	{"51. LSL_GE to TEST-OUT"},
	{"52. LSL_G: Commutation of LSL_G (Open/Close)"},
	{"53. LSL_GE: Commutation of LSL_GE (Open/Close)"},
	{"54. LSL_G to LSL_GE"},
	{"55. LSL_POT+ to TEST-IN"},
	{"56. LSL_POT- to TEST-OUT"},
	{"57. LSL_POT+: Commutation of LSL_POT+ (Open/Close)"},
	{"58. LSL_POT-: Commutation of LSL_POT- (Open/Close)"},
	{"59. LSL_POT+ to LSL_POT-"},
	{"60. Input reserved"},
	{"61. Input reserved"},
	{"62. Input reserved"},
	{"63. Input reserved"}
};
CounterData CounterTablePointers[sizeof(CounterStorageDescription) / sizeof(CounterStorageDescription[0])] = {0};
const Int16U CounterStorageSize = sizeof(CounterStorageDescription) / sizeof(CounterStorageDescription[0]);
