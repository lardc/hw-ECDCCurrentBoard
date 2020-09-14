#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_START_PROCESS				3	// ������ �������� ������������ ��������
#define ACT_STOP_PROCESS				4	// ��������� �������� ������������ ��������
#define ACT_FAULT_CLEAR					5	// ������� fault
#define ACT_WARNING_CLEAR				6	// ������� warning

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

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������

#define REG_ADC_VBAT_MEASURE			1	// �������� ���������� ������ ������� (� �)
#define REG_ADC_VBAT_OFFSET				2	// �������� ������������� ���������� ������� (� �����)
#define REG_ADC_VBAT_K					3	// ����������� ��������� ���������� ��� (� ��) � ���������� (� �) x1000

#define REG_ADC_VD250MV_OFFSET			4	// �������� ��������� �� 250�� (� �����)
#define REG_ADC_VD250MV_K				5	// ����������� ��������� �� 250�� (� �) x1000
#define REG_ADC_VD250MV_FINE_P0			6	// ������� ������ ������������� �� 250�� P0 (� �������)
#define REG_ADC_VD250MV_FINE_P1			7	// ������� ������ ������������� �� 250�� P1 x1000
#define REG_ADC_VD250MV_FINE_P2			8	// ������� ������ ������������� �� 250�� P2 x1e6

#define REG_ADC_VD11V_OFFSET			9	// �������� ��������� �� 11� (� �����)
#define REG_ADC_VD11V_K					10	// ����������� ��������� �� 11� (� �) x1000
#define REG_ADC_VD11V_FINE_P0			11	// ������� ������ ������������� �� 11� P0 (� �������)
#define REG_ADC_VD11V_FINE_P1			12	// ������� ������ ������������� �� 11� P1 x1000
#define REG_ADC_VD11V_FINE_P2			13	// ������� ������ ������������� �� 11� P2 x1e6

#define REG_ADC_ID2A_OFFSET				14	// �������� ��������� �� 2� (� �)
#define REG_ADC_ID2A_K					15	// ����������� ��������� �� 2� (� �����)
#define REG_ADC_ID2A_FINE_P0			16	// ������� ������ ������������� �� 2� P0 (� �������)
#define REG_ADC_ID2A_FINE_P1			17	// ������� ������ ������������� �� 2� P1 x1000
#define REG_ADC_ID2A_FINE_P2			18	// ������� ������ ������������� �� 2� P2 x1e6

#define REG_ADC_ID270A_OFFSET			19	// �������� ��������� �� 270� (� �)
#define REG_ADC_ID270A_K				20	// ����������� ��������� �� 270� (� �����)
#define REG_ADC_ID270A_FINE_P0			21	// ������� ������ ������������� �� 270� P0 (� �������)
#define REG_ADC_ID270A_FINE_P1			22	// ������� ������ ������������� �� 270� P1 x1000
#define REG_ADC_ID270A_FINE_P2			23	// ������� ������ ������������� �� 270� P2 x1e6

#define REG_DAC_I_SET_K					24	// ���������������� ����������� ��������� ���
#define REG_DAC_I_SET_OFFSET			25	// �������� ��� ��������� ���

#define REG_CTRL_P_COEF					26	// ���������������� ����������� ���������� (�1000)
#define REG_CTRL_I_COEF					27	// ������������ ����������� ���������� (�1000)

// ������������ �������� ������-������
#define REG_CURRENT_SETPOINT			128	// �������� ������� ���� (� �)
#define REG_VOLTAGE_SETPOINT			129	// �������� ������� ���� (� ��)
#define REG_VDUT_AVERAGE				130	// �������� ������� ���� (� �)
#define REG_IDUT_AVERAGE				131	// �������� ������� ���� (� ��)

//�������� �������
#define REG_DBG_DATA					140	// �������� ������ �������� �������� ������
#define REG_DBG_ENABLE_DEVICE			141	// �������� ������� ������ ���

// �������� ������ ������
#define REG_DEV_STATE					192	// ������� ���������
#define REG_FAULT_REASON				193	// ������� Fault
#define REG_DISABLE_REASON				194	// ������� Disable
#define REG_WARNING						195	// ������� Warning
#define REG_PROBLEM						196	// ������� Problem
#define REG_OP_RESULT					197	// ������� ���������� ��������
//
#define REG_ACTUAL_BAT_VOLTAGE			200	// ������� ���������� �� ������� (� �)
// -----------------------------

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0
#define DF_BATTERY						1	// �������� ������ �������

// Problem
#define PROBLEM_NONE					0

//  Warning
#define WARNING_NONE					0

// ENDPOINTS
//
#define EP_DUT_V						1		// ������������ ������ ���������� DUT (� �)
#define EP_DUT_I						2		// ������������ ������ ���� DUT (� ��)
//
#define EP_DIAG_DUT_VDUT				4		// �������� ���������� Vdut �� ������� (� �)
#define EP_DIAG_DUT_IDUT				5		// �������� ���������� Idut �� ������� (� ��)

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED			2	//  �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY			3	//  ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD					4	//  ������������ ����

#endif //  __DEV_OBJ_DIC_H
