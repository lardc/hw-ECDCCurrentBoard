#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS		1000	// ������� ���������� SCCI (� ��)
#define EP_WRITE_COUNT			0		// ���������� �������� ��� ������
#define EP_COUNT				0		// ���������� �������� ��� ������
#define ENABLE_LOCKING			FALSE	// ������ NV ��������� �������

// ��������� ���������
#define TIME_LED_BLINK			500		// ������� ����������� (� ��)
#define TIME_EXT_LED_BLINK		500		// ����� ��������� �������� ���������� (� ��)
#define TIME_BAT_CHARGE			1000	// ����� ������ �������  (� ��)

// ��������� ���
#define V_ADC1_CH				1		// ����� ������ ��� V_DUT
#define I_ADC2_CH				1		// ����� ������ ��� I_DUT
#define VBAT_ADC2_CH			3		// ����� ������ ��� �������
#define ADC_REF_VOLTAGE			3300.0f	// ������� ���������� (� ��)
#define ADC_RESOLUTION			4095	// ���������� ���

// ��������� ���
#define DAC_REF_VOLTAGE			3300.0f	// ������� ���������� (� ��)
#define DAC_RESOLUTION			4095	// ���������� ���

// ��������� �������
#define BAT_VOLTAGE_THRESHOLD	50		// ��������� ���������� ������� (� �)
#define BAT_VOLTAGE_DELTA		5.0f	// ���������� ����������� ���������� (� �)

//��������� ������������ ����
#define I_RANGE_20MA			20		// �������� �� 20��
#define I_RANGE_200MA			200		// �������� �� 200��
#define I_RANGE_2A				2000	// �������� �� 2�
#define I_RANGE_20A				20000	// �������� �� 20�
#define I_RANGE_270A			270000	// �������� �� 270�

#endif //  __GLOBAL_H
