#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_START_PROCESS				3	// ������ �������� ������������ ��������
#define ACT_STOP_PROCESS				4	// ��������� �������� ������������ ��������
#define ACT_FAULT_CLEAR					5	// ������� fault
#define ACT_WARNING_CLEAR				6	// ������� warning

#define ACT_DBG_Implse_ExternalLED		10	// ���������� ��������� ������� ���������
#define ACT_DBG_CTRL_VDUTAmp11V			11	// ���������� ��������� ������ �������� ���������� DUT 11�
#define ACT_DBG_CTRL_VDUTAmp1500mV		12	// ���������� ��������� ������ �������� ���������� DUT 1.5�
#define ACT_DBG_CTRL_VDUTAmp250mV		13	// ���������� ��������� ������ �������� ���������� DUT 250��
#define ACT_DBG_CTRL_VDUTAmp30mV		14	// ���������� ��������� ������ �������� ���������� DUT 30��
#define ACT_DBG_EN_Range20mA			15	// ���������� ��������� ���� ����� ������ ������������ ���� �� 20��
#define ACT_DBG_EN_Range200mA			16	// ���������� ��������� ���� ����� ������ ������������ ���� �� 200��
#define ACT_DBG_EN_Range2A				17	// ���������� ��������� ���� ����� ������ ������������ ���� �� 2�
#define ACT_DBG_EN_Range20A				18	// ���������� ��������� ���� ����� ������ ������������ ���� �� 20�
#define ACT_DBG_EN_Range270A			19	// ���������� ��������� ���� ����� ������ ������������ ���� �� 270�
#define ACT_DBG_EN_BatteryDischarge		20	// ���������� ��������� ���� ������� �������
#define ACT_ACT_DBG_EN_PSBoardOutput	21	// ���������� ��������� ���������� ������ ������ �������
#define ACT_DBG_Impulse_ForceSYNC1		22	// ���������� ��������� ������� ������ �������������
#define ACT_DBG_Impulse_ForceSYNC2		23	// ���������� ��������� ������� ������ �������������
#define ACT_DBG_SendDataToDACx			24	// �������� �������� ������ �� ���
#define ACT_DBG_SendDataToOutRegister	25	// �������� �������� ������ �� ������� ��������� �������
#define ACT_DBG_MEASURE_ADC_CH			26	// ������ ������� ���

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
//�������� �������
#define REG_DBG_IOData					0	// �������� ������ �������� �������� ������
#define REG_DBG_ChanellSelect			1	// �������� ������� ������ ���

// ����������� ��������
#define REG_V_BAT_MEASURE				2	// ���������� �������� ���������� �� ������� (� �)
#define REG_V_BAT_OFFSET				3	// �������� ������������� ���������� ������� (� �����)
#define REG_V_BAT_K						4	// ����������� ��������� ���������� ��� (� ��) � ���������� (� �) x1000

#define REG_V_DUT_MEASURE				5	// ���������� �������� ���������� �� DUT (� �)
#define REG_V_DUT_OFFSET				6	// �������� ������������� ���������� DUT (� �����)
#define REG_V_DUT_K						7	// ����������� ��������� ���������� ��� (� ��) � ���������� (� �) x1000
#define REG_V_DUT_P0					8	// ������� ������ ������������� ���������� DUT P0 (� �������)
#define REG_V_DUT_P1					9	// ������� ������ ������������� ���������� DUT P1 x1000
#define REG_V_DUT_P2					10	// ������� ������ ������������� ���������� DUT P2 x1e6

#define REG_I_DUT_MEASURE				11	// ���������� �������� �������� ���� (� �)
#define REG_I_DUT_OFFSET				12	// �������� ������������� �������� ���� (� �����)
#define REG_I_DUT_K						13	// ����������� ��������� ���������� ��� (� ��) � ���������� (� �) x1000
#define REG_I_DUT_P0					14	// ������� ������ ������������� ���� DUT P0 (� �������)
#define REG_I_DUT_P1					15	// ������� ������ ������������� ���� DUT P1 x1000
#define REG_I_DUT_P2					16	// ������� ������ ������������� ���� DUT P2 x1e6

// ������������ �������� ������-������
#define REG_CURRENT_SETPOINT			128	// �������� ������� ���� (� �)

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

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED			2	//  �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY			3	//  ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD					4	//  ������������ ����

#endif //  __DEV_OBJ_DIC_H
