#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_START_DIAG_PULSE			5	// ������ ������������ �� ����������� ��������������
#define ACT_FAULT_CLEAR					6	// ������� fault
#define ACT_WARNING_CLEAR				7	// ������� warning

#define ACT_DBG_IMPULSE_LED				10	// ���������� ��������� ������� ���������
#define ACT_DBG_ENABLE_AMP11V			11	// ���������� ��������� ������ �������� ���������� DUT 11�
#define ACT_DBG_ENABLE_AMP1500MV		12	// ���������� ��������� ������ �������� ���������� DUT 1.5�
#define ACT_DBG_ENABLE_AMP250MV			13	// ���������� ��������� ������ �������� ���������� DUT 250��
#define ACT_DBG_ENABLE_AMP30MV			14	// ���������� ��������� ������ �������� ���������� DUT 30��
#define ACT_DBG_ENABLE_RNG20MA			15	// ���������� ��������� ���� ����� ������ ������������ ���� �� 20��
#define ACT_DBG_ENABLE_RNG200MA			16	// ���������� ��������� ���� ����� ������ ������������ ���� �� 200��
#define ACT_DBG_ENABLE_RNG2A			17	// ���������� ��������� ���� ����� ������ ������������ ���� �� 2�
#define ACT_DBG_ENABLE_RNG20A			18	// ���������� ��������� ���� ����� ������ ������������ ���� �� 20�
#define ACT_DBG_TURNON_RNG270A			19	// ���������� ��������� ���� ����� ������ ������������ ���� �� 270�
#define ACT_DBG_TURNOFF_RNG270A			20	// ���������� ��������� ���� ����� ������ ������������ ���� �� 270�
#define ACT_DBG_ENABLE_DISCHARGE		21	// ���������� ��������� ���� ������� �������
#define ACT_DBG_ENABLE_PSBOARD			22	// ���������� ��������� ���������� ������ ������ �������
#define ACT_DBG_IMPULSE_SYNC1			23	// ���������� ��������� ������� ������ �������������
#define ACT_DBG_IMPULSE_SYNC2			24	// ���������� ��������� ������� ������ �������������
#define ACT_DBG_SET_CURRENT_MAX_2A		25	// �������� �������� ������ �� ��� ��� ������������ ���� �� 2�
#define ACT_DBG_SET_CURRENT_MAX_20A		26	// �������� �������� ������ �� ��� ��� ������������ ���� �� 20�
#define ACT_DBG_SET_CURRENT_MAX_270A	27	// �������� �������� ������ �� ��� ��� ������������ ���� �� 270�
#define ACT_DBG_SEND_DATA_TO_REG		28	// �������� �������� ������ �� ������� ��������� �������
#define ACT_DBG_MEASURE_ID2A			29	// ��������� ���� �� 2�
#define ACT_DBG_MEASURE_ID270A			30	// ��������� ���� �� 270�
#define ACT_DBG_MEASURE_VD250MV			31	// ��������� ���������� �� 250��
#define ACT_DBG_MEASURE_VD11V			32	// ��������� ���������� �� 11�
#define ACT_DBG_IMPULSE_20MA			33	// ������������ ���� �� 20�� ��� ��
#define ACT_DBG_IMPULSE_200MA			34	// ������������ ���� �� 200�� ��� ��
#define ACT_DBG_IMPULSE_2A				35	// ������������ ���� �� 2� ��� ��
#define ACT_DBG_IMPULSE_20A				36	// ������������ ���� �� 20� ��� ��
#define ACT_DBG_IMPULSE_270A			37	// ������������ ���� �� 270� ��� ��

#define ACT_START_PROCESS				100	// ������ �������� ������������ ��������
#define ACT_STOP_PROCESS				101	// ��������� �������� ������������ ��������

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������

#define REG_ADC_VBAT_OFFSET				2	// �������� ������������� ���������� ������� (� �����)
#define REG_ADC_VBAT_K					3	// ����������� ��������� ���������� ��� (� ��) � ���������� (� �) x1000

