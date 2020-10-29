#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
#define VBAT_OFFSET_MIN				0		//
#define VBAT_OFFSET_MAX				65535	//
#define VBAT_OFFSET_DEF				65375	//
#define VBAT_K_MIN					1		//
#define VBAT_K_MAX					50000	//
#define VBAT_K_DEF					1000	//

#define VD10MV_OFFSET_MIN			0		//
#define VD10MV_OFFSET_MAX			65535	//
#define VD10MV_OFFSET_DEF			65000	//
#define VD10MV_K_MIN				1		//
#define VD10MV_K_MAX				50000	//
#define VD10MV_K_DEF				1000	//
#define VD10MV_P0_MIN				0		//
#define VD10MV_P0_MAX				65535	//
#define VD10MV_P0_DEF				65000	//
#define VD10MV_P1_MIN				1		//
#define VD10MV_P1_MAX				60000	//
#define VD10MV_P1_DEF				1000	//
#define VD10MV_P2_MIN				0		//
#define VD10MV_P2_MAX				60000	//
#define VD10MV_P2_DEF				1000	//

#define VD30MV_OFFSET_MIN			0		//
#define VD30MV_OFFSET_MAX			65535	//
#define VD30MV_OFFSET_DEF			65000	//
#define VD30MV_K_MIN				1		//
#define VD30MV_K_MAX				50000	//
#define VD30MV_K_DEF				1000	//
#define VD30MV_P0_MIN				0		//
#define VD30MV_P0_MAX				65535	//
#define VD30MV_P0_DEF				65000	//
#define VD30MV_P1_MIN				1		//
#define VD30MV_P1_MAX				60000	//
#define VD30MV_P1_DEF				1000	//
#define VD30MV_P2_MIN				0		//
#define VD30MV_P2_MAX				60000	//
#define VD30MV_P2_DEF				1000	//

#define VD250MV_OFFSET_MIN			0		//
#define VD250MV_OFFSET_MAX			65535	//
#define VD250MV_OFFSET_DEF			65000	//
#define VD250MV_K_MIN				1		//
#define VD250MV_K_MAX				50000	//
#define VD250MV_K_DEF				1000	//
#define VD250MV_P0_MIN				0		//
#define VD250MV_P0_MAX				65535	//
#define VD250MV_P0_DEF				65000	//
#define VD250MV_P1_MIN				1		//
#define VD250MV_P1_MAX				60000	//
#define VD250MV_P1_DEF				1000	//
#define VD250MV_P2_MIN				0		//
#define VD250MV_P2_MAX				60000	//
#define VD250MV_P2_DEF				1000	//

#define VD1500MV_OFFSET_MIN			0		//
#define VD1500MV_OFFSET_MAX			65535	//
#define VD1500MV_OFFSET_DEF			65000	//
#define VD1500MV_K_MIN				1		//
#define VD1500MV_K_MAX				50000	//
#define VD1500MV_K_DEF				1000	//
#define VD1500MV_P0_MIN				0		//
#define VD1500MV_P0_MAX				65535	//
#define VD1500MV_P0_DEF				65000	//
#define VD1500MV_P1_MIN				1		//
#define VD1500MV_P1_MAX				60000	//
#define VD1500MV_P1_DEF				1000	//
#define VD1500MV_P2_MIN				0		//
#define VD1500MV_P2_MAX				60000	//
#define VD1500MV_P2_DEF				1000	//

#define VD11V_OFFSET_MIN			0		//
#define VD11V_OFFSET_MAX			65535	//
#define VD11V_OFFSET_DEF			65000	//
#define VD11V_K_MIN					1		//
#define VD11V_K_MAX					50000	//
#define VD11V_K_DEF					1000	//
#define VD11V_P0_MIN				0		//
#define VD11V_P0_MAX				65535	//
#define VD11V_P0_DEF				65000	//
#define VD11V_P1_MIN				1		//
#define VD11V_P1_MAX				60000	//
#define VD11V_P1_DEF				1000	//
#define VD11V_P2_MIN				0		//
#define VD11V_P2_MAX				60000	//
#define VD11V_P2_DEF				1000	//

#define ID20MA_OFFSET_MIN			0		//
#define ID20MA_OFFSET_MAX			65535	//
#define ID20MA_OFFSET_DEF			65000	//
#define ID20MA_K_MIN				1		//
#define ID20MA_K_MAX				50000	//
#define ID20MA_K_DEF				1000	//
#define ID20MA_P0_MIN				0		//
#define ID20MA_P0_MAX				65535	//
#define ID20MA_P0_DEF				65000	//
#define ID20MA_P1_MIN				1		//
#define ID20MA_P1_MAX				60000	//
#define ID20MA_P1_DEF				1000	//
#define ID20MA_P2_MIN				0		//
#define ID20MA_P2_MAX				60000	//
#define ID20MA_P2_DEF				1000	//

#define ID200MA_OFFSET_MIN			0		//
#define ID200MA_OFFSET_MAX			65535	//
#define ID200MA_OFFSET_DEF			65000	//
#define ID200MA_K_MIN				1		//
#define ID200MA_K_MAX				50000	//
#define ID200MA_K_DEF				1000	//
#define ID200MA_P0_MIN				0		//
#define ID200MA_P0_MAX				65535	//
#define ID200MA_P0_DEF				65000	//
#define ID200MA_P1_MIN				1		//
#define ID200MA_P1_MAX				60000	//
#define ID200MA_P1_DEF				1000	//
#define ID200MA_P2_MIN				0		//
#define ID200MA_P2_MAX				60000	//
#define ID200MA_P2_DEF				1000	//

