/*
 * 用于和广和通模组进行通信
 * 使用串口6与其链接
 * */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "usart6.h"
#include "usart1.h"
#include <stdio.h>

#define THREAD_STACK_SIZE 1000
#define THREAD_TIMESLICE 40
#define SAMPLE_UART_NAME "uart6"

static rt_thread_t serial_thread = RT_NULL;
static rt_thread_t L610_thread = RT_NULL;
static rt_uint8_t thread_priority = 20;
static rt_device_t serial;
static struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
static struct rt_semaphore rx_sem;

static char str[] = "hello RT-Thread!\r\n";

static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void serial_read_entry(void *parameter)
{
    char ch;
    while (1)
    {
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }
//        ch = ch + 1;
        rt_kprintf("%c",ch);
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

        rt_thread_t thread = rt_thread_create("serial6_read", serial_read_entry, RT_NULL, 1024, 25, 10);

        ADP_L610_Init();

        if (thread != RT_NULL)
        {
            rt_thread_startup(thread);
        }
    }
}
int create_serial6_thread(void)
{
    serial_thread = rt_thread_create("serial6_init", serial_thread_entry,
                                     RT_NULL, THREAD_STACK_SIZE, thread_priority, THREAD_TIMESLICE);
    if (serial_thread != RT_NULL)
    {
        rt_thread_startup(serial_thread);
    }
    return 0;
}
INIT_APP_EXPORT(create_serial6_thread);

void ADP_L610_Init()
{
    const char SetMQTTUser[]="AT+MQTTUSER=1,\"L610\",\"123\"\r\n";
    const char ConnectMQTT_VisualDust[]="AT+MQTTOPEN=1,\"mqtt.visualdust.com\",1883,0,60\r\n";
    const char SubscribeMQTT_Chenhan[]="AT+MQTTSUB=1,\"chenhan\",0\r\n";
    const char ADP_L610_Write[]="AT+MQTTPUB=1,\"chenhan\",0,1,\"Hello VisualDust\"\r\n";
    const char MIPCALL[]="AT+MIPCALL=1\r\n";

    rt_device_write(serial, 0, MIPCALL, 15);
    rt_thread_delay(200);
    rt_device_write(serial, 0, SetMQTTUser, 29);
    rt_thread_delay(200);
    rt_device_write(serial, 0, ConnectMQTT_VisualDust, 48);
    rt_thread_delay(200);
    rt_device_write(serial, 0, SubscribeMQTT_Chenhan, 27);
    rt_thread_delay(200);
    rt_device_write(serial, 0, ADP_L610_Write, 48);
    rt_thread_delay(200);

}

static void ADP_L610_Serial_Update()
{
    //char hello[]="AT+MQTTPUB=1,\"chenhan\",0,1,\"Hello VisualDust\"\r\n";
    static char ADP_L610_Write[300]={};
    sprintf(ADP_L610_Write,"AT+MQTTPUB=1,\"chenhan\",0,1,"
            "\""
            "%.3f,"
            "%d,%d,%d,%d,%d,%d,"
            "%d,%d,%d,"
            "%d,"
            "%d,"
            "%d,"
            "%d,"
            "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d"
            "\"\r\n"
            ,HX711_Weight\
            ,MQ3_adc[0]\
            ,MQ3_adc[1]\
            ,MQ3_adc[2]\
            ,MQ3_adc[3]\
            ,MQ3_adc[4]\
            ,MQ3_adc[5]\
            ,HiLink_Move[0]\
            ,HiLink_Move[1]\
            ,HiLink_Move[2]\
            ,diastolicPressure\
            ,systolicPressure\
            ,pulseRate\
            ,temp\
            ,ECG[0]\
            ,ECG[1]\
            ,ECG[2]\
            ,ECG[3]\
            ,ECG[4]\
            ,ECG[5]\
            ,ECG[6]\
            ,ECG[7]\
            ,ECG[8]\
            ,ECG[9]\
            );
    //rt_kprintf(ADP_L610_Write);
    rt_device_write(serial, 0, ADP_L610_Write, 300);
    rt_thread_delay(200);
}

void ADP_L610_MQTT_Update()
{
   L610_thread = rt_thread_create("ADP_L610_Serial_Update", ADP_L610_Serial_Update,
                                         RT_NULL, THREAD_STACK_SIZE, thread_priority, THREAD_TIMESLICE);
    if (L610_thread != RT_NULL)
    {
        rt_thread_startup(L610_thread);
    }

}
