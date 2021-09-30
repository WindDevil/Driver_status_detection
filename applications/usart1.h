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


//接收到的数据
extern char recivedData[50];
//解析到的数据
extern float HX711_Weight;
extern int MQ3_adc[6];
extern int HiLink_Move[3];
//舒张压
extern int diastolicPressure;
//收缩压
extern int systolicPressure;
//脉率
extern int pulseRate;
//温度
extern int temp;
//ECG
extern int ECG[10];


#endif /* APPLICATIONS_USART1_H_ */
