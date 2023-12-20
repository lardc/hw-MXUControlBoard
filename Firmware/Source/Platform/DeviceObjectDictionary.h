#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER						1	// Включение блока
#define ACT_DISABLE_POWER						2	// Выключение блока
#define ACT_CLR_FAULT							3	// Очистка всех fault
#define ACT_CLR_WARNING							4	// Очистка всех warning
//
#define ACT_DBG_FP_LED							21	// Проверка работы индикатора на передней панели
#define ACT_DBG_SF_RED_LED						22	// Проверка работы красного индикатора системы безопасности
#define ACT_DBG_SF_GRN_LED						23	// Проверка работы зеленого индикатора системы безопасности
#define ACT_DBG_WRITE_SPI						24	// Проверка работы коммутации тестовой комбинации
#define ACT_DBG_SPI_RST							25	// Сброс сдвиговых регистров
#define ACT_DBG_SELF_TEST_MEASURE				26	// Измерение значения напряжение системы самодиагностики

#define ACT_SET_ACTIVE							100	// Команда активации контура безопасности
#define ACT_SET_INACTIVE						101	// Команда деактивации контура безопасности

#define ACT_COMM_NONE							110 // Отключение всех реле
#define ACT_COMM_IGES_POS_PULSE					111 // Режим измерения тока утечки затвора-эмиттера (положительный импульс)
#define ACT_COMM_IGES_NEG_PULSE					112 // Режим измерения тока утечки затвора-эмиттера (отрицательный импульс)
#define ACT_COMM_UGE_TH							113 // Режим измерения порогового напряжения затвор-эмиттер
#define ACT_COMM_QG								114 // Режим измерения заряда затвора (положительный импульс)
#define ACT_COMM_UCE_SAT						115 // Режим измерения напряжения насыщения коллектор-эмиттер
#define ACT_COMM_UFW_CHOPPER_DIODE				116 // Режим измерения прямого напряжения обратно-параллельного диода и диода чоппера
#define ACT_COMM_ICES							117 // Режим измерения тока утечки коллектор-эмиттер
#define ACT_COMM_THERMISTOR						118 // Режим измерения сопротивления термистора
#define ACT_COMM_NO_PE							119 // Отключения защитного заземления

#define ACT_SELFT_TEST							120	// Запуск режима самотестирования

#define ACT_SAVE_TO_ROM							200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM					201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT					202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST					320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------



// Регистры
// Сохраняемые регистры
#define REG_SFTST_V_ALLOWED_VOLTAGE				0	// Допустимое значение напряжения на замкнутом реле
#define REG_SAFETY_DELAY						1	// Задержка отключения коммутации, мс
#define REG_PMXU_CAN_ID							2	// PMXU CAN ID
#define REG_PMXU_EMULATED						3	// PMXU emulation

#define REG_MODULE_TYPE							70	// Module type(Заглушка)
#define REG_DUT_POSITION						71	// Регистр выбора позции тестируемого прибора (1 или 2)

#define REG_EN_SFTY_IN1							80	// Enable safety input #1(Заглушка)
#define REG_EN_SFTY_IN2							81	// Enable safety input #2(Заглушка)
#define REG_EN_SFTY_IN3							82	// Enable safety input #3(Заглушка)
#define REG_EN_SFTY_IN4							83	// Enable safety input #4(Заглушка)

//
#define REG_DEV_STATE							96	// Регистр состояния
#define REG_FAULT_REASON						97	// Регистр Fault
#define REG_DISABLE_REASON						98	// Регистр Disable
#define REG_WARNING								99	// Регистр Warning
#define REG_PROBLEM								100	// Регистр Problem
#define REG_OP_RESULT							101	// Регистр результата операции
#define REG_SELF_TEST_OP_RESULT					102	// Регистр результата самотестирования
#define REG_SUB_STATE							103	// Регистр вспомогательного состояния

// Несохраняемые регистры чтения-записи

#define REG_DBG									150	// Отладочный регистр

// Регистры только чтение