#define ID2A_OFFSET_MIN				0		//
#define ID2A_OFFSET_MAX				65535	//
#define ID2A_OFFSET_DEF				65000	//
#define ID2A_K_MIN					1		//
#define ID2A_K_MAX					50000	//
#define ID2A_K_DEF					1000	//
#define ID2A_P0_MIN					0		//
#define ID2A_P0_MAX					65535	//
#define ID2A_P0_DEF					65000	//
#define ID2A_P1_MIN					1		//
#define ID2A_P1_MAX					60000	//
#define ID2A_P1_DEF					1000	//
#define ID2A_P2_MIN					0		//
#define ID2A_P2_MAX					60000	//
#define ID2A_P2_DEF					1000	//

#define ID20A_OFFSET_MIN			0		//
#define ID20A_OFFSET_MAX			65535	//
#define ID20A_OFFSET_DEF			65000	//
#define ID20A_K_MIN					1		//
#define ID20A_K_MAX					50000	//
#define ID20A_K_DEF					1000	//
#define ID20A_P0_MIN				0		//
#define ID20A_P0_MAX				65535	//
#define ID20A_P0_DEF				65000	//
#define ID20A_P1_MIN				1		//
#define ID20A_P1_MAX				60000	//
#define ID20A_P1_DEF				1000	//
#define ID20A_P2_MIN				0		//
#define ID20A_P2_MAX				60000	//
#define ID20A_P2_DEF				1000	//

#define ID270A_OFFSET_MIN			0		//
#define ID270A_OFFSET_MAX			65535	//
#define ID270A_OFFSET_DEF			65000	//
#define ID270A_K_MIN				1		//
#define ID270A_K_MAX				50000	//
#define ID270A_K_DEF				1000	//
#define ID270A_P0_MIN				0		//
#define ID270A_P0_MAX				65535	//
#define ID270A_P0_DEF				65000	//
#define ID270A_P1_MIN				1		//
#define ID270A_P1_MAX				60000	//
#define ID270A_P1_DEF				1000	//
#define ID270A_P2_MIN				0		//
#define ID270A_P2_MAX				60000	//
#define ID270A_P2_DEF				1000	//

#define DAC_I20MA_OFFSET_MIN		0		//
#define DAC_I20MAT_OFFSET_MAX		65535	//
#define DAC_I20MA_OFFSET_DEF		65000	//
#define DAC_I20MA_K_MIN				1		//
#define DAC_I20MA_K_MAX				50000	//
#define DAC_I20MA_K_DEF				1000	//

#define DAC_I200MA_OFFSET_MIN		0		//
#define DAC_I200MA_OFFSET_MAX		65535	//
#define DAC_I200MA_OFFSET_DEF		65000	//
#define DAC_I200MA_K_MIN			1		//
#define DAC_I200MA_K_MAX			50000	//
#define DAC_I200MA_K_DEF			1000	//

#define DAC_I2A_OFFSET_MIN			0		//
#define DAC_I2A_OFFSET_MAX			65535	//
#define DAC_I2A_OFFSET_DEF			65000	//
#define DAC_I2A_K_MIN				1		//
#define DAC_I2A_K_MAX				50000	//
#define DAC_I2A_K_DEF				1000	//

#define DAC_I20A_OFFSET_MIN			0		//
#define DAC_I20A_OFFSET_MAX			65535	//
#define DAC_I20A_OFFSET_DEF			65000	//
#define DAC_I20A_K_MIN				1		//
#define DAC_I20A_K_MAX				50000	//
#define DAC_I20A_K_DEF				1000	//

#define DAC_I270A_OFFSET_MIN		0		//
#define DAC_I270A_OFFSET_MAX		65535	//
#define DAC_I270A_OFFSET_DEF		65000	//
#define DAC_I270A_K_MIN				1		//
#define DAC_I270A_K_MAX				50000	//
#define DAC_I270A_K_DEF				1000	//

#define CTRL_P_COEF_MIN				0		//
#define CTRL_P_COEF_MAX				50000	//
#define CTRL_P_COEF_DEF				1000	//

#define CTRL_I_COEF_MIN				0		//
#define CTRL_I_COEF_MAX				50000	//
#define CTRL_I_COEF_DEF				1000	//

#define PULSE_PAUSE_MIN				0		//
#define PULSE_PAUSE_MAX				65535		//
#define PULSE_PAUSE_DEF				10000		//

#define CURRENT_SETPOINT_LOW_MIN	0		//
#define CURRENT_SETPOINT_LOW_MAX	65535		//
#define CURRENT_SETPOINT_LOW_DEF	65535		//
#define CURRENT_SETPOINT_HIGH_MIN	0		//
#define CURRENT_SETPOINT_HIGH_MAX	65535		//
#define CURRENT_SETPOINT_HIGH_DEF	4119		//

#define VOLTAGE_DUT_LIM_LOW_MIN		0		//
#define VOLTAGE_DUT_LIM_LOW_MAX		65535		//
#define VOLTAGE_DUT_LIM_LOW_DEF		65535		//
#define VOLTAGE_DUT_LIM_HIGH_MIN	0		//
#define VOLTAGE_DUT_LIM_HIGH_MAX	65535		//
#define VOLTAGE_DUT_LIM_HIGH_DEF	167		//

#define EN_CURRENT_FB_MIN			0		//
#define EN_CURRENT_FB_MAX			1		//
#define EN_CURRENT_FB_DEF			0		//

#define DBG_DATA_MIN				0		//
#define DBG_DATA_MAX				65535		//
#define DBG_DATA_DEF				65535		//

// Types
typedef struct __TableItemConstraint
{
	Int16U Min;
	Int16U Max;
	Int16U Default;
} TableItemConstraint;

// Variables
extern const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE];
extern const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START];

#endif // __CONSTRAINTS_H
