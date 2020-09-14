#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS		1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT			0		// Количество массивов для записи
#define EP_COUNT				2		// Количество массивов для чтения
#define VALUES_x_SIZE			1000	// Размер выходных массивов
#define ENABLE_LOCKING			FALSE	// Защита NV регистров паролем
#define PULSES_MAX				10		// Максимальное количество импульсов на измерение

// Временные параметры
#define TIME_LED_BLINK			500		// Мигание светодиодом (в мс)
#define TIME_EXT_LED_BLINK		500		// Время загорания внешнего светодиода (в мс)
#define TIME_BAT_CHARGE			5000	// Время заряда батареи  (в мс)
#define Pulse2PulsePause		2000	// Время ежду импульсами (в мс)

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

#define END_CURRENT_PULSE		0		// Значение задания тока 0
#define LOCK_ANALOG_CH			0		// Отключение ОС и каналов измерения тока

#define I_ANALOG_2A				0x0024	// Маска выбора включения ОС и измерения канала до 2А
#define I_ANALOG_20A			0x0012	// Маска выбора включения ОС и измерения канала до 20А
#define I_ANALOG_270A			0x0009	// Маска выбора включения ОС и измерения канала до 270А

#define I_SHUNT_20MA			100000	// Шунт 100000 мОм до 20мА
#define I_SHUNT_200MA			10000	// Шунт 10000 мОм до 200мА
#define I_SHUNT_2A				500		// Шунт 500 мОм до 2А
#define I_SHUNT_20A				50		// Шунт 50 мОм до 20А
#define I_SHUNT_270A			0.5		// Шунт 0.5 мОм до 270А

//Параметры измерения напряжения
#define V_RANGE_30MV			30		// Диапазон до 20мА
#define V_RANGE_250MV			250		// Диапазон до 200мА
#define V_RANGE_1500MV			1500	// Диапазон до 2А
#define V_RANGE_11V				11000	// Диапазон до 20А

// High-speed sampling
#define DMA_ADC_DUT_V_CHANNEL			DMA1_Channel1	// Канал DMA для АЦП напряжения
#define DMA_ADC_DUT_I_CHANNEL			DMA2_Channel1	// Канал DMA для АЦП тока
//
#define ADC1_VOLTAGE_CHANNEL			1				// АЦП1 номер канала напряжения
#define ADC2_CURRENT_CHANNEL			1				// АЦП2 номер канала тока


#endif //  __GLOBAL_H