#define REG_SELF_TEST_ACTIVE					200	// Self-test state flag
#define REG_SELF_TEST_SS						201	// Self-test sub-state register

#define REG_SELF_TEST_FAILED_RELAY				210	// Номер коммутации на котором обнаружен отказ

#define REG_EXT_UNIT_ERROR_CODE					220	// Ошибка интерфейса PAU: код ошибки
#define REG_EXT_UNIT_FUNCTION					221	// Ошибка интерфейса PAU: код функции
#define REG_EXT_UNIT_EXT_DATA					222	// Ошибка интерфейса PAU: расширенная информация
// -----------------------------
#define REG_FWINFO_SLAVE_NID					256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID					257	// Device CAN master node ID (if presented)
#define REG_DEVICE_ID							258	// Device ID
// 259
#define REG_FWINFO_STR_LEN						260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN					261	// Begining of the information string record


// Operation results
#define OPRESULT_NONE							0	// No information or not finished
#define OPRESULT_OK								1	// Operation was successful
#define OPRESULT_FAIL							2	// Operation failed

//  Fault and disable codes
#define DF_NONE									0
#define DF_SELF_TEST							1	// Проблема реле
#define DF_PMXU_INTERFACE						2	// Проблема связи по интерфейсу с PMXU
#define DF_PMXU									3	// PMXU в состоянии Fault

// Problem
#define PROBLEM_NONE							0

//  Warning
#define WARNING_NONE							0

//  User Errors
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED					2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY					3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD							4	//  Неправильный ключ

// Endpoints



// PMXU actions
//
#define ACT_PMXU_ENABLE_POWER					1	// Включение блока
#define ACT_PMXU_DISABLE_POWER					2	// Выключение блока
#define ACT_PMXU_CLR_FAULT						3	// Очистка всех fault
#define ACT_PMXU_CLR_WARNING					4	// Очистка всех warning
//
#define ACT_PMXU_SET_ACTIVE						100	// Команда активации контура безопасности
#define ACT_PMXU_SET_INACTIVE					101	// Команда деактивации контура безопасности
//
#define ACT_PMXU_COMM_PE						110 // Отключение всех реле, замыкание шин на PE
#define ACT_PMXU_COMM_ICES						111 // Режим измерения тока утечки коллектор-эмиттер
#define ACT_PMXU_COMM_VCESAT					112 // Режим измерения напряжения насыщения коллектор-эмиттер IGBT транзисторов
#define ACT_PMXU_COMM_VF						113 // Режим измерения постоянного прямого напряжения диода чоппера и обратно-параллельного диода
#define ACT_PMXU_COMM_QG						114 // Режим измерения заряда затвора
#define ACT_PMXU_COMM_NO_PE						115 // Отключение всех реле
//

// PMXU registers
//
#define REG_PMXU_DUT_POSITION					128	// Регистр выбора позции тестируемого прибора (1 или 2)

#define REG_PMXU_DEV_STATE						192	// Регистр состояния
#define REG_PMXU_FAULT_REASON					193	// Регистр Fault
#define REG_PMXU_DISABLE_REASON					194	// Регистр Disable
#define REG_PMXU_WARNING						195	// Регистр Warning
//

// PMXU faults
//
#define DF_PMXU_NONE							0
#define DF_PMXU_PMXU_RELAY_SHORT				1	// Обнаружено залипшее реле
#define DF_PMXU_CHAIN_BREAK						2	// Обнаружен разрыв при прозвонке
#define DF_PMXU_CONTACTOR_COMMUTATION_FAULT		3	// Ошибка коммутации контакторов, номер неисправного контактора в регистре REG_PROBLEM
#define DF_PMXU_LOW_PRESSURE					4	// Низкое давление в пневмосистеме
#define DF_PMXU_SAFETY_ERROR					5	// Ошибка защитной цепи

// PMXU warnings
//
#define WARNING_PMXU_NONE						0
#define WARNING_PMXU_CONTACTORS_CHECK			1	// Требуется проверка контактных сопротивлений контакторов, номер контактора в регистре REG_PROBLEM

#endif //  __DEV_OBJ_DIC_H
