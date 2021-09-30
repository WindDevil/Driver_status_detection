/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-17     11607       the first version
 */
#include "button.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "touch.h"
#include "rtdbg.h"
#include "ft5426.h"
#include "usart6.h"
#include "lcd_port.h"
#include "dfs_fs.h"
#include "drv_dcmi.h"
#include "tiny_jpeg.h"

#define USER_KEY GET_PIN(H,4)
#define THREAD_STACK_SIZE 1000
#define THREAD_STACK_BIG_SIZE 4096
#define THREAD_TIMESLICE 40
#define THREAD_LONG_TIMESLICE 200

//百度识别人脸
extern rt_err_t baidu_ai_sample(char *filename);
//拍照
extern int camera(int argc, char *argv);
//获取LCD
extern struct drv_lcd_device _lcd;
//换目录
extern int chdir(const char *path);

static rt_thread_t button_thread = RT_NULL;
static rt_thread_t button_init_thread = RT_NULL;
static rt_uint8_t thread_priority = 20;
static rt_uint8_t thread_low_priority = 10;

//人脸识别的结果
extern char result_Face[20];

int result=RT_EOK;

void save()
{
    int r=0;
    r=tje_encode_to_file_at_quality("hello.jpg",1,320,240,3,_lcd.lcd_info.framebuffer);
    rt_kprintf("%d\r\n",r);
}
//MSH_CMD_EXPORT(save,save);

void change_somthing()
{
    result=-RT_ERROR;
}
void button_entry()
{
    //设置USER_KEY引脚为输入模式
    rt_pin_mode(USER_KEY, PIN_MODE_INPUT);
    //绑定USER_KEY引脚中断回调函数
    rt_pin_attach_irq(USER_KEY, PIN_IRQ_MODE_FALLING, change_somthing, RT_NULL);
    //使能USER_KEY引脚中断
    rt_pin_irq_enable(USER_KEY, PIN_IRQ_ENABLE);
}
int create_button_init_thread(void)
{
    button_init_thread = rt_thread_create("button_init", button_entry,
                                     RT_NULL, THREAD_STACK_SIZE, thread_priority, THREAD_TIMESLICE);
    if (button_init_thread != RT_NULL)
    {
        rt_thread_startup(button_init_thread);
    }
    return 0;
}
INIT_APP_EXPORT(create_button_init_thread);

void button_thread_entry()
{
    while(1)
    {
        if(result==-RT_ERROR)
        {
            rt_kprintf("Hello\n");
            chdir("sdcard");
            rt_kprintf("cd \r\n");
            save();
            rt_kprintf("save \r\n");
            baidu_ai_sample("hello.jpg");
            rt_kprintf("baidu \r\n");
            result=RT_EOK;
            rt_kprintf("%s \r\n",result_Face);
        }
        rt_thread_delay(500);
    }
}

int create_button_thread(void)
{
    button_thread = rt_thread_create("button_init", button_thread_entry,
                                     RT_NULL, THREAD_STACK_BIG_SIZE, thread_low_priority, THREAD_LONG_TIMESLICE);
    if (button_thread != RT_NULL)
    {
        rt_thread_startup(button_thread);
    }
    return 0;
}
INIT_APP_EXPORT(create_button_thread);



