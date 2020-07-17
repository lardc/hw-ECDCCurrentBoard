#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Переход в состояние ожидания
#define ACT_DISABLE_POWER				2	// Отключение блока
#define ACT_START_PROCESS				3	// Страрт процесса формирования импульса
#define ACT_STOP_PROCESS				4	// Остановка процесса формирования импульса
#define ACT_FAULT_CLEAR					5	// Очистка fault
#define ACT_WARNING_CLEAR				6	// Очистка warning

#define ACT_DBG_IMPULSE_LED				10	// Импульсное включение внешней индикации
#define ACT_DBG_ENABLE_AMP11V			11	// Импульсное включение канала усиления напряжения DUT 11В
#define ACT_DBG_ENABLE_AMP1500MV		12	// Импульсное включение канала усиления напряжения DUT 1.5В
#define ACT_DBG_ENABLE_AMP250MV			13	// Импульсное включение канала усиления напряжения DUT 250мВ
#define ACT_DBG_ENABLE_AMP30MV			14	// Импульсное включение канала усиления напряжения DUT 30мВ
#define ACT_DBG_ENABLE_RNG20MA			15	// Импульсное включение реле шунта канала формирования тока до 20мА
#define ACT_DBG_ENABLE_RNG200MA			16	// Импульсное включение реле шунта канала формирования тока до 200мА
#define ACT_DBG_ENABLE_RNG2A			17	// Импульсное включение реле шунта канала формирования тока до 2А
#define ACT_DBG_ENABLE_RNG20A			18	// Импульсное включение реле шунта канала формирования тока до 20А
#define ACT_DBG_ENABLE_RNG270A			19	// Импульсное включение реле шунта канала формирования тока до 270А
#define ACT_DBG_ENABLE_DISCHARGE		20	// Импульсное включение реле разряда батареи
#define ACT_DBG_ENABLE_PSBOARD			21	// Импульсное включение разрешения работы заряда батареи
#define ACT_DBG_IMPULSE_SYNC1			22	// Импульсное включение первого выхода синхронизации
#define ACT_DBG_IMPULSE_SYNC2			23	// Импульсное включение второго выхода синхронизации
#define ACT_DBG_SEND_DATA_TO_DAC		24	// Отправка тестовых данных на ЦАП
#define ACT_DBG_SEND_DATA_TO_REG		25	// Отправка тестовых данных на внешний сдвиговый регистр
#define ACT_DBG_MEASURE_ADC				26	// Чтение каналов АЦП

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры
#define REG_V_BAT_MEASURE				2	// Измеренное значение напряжения на батареи (в В)
#define REG_V_BAT_OFFSET				3	// Смещение оцифрованного напряжения батареи (в тиках)
#define REG_V_BAT_K						4	// Коэффициент пересчёта напряжения АЦП (в мВ) в напряжение (в В) x1000

#define REG_V_DUT_MEASURE				5	// Измеренное значение напряжения на DUT (в В)
#define REG_V_DUT_OFFSET				6	// Смещение оцифрованного напряжения DUT (в тиках)
#define REG_V_DUT_K						7	// Коэффициент пересчёта напряжения АЦП (в мВ) в напряжение (в В) x1000
#define REG_V_DUT_P0					8	// Полином точной корректировки напряжения DUT P0 (в вольтах)
#define REG_V_DUT_P1					9	// Полином точной корректировки напряжения DUT P1 x1000
#define REG_V_DUT_P2					10	// Полином точной корректировки напряжения DUT P2 x1e6

#define REG_I_DUT_MEASURE				11	// Измеренное значение импульса тока (в В)
#define REG_I_DUT_OFFSET				12	// Смещение оцифрованного импульса тока (в тиках)
#define REG_I_DUT_K						13	// Коэффициент пересчёта напряжения АЦП (в мВ) в напряжение (в В) x1000
#define REG_I_DUT_P0					14	// Полином точной корректировки тока DUT P0 (в вольтах)
#define REG_I_DUT_P1					15	// Полином точной корректировки тока DUT P1 x1000
#define REG_I_DUT_P2					16	// Полином точной корректировки тока DUT P2 x1e6

#define REG_DAC_I_SET_K					17	// Пропорцианальный коэффициент пересчета ЦАП
#define REG_DAC_I_SET_OFFSET			18	// Смещение при пересчете ЦАП


// Несохраняемы регистры чтения-записи
#define REG_CURRENT_SETPOINT			128	// Значение задания тока (в А)

//Регистры отладки
#define REG_DBG_DATA					140	// Регистор приема передачи тестовых данных
#define REG_DBG_ENABLE_DEVICE			141	// Тестовый регистр выбора ЦАП

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_WARNING						195	// Регистр Warning
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции
//
#define REG_ACTUAL_BAT_VOLTAGE			200	// Текущее напряжение на батарее (в В)
// -----------------------------

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0
#define DF_BATTERY						1	// Проблема заряда батареи

// Problem
#define PROBLEM_NONE					0

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ

#endif //  __DEV_OBJ_DIC_H
