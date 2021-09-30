/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-25     11607       the first version
 */
#ifndef APPLICATIONS_USART1_H_
#define APPLICATIONS_USART1_H_


//���յ�������
extern char recivedData[50];
//������������
extern float HX711_Weight;
extern int MQ3_adc[6];
extern int HiLink_Move[3];
//����ѹ
extern int diastolicPressure;
//����ѹ
extern int systolicPressure;
//����
extern int pulseRate;
//�¶�
extern int temp;
//ECG
extern int ECG[10];


#endif /* APPLICATIONS_USART1_H_ */
