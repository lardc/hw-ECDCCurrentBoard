﻿// -----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "Constraints.h"

// Constants
//
const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE] = {{0, 0, 0},			// 0
		{0, 0, 0},																	// 1
		{VBAT_OFFSET_MIN, VBAT_OFFSET_MAX, VBAT_OFFSET_DEF},						// 2
		{VBAT_K_MIN, VBAT_K_MAX, VBAT_K_DEF},										// 3
		{VD30MV_OFFSET_MIN, VD30MV_OFFSET_MAX, VD30MV_OFFSET_DEF},					// 4
		{VD30MV_K_MIN, VD30MV_K_MAX, VD30MV_K_DEF},									// 5
		{VD30MV_P0_MIN, VD30MV_P0_MAX, VD30MV_P0_DEF},								// 6
		{VD30MV_P1_MIN, VD30MV_P1_MAX, VD30MV_P1_DEF},								// 7
		{VD30MV_P2_MIN, VD30MV_P2_MAX, VD30MV_P2_DEF},								// 8
		{VD250MV_OFFSET_MIN, VD250MV_OFFSET_MAX, VD250MV_OFFSET_DEF},				// 9
		{VD250MV_K_MIN, VD250MV_K_MAX, VD250MV_K_DEF},								// 10
		{VD250MV_P0_MIN, VD250MV_P0_MAX, VD250MV_P0_DEF},							// 11
		{VD250MV_P1_MIN, VD250MV_P1_MAX, VD250MV_P1_DEF},							// 12
		{VD250MV_P2_MIN, VD250MV_P2_MAX, VD250MV_P2_DEF},							// 13
		{VD1500MV_OFFSET_MIN, VD1500MV_OFFSET_MAX, VD1500MV_OFFSET_DEF},			// 14
		{VD1500MV_K_MIN, VD1500MV_K_MAX, VD1500MV_K_DEF},							// 15
		{VD1500MV_P0_MIN, VD1500MV_P0_MAX, VD1500MV_P0_DEF},						// 16
		{VD1500MV_P1_MIN, VD1500MV_P1_MAX, VD1500MV_P1_DEF},						// 17
		{VD1500MV_P2_MIN, VD1500MV_P2_MAX, VD1500MV_P2_DEF},						// 18
		{VD11V_OFFSET_MIN, VD11V_OFFSET_MAX, VD11V_OFFSET_DEF},						// 19
		{VD11V_K_MIN, VD11V_K_MAX, VD11V_K_DEF},									// 20
		{VD11V_P0_MIN, VD11V_P0_MAX, VD11V_P0_DEF},									// 21
		{VD11V_P1_MIN, VD11V_P1_MAX, VD11V_P1_DEF},									// 22
		{VD11V_P2_MIN, VD11V_P2_MAX, VD11V_P2_DEF},									// 23
		{ID20MA_OFFSET_MIN, ID20MA_OFFSET_MAX, ID20MA_OFFSET_DEF},					// 24
		{ID20MA_K_MIN, ID20MA_K_MAX, ID20MA_K_DEF},									// 25
		{ID20MA_P0_MIN, ID20MA_P0_MAX, ID20MA_P0_DEF},								// 26
		{ID20MA_P1_MIN, ID20MA_P1_MAX, ID20MA_P1_DEF},								// 27
		{ID20MA_P2_MIN, ID20MA_P2_MAX, ID20MA_P2_DEF},								// 28
		{ID200MA_OFFSET_MIN, ID200MA_OFFSET_MAX, ID200MA_OFFSET_DEF},				// 29
		{ID200MA_K_MIN, ID200MA_K_MAX, ID200MA_K_DEF},								// 30
		{ID200MA_P0_MIN, ID200MA_P0_MAX, ID200MA_P0_DEF},							// 31
		{ID200MA_P1_MIN, ID200MA_P1_MAX, ID200MA_P1_DEF},							// 32
		{ID200MA_P2_MIN, ID200MA_P2_MAX, ID200MA_P2_DEF},							// 33
		{ID2A_OFFSET_MIN, ID2A_OFFSET_MAX, ID2A_OFFSET_DEF},						// 34
		{ID2A_K_MIN, ID2A_K_MAX, ID2A_K_DEF},										// 35
		{ID2A_P0_MIN, ID2A_P0_MAX, ID2A_P0_DEF},									// 36
		{ID2A_P1_MIN, ID2A_P1_MAX, ID2A_P1_DEF},									// 37
		{ID2A_P2_MIN, ID2A_P2_MAX, ID2A_P2_DEF},									// 38
		{ID20A_OFFSET_MIN, ID20A_OFFSET_MAX, ID20A_OFFSET_DEF},						// 39
		{ID20A_K_MIN, ID20A_K_MAX, ID20A_K_DEF},									// 40
		{ID20A_P0_MIN, ID20A_P0_MAX, ID20A_P0_DEF},									// 41
		{ID20A_P1_MIN, ID20A_P1_MAX, ID20A_P1_DEF},									// 42
		{ID20A_P2_MIN, ID20A_P2_MAX, ID20A_P2_DEF},									// 43
		{ID270A_OFFSET_MIN, ID270A_OFFSET_MAX, ID270A_OFFSET_DEF},					// 44
		{ID270A_K_MIN, ID270A_K_MAX, ID270A_K_DEF},									// 45
		{ID270A_P0_MIN, ID270A_P0_MAX, ID270A_P0_DEF},								// 46
		{ID270A_P1_MIN, ID270A_P1_MAX, ID270A_P1_DEF},								// 47
		{ID270A_P2_MIN, ID270A_P2_MAX, ID270A_P2_DEF},								// 48
		{DAC_I20MA_OFFSET_MIN, DAC_I20MAT_OFFSET_MAX, DAC_I20MA_OFFSET_DEF},		// 49
		{DAC_I20MA_K_MIN, DAC_I20MA_K_MAX, DAC_I20MA_K_DEF},						// 50
		{DAC_I200MA_OFFSET_MIN, DAC_I200MA_OFFSET_MAX, DAC_I200MA_OFFSET_DEF},		// 51
		{DAC_I200MA_K_MIN, DAC_I200MA_K_MAX, DAC_I200MA_K_DEF},						// 52
		{DAC_I2A_OFFSET_MIN, DAC_I2A_OFFSET_MAX, DAC_I2A_OFFSET_DEF},				// 53
		{DAC_I2A_K_MIN, DAC_I2A_K_MAX, DAC_I2A_K_DEF},								// 54
		{DAC_I20A_OFFSET_MIN, DAC_I20A_OFFSET_MAX, DAC_I20A_OFFSET_DEF},			// 53
		{DAC_I20A_K_MIN, DAC_I20A_K_MAX, DAC_I20A_K_DEF},							// 54
		{DAC_I270A_OFFSET_MIN, DAC_I270A_OFFSET_MAX, DAC_I270A_OFFSET_DEF},			// 53
		{DAC_I270A_K_MIN, DAC_I270A_K_MAX, DAC_I270A_K_DEF},						// 54
		{CTRL_P_COEF_MIN, CTRL_P_COEF_MAX, CTRL_P_COEF_DEF},						// 59
		{CTRL_I_COEF_MIN, CTRL_I_COEF_MAX, CTRL_I_COEF_DEF},						// 60
		{PULSE_PAUSE_MIN, PULSE_PAUSE_MAX, PULSE_PAUSE_DEF},						// 61
		{0, 0, 0},																	// 62
		{0, 0, 0},																	// 63
		{0, 0, 0},																	// 64
		{0, 0, 0},																	// 65
		{0, 0, 0},																	// 66
		{0, 0, 0},																	// 67
		{0, 0, 0},																	// 68
		{0, 0, 0},																	// 69
		{0, 0, 0},																	// 70
		{0, 0, 0},																	// 71
		{0, 0, 0},																	// 72
		{0, 0, 0},																	// 73
		{0, 0, 0},																	// 74
		{0, 0, 0},																	// 75
		{0, 0, 0},																	// 76
		{0, 0, 0},																	// 77
		{0, 0, 0},																	// 78
		{0, 0, 0},																	// 79
		{0, 0, 0},																	// 80
		{0, 0, 0},																	// 81
		{0, 0, 0},																	// 82
		{0, 0, 0},																	// 83
		{0, 0, 0},																	// 84
		{0, 0, 0},																	// 85
		{0, 0, 0},																	// 86
		{0, 0, 0},																	// 87
		{0, 0, 0},																	// 88
		{0, 0, 0},																	// 89
		{0, 0, 0},																	// 90
		{0, 0, 0},																	// 91
		{0, 0, 0},																	// 92
		{0, 0, 0},																	// 93
		{0, 0, 0},																	// 94
		{0, 0, 0},																	// 95
		{0, 0, 0},																	// 96
		{0, 0, 0},																	// 97
		{0, 0, 0},																	// 98
		{0, 0, 0},																	// 99
		{0, 0, 0},																	// 100
		{0, 0, 0},																	// 101
		{0, 0, 0},																	// 102
		{0, 0, 0},																	// 103
		{0, 0, 0},																	// 104
		{0, 0, 0},																	// 105
		{0, 0, 0},																	// 106
		{0, 0, 0},																	// 107
		{0, 0, 0},																	// 108
		{0, 0, 0},																	// 109
		{0, 0, 0},																	// 110
		{0, 0, 0},																	// 111
		{0, 0, 0},																	// 112
		{0, 0, 0},																	// 113
		{0, 0, 0},																	// 114
		{0, 0, 0},																	// 115
		{0, 0, 0},																	// 116
		{0, 0, 0},																	// 117
		{0, 0, 0},																	// 118
		{0, 0, 0},																	// 119
		{0, 0, 0},																	// 120
		{0, 0, 0},																	// 121
		{0, 0, 0},																	// 122
		{0, 0, 0},																	// 123
		{0, 0, 0},																	// 124
		{0, 0, 0},																	// 125
		{0, 0, 0},																	// 126
		{0, 1, 1}																	// 127
};

