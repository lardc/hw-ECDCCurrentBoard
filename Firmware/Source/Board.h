#ifndef __BOARD_H
#define __BOARD_H

#include "stm32f30x.h"

#include "ZwRCC.h"
#include "ZwGPIO.h"
#include "ZwNCAN.h"
#include "ZwTIM.h"
#include "ZwDAC.h"
#include "ZwDMA.h"
#include "ZwADC.h"
#include "ZwEXTI.h"
#include "ZwSCI.h"
#include "ZwIWDG.h"
#include "ZwNFLASH.h"

// Определения для выходных портов
GPIO_PortPinSettingMacro GPIO_CS				= {GPIOA, Pin_1};
GPIO_PortPinSettingMacro GPIO_LDAC1				= {GPIOA, Pin_2};
GPIO_PortPinSettingMacro GPIO_LDAC2				= {GPIOA, Pin_3};
GPIO_PortPinSettingMacro GPIO_CTRL_SEN_11V		= {GPIOA, Pin_8};
GPIO_PortPinSettingMacro GPIO_CTRL_SEN_1500mV	= {GPIOA, Pin_1};
GPIO_PortPinSettingMacro GPIO_SREG_OE			= {GPIOB, Pin_0};
GPIO_PortPinSettingMacro GPIO_SREG_CS			= {GPIOB, Pin_1};
GPIO_PortPinSettingMacro GPIO_EN_RANGE_200mA	= {GPIOB, Pin_2};
GPIO_PortPinSettingMacro GPIO_CTRL_SEN_250mV	= {GPIOB, Pin_3};
GPIO_PortPinSettingMacro GPIO_CTRL_SEN_30mV		= {GPIOB, Pin_4};
GPIO_PortPinSettingMacro GPIO_CTRL_RLC_20A		= {GPIOB, Pin_5};
GPIO_PortPinSettingMacro GPIO_SET_RLC_270A		= {GPIOB, Pin_6};
GPIO_PortPinSettingMacro GPIO_RES_RLC_270A		= {GPIOB, Pin_7};
GPIO_PortPinSettingMacro GPIO_BAT_DISCHARGE		= {GPIOB, Pin_8};
GPIO_PortPinSettingMacro GPIO_PS_CTRL			= {GPIOB, Pin_9};
GPIO_PortPinSettingMacro GPIO_EN_RANGE_2A		= {GPIOB, Pin_10};
GPIO_PortPinSettingMacro GPIO_EN_RANGE_20mA		= {GPIOB, Pin_14};
GPIO_PortPinSettingMacro GPIO_LED				= {GPIOC, Pin_13};
GPIO_PortPinSettingMacro GPIO_LED_EXT			= {GPIOC, Pin_14};


// Определения для портов альтернативных функций
GPIO_PortPinSettingMacro GPIO_ALT_CAN_RX		= {GPIOA, Pin_11};
GPIO_PortPinSettingMacro GPIO_ALT_CAN_TX		= {GPIOA, Pin_12};
GPIO_PortPinSettingMacro GPIO_ALT_UART_RX		= {GPIOA, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_UART_TX		= {GPIOA, Pin_9};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_CLK		= {GPIOA, Pin_5};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_MOSI		= {GPIOA, Pin_7};

// Линия синхронизации
GPIO_PortPinSettingMacro GPIO_SYNC_OUT2			= {GPIOB, Pin_11};
GPIO_PortPinSettingMacro GPIO_SYNC_OUT1			= {GPIOB, Pin_12};
GPIO_PortPinSettingMacro GPIO_SYNC_IN1			= {GPIOB, Pin_13};
GPIO_PortPinSettingMacro GPIO_SYNC_IN2			= {GPIOB, Pin_15};

#endif // __BOARD_H
