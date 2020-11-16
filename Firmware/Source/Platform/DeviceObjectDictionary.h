#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Переход в состояние ожидания
#define ACT_DISABLE_POWER				2	// Отключение блока
#define ACT_FAULT_CLEAR					3	// Очистка fault
#define ACT_WARNING_CLEAR				4	// Очистка warning

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
#define ACT_DBG_TURNON_OUT_BUS			21	// Импульсное включение реле шунта канала формирования тока до 270А
#define ACT_DBG_TURNOFF_OUT_BUS			22	// Импульсное включение реле шунта канала формирования тока до 270А
#define ACT_DBG_ENABLE_DISCHARGE		23	// Импульсное включение реле разряда батареи
#define ACT_DBG_ENABLE_PSBOARD			24	// Импульсное включение разрешения работы заряда батареи
#define ACT_DBG_IMPULSE_SYNC1			25	// Импульсное включение первого выхода синхронизации
#define ACT_DBG_IMPULSE_SYNC2			26	// Импульсное включение второго выхода синхронизации
#define ACT_DBG_SET_CURRENT_MAX_2A		27	// Отправка тестовых данных на ЦАП для формирования тока до 2А
#define ACT_DBG_SET_CURRENT_MAX_20A		28	// Отправка тестовых данных на ЦАП для формирования тока до 20А
#define ACT_DBG_SET_CURRENT_MAX_270A	29	// Отправка тестовых данных на ЦАП для формирования тока до 270А
#define ACT_DBG_SEND_DATA_TO_REG		30	// Отправка тестовых данных на внешний сдвиговый регистр
#define ACT_DBG_MEASURE_ID2A			31	// Измерение тока до 2А
#define ACT_DBG_MEASURE_ID270A			32	// Измерение тока до 270А
#define ACT_DBG_MEASURE_VD250MV			33	// Измерение напряжения до 250мВ
#define ACT_DBG_MEASURE_VD11V			34	// Измерение напряжения до 11В
#define ACT_DBG_IMPULSE_20MA			35	// Формирование тока до 20мА без ОС
#define ACT_DBG_IMPULSE_200MA			36	// Формирование тока до 200мА без ОС
#define ACT_DBG_IMPULSE_2A				37	// Формирование тока до 2А без ОС
#define ACT_DBG_IMPULSE_20A				39	// Формирование тока до 20А без ОС
#define ACT_DBG_IMPULSE_270A			40	// Формирование тока до 270А без ОС

#define ACT_START_PROCESS				100	// Страрт процесса формирования импульса
#define ACT_STOP_PROCESS				101	// Остановка процесса формирования импульса

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры

#define REG_ADC_VBAT_OFFSET				2	// Смещение оцифрованного напряжения батареи (в тиках)
#define REG_ADC_VBAT_K					3	// Коэффициент пересчёта напряжения АЦП (в мВ) в напряжение (в В) x1000

#define REG_ADC_VD10MV_OFFSET			62	// Смещение пересчета до 10мВ (в тиках)
#define REG_ADC_VD10MV_K				63	// Коэффициент пересчета до 10мВ (в В) x1000
#define REG_ADC_VD10MV_FINE_P0			64	// Полином точной корректировки до 10мВ P0 (в вольтах)
#define REG_ADC_VD10MV_FINE_P1			65	// Полином точной корректировки до 10мВ P1 x1000
#define REG_ADC_VD10MV_FINE_P2			66	// Полином точной корректировки до 10мВ P2 x1e6

#define REG_ADC_VD30MV_OFFSET			4	// Смещение пересчета до 30мВ (в тиках)
#define REG_ADC_VD30MV_K				5	// Коэффициент пересчета до 30мВ (в В) x1000
#define REG_ADC_VD30MV_FINE_P0			6	// Полином точной корректировки до 30мВ P0 (в вольтах)
#define REG_ADC_VD30MV_FINE_P1			7	// Полином точной корректировки до 30мВ P1 x1000
#define REG_ADC_VD30MV_FINE_P2			8	// Полином точной корректировки до 30мВ P2 x1e6

