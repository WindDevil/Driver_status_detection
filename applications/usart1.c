/*
 * 用于和ESP32进行通信
 * 使用串口1与其链接
 * */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "usart1.h"
#include "usart6.h"
#include <stdio.h>

#define THREAD_STACK_SIZE 1000
#define THREAD_TIMESLICE 40
#define SAMPLE_UART_NAME "uart1"

static rt_thread_t serial_thread = RT_NULL;
static rt_uint8_t thread_priority = 20;
static rt_device_t serial;
static struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
static struct rt_semaphore rx_sem;

static char str[] = "hello RT-Thread!\r\n";

//接收到的数据
char recivedData[50];
//解析到的数据
float HX711_Weight;
int MQ3_adc[6];
int HiLink_Move[3];
//舒张压
int diastolicPressure;
//收缩压
int systolicPressure;
//脉率
int pulseRate;
//温度
int temp;
//ECG
int ECG[10];

static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void serial_read_entry(void *parameter)
{
    char ch;
    uint16_t UsartFlag=0;

    int i=0;
    int j=0;
    char cc=0xcc;

    while (1)
    {
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }
        if((UsartFlag&0x8000)==0)
        {
            if(UsartFlag&0x4000)
            {
                recivedData[UsartFlag&0X3fff]=ch;
                UsartFlag++;
                if((UsartFlag&0X3fff)>=50)
                {
                    UsartFlag|=0x8000;
                }
            }
            else if(ch==0xfd)
            {
                UsartFlag|=0x4000;
                recivedData[UsartFlag&0X3fff]=ch;
                UsartFlag++;
            }
        }
        if(UsartFlag&0x8000)
        {
            rt_device_write(serial, 0, &cc ,1 );
            for (i = 0,j = 0; i < 6; i++, j = j + 2)
            {
                MQ3_adc[i] = recivedData[j + 1] * 256 + recivedData[j + 2];
            }

            HX711_Weight=*((float *)(recivedData + 13));

            for (i = 0; i < 3; i = i + 1)
            {
                HiLink_Move[i] = recivedData[i + 17];
            }
            diastolicPressure = recivedData[20];
            systolicPressure = recivedData[21];
            pulseRate=recivedData[22];
            temp=(recivedData[23]*256+recivedData[24])/256;
            for (i = 0,j = 0; i < 8; i++,j = j+2 )
            {
                ECG[i]=recivedData[j + 25]*256+recivedData[j + 26];
            }
            ADP_L610_MQTT_Update();
            UsartFlag=0;
        }
    }
}

static void serial_thread_entry(void *params)
{
    serial = rt_device_find(SAMPLE_UART_NAME);
    if (serial != RT_NULL)
    {
        config.baud_rate = BAUD_RATE_115200;
        config.data_bits = DATA_BITS_8;
        config.stop_bits = STOP_BITS_1;
        config.bufsz = 128;
        config.parity = PARITY_NONE;

        rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);

        rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);

        rt_device_write(serial, 0, str, (sizeof(str) - 1));

        rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

        rt_device_set_rx_indicate(serial, uart_input);

        rt_thread_t thread = rt_thread_create("serial_read", serial_read_entry, RT_NULL, 1024, 25, 10);

        if (thread != RT_NULL)
        {
            rt_thread_startup(thread);
        }
    }
}
int create_serial1_thread(void)
{
    serial_thread = rt_thread_create("serial_init", serial_thread_entry,
                                     RT_NULL, THREAD_STACK_SIZE, thread_priority, THREAD_TIMESLICE);
    if (serial_thread != RT_NULL)
    {
        rt_thread_startup(serial_thread);
    }
    return 0;
}

INIT_APP_EXPORT(create_serial1_thread);
