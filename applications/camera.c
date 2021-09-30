/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-27     11607       the first version
 */
#include <drv_dcmi.h>

#define THREAD_STACK_SIZE 1000
#define THREAD_TIMESLICE 40

extern int rt_gc0328c_init(void);

struct rt_event ov2640_event;
static rt_thread_t camera_thread = RT_NULL;
static rt_uint8_t thread_priority = 20;

void camera_thread_entry()
{
    /*初始化事件*/
    rt_event_init(&ov2640_event, "ov2640", RT_IPC_FLAG_FIFO);
    rt_gc0328c_init();
    DCMI_Start();
    while(1)
    {
        rt_event_recv(&ov2640_event,
                            1,
                            RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER,
                            RT_NULL);
        DCMI_Start();
    }

}


int create_camera_thread(void)
{
    camera_thread = rt_thread_create("camera_thread", camera_thread_entry,
                                     RT_NULL, THREAD_STACK_SIZE, thread_priority, THREAD_TIMESLICE);
    if (camera_thread != RT_NULL)
    {
        rt_thread_startup(camera_thread);
    }
    return 0;
}
INIT_APP_EXPORT(create_camera_thread);

