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
#define ACT_DBG_TURNON_RNG270A			19	// Импульсное включение реле шунта канала формирования тока до 270А
#define ACT_DBG_TURNOFF_RNG270A			20	// Импульсное включение реле шунта канала формирования тока до 270А
#define ACT_DBG_ENABLE_DISCHARGE		21	// Импульсное включение реле разряда батареи
#define ACT_DBG_ENABLE_PSBOARD			22	// Импульсное включение разрешения работы заряда батареи
#define ACT_DBG_IMPULSE_SYNC1			23	// Импульсное включение первого выхода синхронизации
#define ACT_DBG_IMPULSE_SYNC2			24	// Импульсное включение второго выхода синхронизации
#define ACT_DBG_SET_CURRENT_MAX_2A		25	// Отправка тестовых данных на ЦАП для формирования тока до 2А
#define ACT_DBG_SET_CURRENT_MAX_20A		26	// Отправка тестовых данных на ЦАП для формирования тока до 20А
#define ACT_DBG_SET_CURRENT_MAX_270A	27	// Отправка тестовых данных на ЦАП для формирования тока до 270А
#define ACT_DBG_SEND_DATA_TO_REG		28	// Отправка тестовых данных на внешний сдвиговый регистр
#define ACT_DBG_MEASURE_ID2A			29	// Измерение тока до 2А
#define ACT_DBG_MEASURE_ID270A			30	// Измерение тока до 270А
#define ACT_DBG_MEASURE_VD250MV			31	// Измерение напряжения до 250мВ
#define ACT_DBG_MEASURE_VD11V			32	// Измерение напряжения до 11В
#define ACT_DBG_IMPULSE_20MA			33	// Формирование тока до 20мА без ОС
#define ACT_DBG_IMPULSE_200MA			34	// Формирование тока до 200мА без ОС
#define ACT_DBG_IMPULSE_2A				35	// Формирование тока до 2А без ОС
#define ACT_DBG_IMPULSE_20A				36	// Формирование тока до 20А без ОС
#define ACT_DBG_IMPULSE_270A			37	// Формирование тока до 270А без ОС

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры

#define REG_ADC_VBAT_MEASURE			1	// Хранение напряжения заряда батареи (в В)
#define REG_ADC_VBAT_OFFSET				2	// Смещение оцифрованного напряжения батареи (в тиках)
#define REG_ADC_VBAT_K					3	// Коэффициент пересчёта напряжения АЦП (в мВ) в напряжение (в В) x1000

#define REG_ADC_VD250MV_OFFSET			4	// Смещение пересчета до 250мВ (в тиках)
#define REG_ADC_VD250MV_K				5	// Коэффициент пересчета до 250мВ (в В) x1000
#define REG_ADC_VD250MV_FINE_P0			6	// Полином точной корректировки до 250мВ P0 (в вольтах)
#define REG_ADC_VD250MV_FINE_P1			7	// Полином точной корректировки до 250мВ P1 x1000
#define REG_ADC_VD250MV_FINE_P2			8	// Полином точной корректировки до 250мВ P2 x1e6

#define REG_ADC_VD11V_OFFSET			9	// Смещение пересчета до 11В (в тиках)
#define REG_ADC_VD11V_K					10	// Коэффициент пересчета до 11В (в В) x1000
#define REG_ADC_VD11V_FINE_P0			11	// Полином точной корректировки до 11В P0 (в вольтах)
#define REG_ADC_VD11V_FINE_P1			12	// Полином точной корректировки до 11В P1 x1000
#define REG_ADC_VD11V_FINE_P2			13	// Полином точной корректировки до 11В P2 x1e6

#define REG_ADC_ID2A_OFFSET				14	// Смещение пересчета до 2А (в В)
#define REG_ADC_ID2A_K					15	// Коэффициент пересчета до 2А (в тиках)
#define REG_ADC_ID2A_FINE_P0			16	// Полином точной корректировки до 2А P0 (в вольтах)
#define REG_ADC_ID2A_FINE_P1			17	// Полином точной корректировки до 2А P1 x1000
#define REG_ADC_ID2A_FINE_P2			18	// Полином точной корректировки до 2А P2 x1e6

#define REG_ADC_ID270A_OFFSET			19	// Смещение пересчета до 270А (в В)
#define REG_ADC_ID270A_K				20	// Коэффициент пересчета до 270А (в тиках)
#define REG_ADC_ID270A_FINE_P0			21	// Полином точной корректировки до 270А P0 (в вольтах)
#define REG_ADC_ID270A_FINE_P1			22	// Полином точной корректировки до 270А P1 x1000
#define REG_ADC_ID270A_FINE_P2			23	// Полином точной корректировки до 270А P2 x1e6

#define REG_DAC_I_SET_K					24	// Пропорцианальный коэффициент пересчета ЦАП
#define REG_DAC_I_SET_OFFSET			25	// Смещение при пересчете ЦАП

#define REG_CTRL_P_COEF					26	// Пропорциональный коэффициент регулятора (х1000)
#define REG_CTRL_I_COEF					27	// Интегральный коэффициент регулятора (х1000)

// Несохраняемы регистры чтения-записи
#define REG_CURRENT_SETPOINT			128	// Значение задания тока (в А)
#define REG_VOLTAGE_SETPOINT			129	// Значение задания тока (в мВ)
#define REG_VDUT_AVERAGE				130	// Значение задания тока (в А)
#define REG_IDUT_AVERAGE				131	// Значение задания тока (в мВ)

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

// ENDPOINTS
//
#define EP_DUT_V						1		// Оцифрованные данные напряжения DUT (в В)
#define EP_DUT_I						2		// Оцифрованные данные тока DUT (в мА)
//
#define EP_DIAG_DUT_VDUT				4		// Значения напряжения Vdut по пульсам (в В)
#define EP_DIAG_DUT_IDUT				5		// Значения напряжения Idut по пульсам (в мА)

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ

#endif //  __DEV_OBJ_DIC_H