#define REG_ADC_VD30MV_OFFSET			4	// �������� ��������� �� 30�� (� �����)
#define REG_ADC_VD30MV_K				5	// ����������� ��������� �� 30�� (� �) x1000
#define REG_ADC_VD30MV_FINE_P0			6	// ������� ������ ������������� �� 30�� P0 (� �������)
#define REG_ADC_VD30MV_FINE_P1			7	// ������� ������ ������������� �� 30�� P1 x1000
#define REG_ADC_VD30MV_FINE_P2			8	// ������� ������ ������������� �� 30�� P2 x1e6

#define REG_ADC_VD250MV_OFFSET			9	// �������� ��������� �� 250�� (� �����)
#define REG_ADC_VD250MV_K				10	// ����������� ��������� �� 250�� (� �) x1000
#define REG_ADC_VD250MV_FINE_P0			11	// ������� ������ ������������� �� 250�� P0 (� �������)
#define REG_ADC_VD250MV_FINE_P1			12	// ������� ������ ������������� �� 250�� P1 x1000
#define REG_ADC_VD250MV_FINE_P2			13	// ������� ������ ������������� �� 250�� P2 x1e6

#define REG_ADC_VD1500MV_OFFSET			14	// �������� ��������� �� 1500�� (� �����)
#define REG_ADC_VD1500MV_K				15	// ����������� ��������� �� 1500�� (� �) x1000
#define REG_ADC_VD1500MV_FINE_P0		16	// ������� ������ ������������� �� 1500�� P0 (� �������)
#define REG_ADC_VD1500MV_FINE_P1		17	// ������� ������ ������������� �� 1500�� P1 x1000
#define REG_ADC_VD1500MV_FINE_P2		18	// ������� ������ ������������� �� 1500�� P2 x1e6

#define REG_ADC_VD11V_OFFSET			19	// �������� ��������� �� 11� (� �����)
#define REG_ADC_VD11V_K					20	// ����������� ��������� �� 11� (� �) x1000
#define REG_ADC_VD11V_FINE_P0			21	// ������� ������ ������������� �� 11� P0 (� �������)
#define REG_ADC_VD11V_FINE_P1			22	// ������� ������ ������������� �� 11� P1 x1000
#define REG_ADC_VD11V_FINE_P2			23	// ������� ������ ������������� �� 11� P2 x1e6

#define REG_ADC_ID20MA_OFFSET			24	// �������� ��������� �� 2� (� �)
#define REG_ADC_ID20MA_K				25	// ����������� ��������� �� 2� (� �����)
#define REG_ADC_ID20MA_FINE_P0			26	// ������� ������ ������������� �� 2� P0 (� �������)
#define REG_ADC_ID20MA_FINE_P1			27	// ������� ������ ������������� �� 2� P1 x1000
#define REG_ADC_ID20MA_FINE_P2			28	// ������� ������ ������������� �� 2� P2 x1e6

#define REG_ADC_ID200MA_OFFSET			29	// �������� ��������� �� 2� (� �)
#define REG_ADC_ID200MA_K				30	// ����������� ��������� �� 2� (� �����)
#define REG_ADC_ID200MA_FINE_P0			31	// ������� ������ ������������� �� 2� P0 (� �������)
#define REG_ADC_ID200MA_FINE_P1			32	// ������� ������ ������������� �� 2� P1 x1000
#define REG_ADC_ID200MA_FINE_P2			33	// ������� ������ ������������� �� 2� P2 x1e6

#define REG_ADC_ID2A_OFFSET				34	// �������� ��������� �� 2� (� �)
#define REG_ADC_ID2A_K					35	// ����������� ��������� �� 2� (� �����)
#define REG_ADC_ID2A_FINE_P0			36	// ������� ������ ������������� �� 2� P0 (� �������)
#define REG_ADC_ID2A_FINE_P1			37	// ������� ������ ������������� �� 2� P1 x1000
#define REG_ADC_ID2A_FINE_P2			38	// ������� ������ ������������� �� 2� P2 x1e6

#define REG_ADC_ID20A_OFFSET			39	// �������� ��������� �� 270� (� �)
#define REG_ADC_ID20A_K					40	// ����������� ��������� �� 270� (� �����)
#define REG_ADC_ID20A_FINE_P0			41	// ������� ������ ������������� �� 270� P0 (� �������)
#define REG_ADC_ID20A_FINE_P1			42	// ������� ������ ������������� �� 270� P1 x1000
#define REG_ADC_ID20A_FINE_P2			43	// ������� ������ ������������� �� 270� P2 x1e6