const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] = {{CURRENT_SETPOINT_LOW_MIN,
CURRENT_SETPOINT_LOW_MAX,
CURRENT_SETPOINT_LOW_DEF},																				// 128
		{CURRENT_SETPOINT_HIGH_MIN, CURRENT_SETPOINT_HIGH_MAX, CURRENT_SETPOINT_HIGH_DEF},						// 129
		{VOLTAGE_DUT_LIM_MIN, VOLTAGE_DUT_LIM_MAX, VOLTAGE_DUT_LIM_DEF},										// 130
		{EN_CURRENT_FB_MIN, EN_CURRENT_FB_MAX, EN_CURRENT_FB_DEF},												// 131
		{0, 0, 0},																	// 132
		{0, 0, 0},																	// 133
		{0, 0, 0},																	// 134
		{0, 0, 0},																	// 135
		{0, 0, 0},																	// 136
		{0, 0, 0},																	// 137
		{0, 0, 0},																	// 138
		{0, 0, 0},																	// 139
		{DBG_DATA_MIN, DBG_DATA_MAX, DBG_DATA_DEF},									// 140
		{0, 0, 0},																	// 141
		{0, 0, 0},																	// 142
		{0, 0, 0},																	// 143
		{0, 0, 0},																	// 144
		{0, 0, 0},																	// 145
		{0, 0, 0},																	// 146
		{0, 0, 0},																	// 147
		{0, 0, 0},																	// 148
		{0, 0, 0},																	// 149
		{0, 0, 0},																	// 150
		{0, 0, 0},																	// 151
		{0, 0, 0},																	// 152
		{0, 0, 0},																	// 153
		{0, 0, 0},																	// 154
		{0, 0, 0},																	// 155
		{0, 0, 0},																	// 156
		{0, 0, 0},																	// 157
		{0, 0, 0},																	// 158
		{0, 0, 0},																	// 159
		{0, 0, 0},																	// 160
		{0, 0, 0},																	// 161
		{0, 0, 0},																	// 162
		{0, 0, 0},																	// 163
		{0, 0, 0},																	// 164
		{0, 0, 0},																	// 165
		{0, 0, 0},																	// 166
		{0, 0, 0},																	// 167
		{0, 0, 0},																	// 168
		{0, 0, 0},																	// 169
		{0, 0, 0},																	// 170
		{0, 0, 0},																	// 171
		{0, 0, 0},																	// 172
		{0, 0, 0},																	// 173
		{0, 0, 0},																	// 174
		{0, 0, 0},																	// 175
		{0, 0, 0},																	// 176
		{0, 0, 0},																	// 177
		{0, 0, 0},																	// 178
		{0, 0, 0},																	// 179
		{0, 0, 0},																	// 180
		{0, 0, 0},																	// 181
		{0, 0, 0},																	// 182
		{0, 0, 0},																	// 183
		{0, 0, 0},																	// 184
		{0, 0, 0},																	// 185
		{0, 0, 0},																	// 186
		{0, 0, 0},																	// 187
		{0, 0, 0},																	// 188
		{0, 0, 0},																	// 189
		{0, 0, 0},																	// 190
		{0, 0, 0}																	// 191
};
