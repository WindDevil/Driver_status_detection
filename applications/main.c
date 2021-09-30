/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

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

#define LED_PIN GET_PIN(I, 8)

#define REST_PIN GET_PIN(D, 3)

extern int result;
rt_device_t touch;
rt_thread_t ft5426_thread;

struct rt_event ov2640_event;
extern rt_uint8_t model_input_data_rgb[];
extern rt_uint8_t model_input_data_gray[];
//保存照片
void save();
//获取LCD
extern struct drv_lcd_device _lcd;
//是否拍到照片
int got_Image=0;
//自动重连
extern void wlan_autoconnect_init(void);
//拍照
extern int camera(int argc, char *argv);
//换目录
extern int chdir(const char *path);
//百度人脸识别
extern rt_err_t baidu_ai_sample(char *filename);
//人脸识别的结果
extern char result_Face[20];

void ft5426_thread_entry(void *parameter)
{
    struct rt_touch_data *read_data;

    read_data = (struct rt_touch_data *)rt_calloc(1, sizeof(struct rt_touch_data));

    while(1)
    {
        rt_device_read(touch, 0, read_data, 1);

//        if (read_data->event == RT_TOUCH_EVENT_DOWN)
//        {
//            rt_kprintf("down x: %03d y: %03d", read_data->x_coordinate, read_data->y_coordinate);
//            rt_kprintf(" t: %d\n", read_data->timestamp);
//        }
//        if (read_data->event == RT_TOUCH_EVENT_MOVE)
//        {
//            rt_kprintf("move x: %03d y: %03d", read_data->x_coordinate, read_data->y_coordinate);
//            rt_kprintf(" t: %d\n", read_data->timestamp);
//        }
//        if (read_data->event == RT_TOUCH_EVENT_UP)
//        {
//            rt_kprintf("up   x: %03d y: %03d", read_data->x_coordinate, read_data->y_coordinate);
//            rt_kprintf(" t: %d\n\n", read_data->timestamp);
//        }

        rt_thread_delay(10);
    }

}

int ft5426_example(void)
{
    struct rt_touch_config cfg;
    cfg.dev_name = "i2c1";
    rt_hw_ft5426_init("touch", &cfg);

    touch=rt_device_find("touch");

    rt_device_open(touch, RT_DEVICE_FLAG_RDONLY);

    struct rt_touch_info info;
    rt_device_control(touch, RT_TOUCH_CTRL_GET_INFO, &info);

    LOG_I("type     :%d",info.type);
    LOG_I("vendor   :%d",info.vendor);
    LOG_I("point_num:%d",info.point_num);
    LOG_I("range_x  :%d",info.range_x);
    LOG_I("range_y  :%d",info.range_y);

    ft5426_thread=rt_thread_create("touch", ft5426_thread_entry, RT_NULL, 800, 10, 20);
    if(ft5426_thread==RT_NULL)
    {
        LOG_D("creat ft5426 thread err");
        return -RT_ENOMEM;
    }
    rt_thread_startup(ft5426_thread);

    return RT_EOK;
}
//INIT_APP_EXPORT(ft5426_example);

int main(void)
{

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    /* init Wi-Fi auto connect feature */
    wlan_autoconnect_init();
    /* enable auto reconnect on WLAN device */
    rt_wlan_config_autoreconnect(RT_TRUE);

    while(1)
    {
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
    }

    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


