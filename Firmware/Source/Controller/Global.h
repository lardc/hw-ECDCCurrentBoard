#ifndef __GLOBAL_H
#define __GLOBAL_H

// Include
//
#include "stdinc.h"
#include "SysConfig.h"

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS				1000									// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT					0										// Количество массивов для записи
#define EP_COUNT						4										// Количество массивов для чтения
#define ENABLE_LOCKING					FALSE									// Защита NV регистров паролем
#define EP_VALUE						PULSE_BUFFER_SIZE						// Размер выходного массива EP

// Параметры импульса тока
#define PULSE_DELAY						10000									// Время паузы между импульсами тока, мС
#define PULSE_TIME_VALUE				10000									// Длительность импульса тока, мкС
#define PULSE_BUFFER_SIZE				(PULSE_TIME_VALUE / PULSE_DIVIDER)		// Количество точек в буфере формы импульса
#define OFFSET_BUFFER_SIZE				65										// Оффсет для начала усреднения измерений
#define SYNC_LINE_HIGHSTATE_TIMEOUT		25										// Таймаут пребывания линии синхронизации в высоком состоянии
#define BLOCK_MAX_CURRENT				270000000								// Максимально возможный ток для канала до 250А (мА/10)
#define PULSE_LITE_START				10										// Количество шагов перед выходом на полку
#define PULSE_DIVIDER					80										// Делитель массива импульса, мс

// Временные параметры
#define TIME_LED_BLINK					500										// Мигание светодиодом (в мс)
#define TIME_EXT_LED_BLINK				500										// Время загорания внешнего светодиода (в мс)
#define TIME_BAT_CHARGE					22000									// Время заряда батареи  (в мс)
#define TIME_REG_STEP					50										// Время работы такта регулятора (в мс)
#define TIME_TRANSIENT_DELAY			100										// Время на раскоммутацию (в мс)

// Параметры АЦП
#define V_ADC1_CH						1										// Номер канала АЦП V_DUT
#define I_ADC2_CH						1										// Номер канала АЦП I_DUT
#define VBAT_ADC3_CH					12										// Номер канала АЦП батареи
#define ADC_REF_VOLTAGE					3000000.0f								// Опорное напряжение (в мкВ)
#define ADC_RESOLUTION					4095									// Разрешение АЦП

// Параметры ЦАП
#define DAC_REF_VOLTAGE					3000000.0f								// Опорное напряжение (в мВ)
#define DAC_RESOLUTION					4095									// Разрешение ЦАП

// Параметры батареи
#define BAT_VOLTAGE_THRESHOLD			40000									// Пороговое напряжение батареи (в мВ)
#define BAT_VOLTAGE_DELTA				500										// Гистерезис поддержания напряжения (в мВ)
#define BAT_VOLTAGE_NEG_DELTA_PASSIVE	3000									// Гистерезис в минус пассивного поддержания напряжения (в мВ)
#define BAT_VOLTAGE_NEG_DELTA_ACTIVE	500										// Гистерезис в минус активного поддержания напряжения (в мВ)

//Параметры формирования тока
#define I_RANGE_20MA					20000									// Диапазон до 20мА (мкА)
#define I_RANGE_200MA					200000									// Диапазон до 200мА (мкА)
#define I_RANGE_2A						2000000									// Диапазон до 2А (мкА)
#define I_RANGE_20A						20000000								// Диапазон до 20А (мкА)
#define I_RANGE_270A					250000000								// Диапазон до 250А (мкА)

#define END_CURRENT_PULSE				0										// Значение задания тока 0
#define LOCK_ANALOG_CH					0										// Отключение ОС и каналов измерения тока

#define BUS_OUT_ON						0x0080									// Маска выбора включения выходного реле
#define BUS_OUT_OFF						0x0040									// Маска выбора выключения выходного реле

#define I_ANALOG_2A						0x0024									// Маска выбора включения ОС и измерения канала до 2А
#define I_ANALOG_20A					0x0012									// Маска выбора включения ОС и измерения канала до 20А
#define I_ANALOG_270A					0x0009									// Маска выбора включения ОС и измерения канала до 270А

#define I_FB_ENABLE						0x0007									// Маска разрешения включения обратной связи
#define IV_MASK_LOW						0x0000FFFF								// Маска младших разрядов тока
#define IV_MASK_HIGH					0xFFFF0000								// Маска старших разрядов тока

#define I_SHUNT_20MA					100										// Шунт 100 Ом до 20мА
#define I_SHUNT_200MA					10										// Шунт 10 Ом до 200мА
#define I_SHUNT_2A						0.44									// Шунт 0.44 Ом до 2А
#define I_SHUNT_20A						0.05									// Шунт 0.05 Ом до 20А
#define I_SHUNT_270A					0.0005									// Шунт 0.0005 Ом до 270А

//Параметры измерения напряжения
#define V_RANGE_10MV					10000									// Диапазон до 10мВ (мкВ)
#define V_RANGE_30MV					30000									// Диапазон до 30мВ (мкВ)
#define V_RANGE_250MV					250000									// Диапазон до 250мВ (мкВ)
#define V_RANGE_1500MV					1500000									// Диапазон до 1500мВ (мкВ)
#define V_RANGE_11V						11000000								// Диапазон до 11В (мкВ)

// Параметры DMA
#define DMA_ADC_DUT_V_CHANNEL			DMA1_Channel1							// Канал DMA для АЦП напряжения
#define DMA_ADC_DUT_I_CHANNEL			DMA2_Channel1							// Канал DMA для АЦП тока
//
#define ADC1_VOLTAGE_CHANNEL			1										// АЦП1 номер канала напряжения DUT
#define ADC2_CURRENT_CHANNEL			1										// АЦП2 номер канала тока DUT

#define VALUES_OUT_SIZE					6										// Размер массива DMA

#endif //  __GLOBAL_H