#define REG_ADC_VD250MV_OFFSET			9	// Смещение пересчета до 250мВ (в тиках)
#define REG_ADC_VD250MV_K				10	// Коэффициент пересчета до 250мВ (в В) x1000
#define REG_ADC_VD250MV_FINE_P0			11	// Полином точной корректировки до 250мВ P0 (в вольтах)
#define REG_ADC_VD250MV_FINE_P1			12	// Полином точной корректировки до 250мВ P1 x1000
#define REG_ADC_VD250MV_FINE_P2			13	// Полином точной корректировки до 250мВ P2 x1e6

#define REG_ADC_VD1500MV_OFFSET			14	// Смещение пересчета до 1500мВ (в тиках)
#define REG_ADC_VD1500MV_K				15	// Коэффициент пересчета до 1500мВ (в В) x1000
#define REG_ADC_VD1500MV_FINE_P0		16	// Полином точной корректировки до 1500мВ P0 (в вольтах)
#define REG_ADC_VD1500MV_FINE_P1		17	// Полином точной корректировки до 1500мВ P1 x1000
#define REG_ADC_VD1500MV_FINE_P2		18	// Полином точной корректировки до 1500мВ P2 x1e6

#define REG_ADC_VD11V_OFFSET			19	// Смещение пересчета до 11В (в тиках)
#define REG_ADC_VD11V_K					20	// Коэффициент пересчета до 11В (в В) x1000
#define REG_ADC_VD11V_FINE_P0			21	// Полином точной корректировки до 11В P0 (в вольтах)
#define REG_ADC_VD11V_FINE_P1			22	// Полином точной корректировки до 11В P1 x1000
#define REG_ADC_VD11V_FINE_P2			23	// Полином точной корректировки до 11В P2 x1e6

#define REG_ADC_ID20MA_OFFSET			24	// Смещение пересчета до 20мА (в В)
#define REG_ADC_ID20MA_K				25	// Коэффициент пересчета до 20мА (в тиках)
#define REG_ADC_ID20MA_FINE_P0			26	// Полином точной корректировки до 2А P0 (в вольтах)
#define REG_ADC_ID20MA_FINE_P1			27	// Полином точной корректировки до 2А P1 x1000
#define REG_ADC_ID20MA_FINE_P2			28	// Полином точной корректировки до 2А P2 x1e6

#define REG_ADC_ID200MA_OFFSET			29	// Смещение пересчета до 200мА (в В)
#define REG_ADC_ID200MA_K				30	// Коэффициент пересчета до 200мА (в тиках)
#define REG_ADC_ID200MA_FINE_P0			31	// Полином точной корректировки до 200мА P0 (в вольтах)
#define REG_ADC_ID200MA_FINE_P1			32	// Полином точной корректировки до 200мА P1 x1000
#define REG_ADC_ID200MA_FINE_P2			33	// Полином точной корректировки до 200мА P2 x1e6

#define REG_ADC_ID2A_OFFSET				34	// Смещение пересчета до 2А (в В)
#define REG_ADC_ID2A_K					35	// Коэффициент пересчета до 2А (в тиках)
#define REG_ADC_ID2A_FINE_P0			36	// Полином точной корректировки до 2А P0 (в вольтах)
#define REG_ADC_ID2A_FINE_P1			37	// Полином точной корректировки до 2А P1 x1000
#define REG_ADC_ID2A_FINE_P2			38	// Полином точной корректировки до 2А P2 x1e6

#define REG_ADC_ID20A_OFFSET			39	// Смещение пересчета до 20А (в В)
#define REG_ADC_ID20A_K					40	// Коэффициент пересчета до 20А (в тиках)
#define REG_ADC_ID20A_FINE_P0			41	// Полином точной корректировки до 20А P0 (в вольтах)
#define REG_ADC_ID20A_FINE_P1			42	// Полином точной корректировки до 20А P1 x1000
#define REG_ADC_ID20A_FINE_P2			43	// Полином точной корректировки до 20А P2 x1e6

#define REG_ADC_ID270A_OFFSET			44	// Смещение пересчета до 270А (в В)
#define REG_ADC_ID270A_K				45	// Коэффициент пересчета до 270А (в тиках)
#define REG_ADC_ID270A_FINE_P0			46	// Полином точной корректировки до 270А P0 (в вольтах)
#define REG_ADC_ID270A_FINE_P1			47	// Полином точной корректировки до 270А P1 x1000
#define REG_ADC_ID270A_FINE_P2			48	// Полином точной корректировки до 270А P2 x1e6

