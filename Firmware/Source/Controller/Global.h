#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS		1000	// ������� ���������� SCCI (� ��)
#define EP_WRITE_COUNT			0		// ���������� �������� ��� ������
#define EP_COUNT				2		// ���������� �������� ��� ������
#define VALUES_x_SIZE			1000	// ������ �������� ��������
#define ENABLE_LOCKING			FALSE	// ������ NV ��������� �������
#define PULSES_MAX				10		// ������������ ���������� ��������� �� ���������

// ��������� ���������
#define TIME_LED_BLINK			500		// ������� ����������� (� ��)
#define TIME_EXT_LED_BLINK		500		// ����� ��������� �������� ���������� (� ��)
#define TIME_BAT_CHARGE			5000	// ����� ������ �������  (� ��)
#define Pulse2PulsePause		2000	// ����� ���� ���������� (� ��)

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

#define END_CURRENT_PULSE		0		// �������� ������� ���� 0
#define LOCK_ANALOG_CH			0		// ���������� �� � ������� ��������� ����

#define I_ANALOG_2A				0x0024	// ����� ������ ��������� �� � ��������� ������ �� 2�
#define I_ANALOG_20A			0x0012	// ����� ������ ��������� �� � ��������� ������ �� 20�
#define I_ANALOG_270A			0x0009	// ����� ������ ��������� �� � ��������� ������ �� 270�

#define I_SHUNT_20MA			100000	// ���� 100000 ��� �� 20��
#define I_SHUNT_200MA			10000	// ���� 10000 ��� �� 200��
#define I_SHUNT_2A				500		// ���� 500 ��� �� 2�
#define I_SHUNT_20A				50		// ���� 50 ��� �� 20�
#define I_SHUNT_270A			0.5		// ���� 0.5 ��� �� 270�

//��������� ��������� ����������
#define V_RANGE_30MV			30		// �������� �� 20��
#define V_RANGE_250MV			250		// �������� �� 200��
#define V_RANGE_1500MV			1500	// �������� �� 2�
#define V_RANGE_11V				11000	// �������� �� 20�

// High-speed sampling
#define DMA_ADC_DUT_V_CHANNEL			DMA1_Channel1	// ����� DMA ��� ��� ����������
#define DMA_ADC_DUT_I_CHANNEL			DMA2_Channel1	// ����� DMA ��� ��� ����
//
#define ADC1_VOLTAGE_CHANNEL			1				// ���1 ����� ������ ����������
#define ADC2_CURRENT_CHANNEL			1				// ���2 ����� ������ ����


#endif //  __GLOBAL_H
