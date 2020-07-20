#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS		1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT			0		// Количество массивов для записи
#define EP_COUNT				0		// Количество массивов для чтения
#define ENABLE_LOCKING			FALSE	// Защита NV регистров паролем

// Временные параметры
#define TIME_LED_BLINK			500		// Мигание светодиодом (в мс)
#define TIME_EXT_LED_BLINK		500		// Время загорания внешнего светодиода (в мс)
#define TIME_BAT_CHARGE			1000	// Время заряда батареи  (в мс)

// Параметры АЦП
#define V_ADC1_CH				1		// Номер канала АЦП V_DUT
#define I_ADC2_CH				1		// Номер канала АЦП I_DUT
#define VBAT_ADC2_CH			3		// Номер канала АЦП батареи
#define ADC_REF_VOLTAGE			3300.0f	// Опорное напряжение (в мВ)
#define ADC_RESOLUTION			4095	// Разрешение АЦП

// Параметры ЦАП
#define DAC_REF_VOLTAGE			3300.0f	// Опорное напряжение (в мВ)
#define DAC_RESOLUTION			4095	// Разрешение ЦАП

// Параметры батареи
#define BAT_VOLTAGE_THRESHOLD	50		// Пороговое напряжение батареи (в В)
#define BAT_VOLTAGE_DELTA		5.0f	// Гистерезис поддержания напряжения (в В)

//Параметры формирования тока
#define I_RANGE_20MA			20		// Диапазон до 20мА
#define I_RANGE_200MA			200		// Диапазон до 200мА
#define I_RANGE_2A				2000	// Диапазон до 2А
#define I_RANGE_20A				20000	// Диапазон до 20А
#define I_RANGE_270A			270000	// Диапазон до 270А

#endif //  __GLOBAL_H