#define REG_DAC_I20MA_SET_OFFSET		49	// Смещение при пересчете ЦАП
#define REG_DAC_I20MA_SET_K				50	// Пропорцианальный коэффициент пересчета ЦАП
#define REG_DAC_I200MA_SET_OFFSET		51	// Смещение при пересчете ЦАП
#define REG_DAC_I200MA_SET_K			52	// Пропорцианальный коэффициент пересчета ЦАП
#define REG_DAC_I2A_SET_OFFSET			53	// Смещение при пересчете ЦАП
#define REG_DAC_I2A_SET_K				54	// Пропорцианальный коэффициент пересчета ЦАП
#define REG_DAC_I20A_SET_OFFSET			55	// Смещение при пересчете ЦАП
#define REG_DAC_I20A_SET_K				56	// Пропорцианальный коэффициент пересчета ЦАП
#define REG_DAC_I270A_SET_OFFSET		57	// Смещение при пересчете ЦАП
#define REG_DAC_I270A_SET_K				58	// Пропорцианальный коэффициент пересчета ЦАП

#define REG_CTRL_P_COEF					59	// Пропорциональный коэффициент регулятора (х1000)
#define REG_CTRL_I_COEF					60	// Интегральный коэффициент регулятора (х1000)

#define REG_MAX_PULSE_TO_PULSE_PAUSE	61	// Задержка между импульсами на максимальном токе (в мс)

#define REG_ENABLE_FOLLOWING_ERROR		70	// Разрешение мониторинга FollowingError
#define REG_FE_THRESHOLD				71	// Уровень ошибки срабатывания FollowingError (в %)
#define REG_FE_COUNTER_MAX				72	// Счётчик условия срабатывания FollowingError

// Несохраняемы регистры чтения-записи
#define REG_CURRENT_SETPOINT_LOW		128	// Значение задания тока младшие разряды (в мкА)
#define REG_CURRENT_SETPOINT_HIGH		129	// Значение задания тока старшие разряды(в мкА)
#define REG_VOLTAGE_DUT_LIM_LOW			130	// Предельное значение падения напряжения младшие разряды (в мкВ)
#define REG_VOLTAGE_DUT_LIM_HIGH		131	// Предельное значение падения напряжения старшие разряды (в мкВ)

#define REG_EN_CURRENT_FB				132 // Регистр выбора обратной связи по току

//Регистры отладки
#define REG_DBG_DATA					140	// Регистор приема передачи тестовых данных

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_WARNING						195	// Регистр Warning
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции
#define REG_SUB_STATE					198	// Регистр вспомогательного состояния

#define REG_IDUT_AVERAGE_LOW			250	// Полученное значение тока младшие разряды (в мкА)
#define REG_IDUT_AVERAGE_HIGH			251	// Полученное значение тока старшие разряды (в мкА)
#define REG_VDUT_AVERAGE_LOW			252	// Полученное значение напряжения младшие разряды (в мкВ)
#define REG_VDUT_AVERAGE_HIGH			253	// Полученное значение напряжения старшие разряды (в мкВ)
#define REG_ADC_VBAT_MEASURE			254	// Хранение напряжения заряда батареи (в мВ)
// -----------------------------
#define REG_FWINFO_SLAVE_NID			256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID			257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN				260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN			261	// Begining of the information string record

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0
#define DF_BATTERY						1	// Проблема заряда батареи

// Problem
#define PROBLEM_NONE					0
#define PROBLEM_FOLLOWING_ERROR			1	// Ошибка регулятора FollowingError

//  Warning
#define WARNING_NONE					0
#define WARNING_CURRENT_TO_HIGH			1	// Попытка задать уставку тока больше допустимой

// ENDPOINTS
//
#define EP_DUT_V						1		// Оцифрованные данные напряжения DUT (в В)
#define EP_DUT_I						2		// Оцифрованные данные напряжения DUT (в В)
#define EP_REG_ERROE					3		// Оцифрованные данные тока DUT (в мА)
#define EP_OUT_DATA						4		// Оцифрованные данные тока DUT (в мА)
//
//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1		//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2		//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3		//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4		//  Неправильный ключ

#endif //  __DEV_OBJ_DIC_H