#define REG_ADC_ID270A_OFFSET			44	// �������� ��������� �� 270� (� �)
#define REG_ADC_ID270A_K				45	// ����������� ��������� �� 270� (� �����)
#define REG_ADC_ID270A_FINE_P0			46	// ������� ������ ������������� �� 270� P0 (� �������)
#define REG_ADC_ID270A_FINE_P1			47	// ������� ������ ������������� �� 270� P1 x1000
#define REG_ADC_ID270A_FINE_P2			48	// ������� ������ ������������� �� 270� P2 x1e6

#define REG_DAC_I20MA_SET_OFFSET		49	// �������� ��� ��������� ���
#define REG_DAC_I20MA_SET_K				50	// ���������������� ����������� ��������� ���
#define REG_DAC_I200MA_SET_OFFSET		51	// �������� ��� ��������� ���
#define REG_DAC_I200MA_SET_K			52	// ���������������� ����������� ��������� ���
#define REG_DAC_I2A_SET_OFFSET			53	// �������� ��� ��������� ���
#define REG_DAC_I2A_SET_K				54	// ���������������� ����������� ��������� ���
#define REG_DAC_I20A_SET_OFFSET			55	// �������� ��� ��������� ���
#define REG_DAC_I20A_SET_K				56	// ���������������� ����������� ��������� ���
#define REG_DAC_I270A_SET_OFFSET		57	// �������� ��� ��������� ���
#define REG_DAC_I270A_SET_K				58	// ���������������� ����������� ��������� ���

#define REG_CTRL_P_COEF					59	// ���������������� ����������� ���������� (�1000)
#define REG_CTRL_I_COEF					60	// ������������ ����������� ���������� (�1000)

#define REG_MAX_PULSE_TO_PULSE_PAUSE	61	// �������� ����� ���������� �� ������������ ���� (� ��)

// ������������ �������� ������-������
#define REG_CURRENT_SETPOINT_LOW		128	// �������� ������� ���� (� ��)
#define REG_CURRENT_SETPOINT_HIGH		129	// �������� ������� ���� (� ��)
#define REG_VOLTAGE_DUT_LIM				130	// ���������� �������� ������� ���������� (� ��)

#define REG_EN_CURRENT_FB				131 // ������� ������ �������� ����� �� ����

//�������� �������
#define REG_DBG_DATA					140	// �������� ������ �������� �������� ������

// �������� ������ ������
#define REG_DEV_STATE					192	// ������� ���������
#define REG_FAULT_REASON				193	// ������� Fault
#define REG_DISABLE_REASON				194	// ������� Disable
#define REG_WARNING						195	// ������� Warning
#define REG_PROBLEM						196	// ������� Problem
#define REG_OP_RESULT					197	// ������� ���������� ��������

#define REG_IDUT_AVERAGE_LOW			250	// ���������� �������� ���� (� ��)
#define REG_IDUT_AVERAGE_HIGH			251	// ���������� �������� ���� (� ��)
#define REG_VDUT_AVERAGE				252	// ���������� �������� ���������� (� ��)
#define REG_ADC_VBAT_MEASURE			253	// �������� ���������� ������ ������� (� ��)
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
#define DF_BATTERY						1	// �������� ������ �������
#define DF_OVERCURRENT					2	// �������� ��� ���� �������������
#define DF_ERRORMAX						3	// ���������� ������������� �������� ������

// Problem
#define PROBLEM_NONE					0
#define PROBLEM_CURRENT_TO_HIGH			1

//  Warning
#define WARNING_NONE					0

// ENDPOINTS
//
#define EP_DUT_V						1		// ������������ ������ ���������� DUT (� �)
#define EP_DUT_I						2		// ������������ ������ ���� DUT (� ��)
#define EP_REG_ERROE					3		// ������������ ������ ������ (� �����)
#define EP_OUT_DATA						4		// ������������ ������ ���� DUT (� ��)
//
#define EP_DIAG_DUT_VDUT				4		// �������� ���������� Vdut �� ������� (� �)
#define EP_DIAG_DUT_IDUT				5		// �������� ���������� Idut �� ������� (� ��)

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1		//  ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED			2		//  �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY			3		//  ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD					4		//  ������������ ����

#endif //  __DEV_OBJ_DIC_H
