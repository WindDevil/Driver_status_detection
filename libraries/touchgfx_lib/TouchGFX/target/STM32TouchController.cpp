/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>
#include <rtthread.h>

rt_device_t touch;
struct rt_touch_data *read_data;

#ifdef __cplusplus
extern "C"{
#endif

#include "ft5426.h"
#include "touch.h"

#ifdef __cplusplus
}
#endif

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
    struct rt_touch_config cfg;

    cfg.dev_name = "i2c1";
    rt_hw_ft5426_init("touch", &cfg);

    touch = rt_device_find("touch");
    rt_device_open(touch, RT_DEVICE_FLAG_RDONLY);
    read_data = (struct rt_touch_data *)rt_calloc(1, sizeof(struct rt_touch_data));
}


bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */

    rt_device_read(touch, 0, read_data, 1);

    if ((read_data->event == RT_TOUCH_EVENT_DOWN)|| (read_data->event == RT_TOUCH_EVENT_MOVE))
    {
        //rt_kprintf("down x: %03d y: %03d", read_data->x_coordinate, read_data->y_coordinate);
        //rt_kprintf(" t: %d\n", read_data->timestamp);

        //x和y为传回给touchGFX的位置。
        y = read_data->x_coordinate;
        x = read_data->y_coordinate;
        return true;

    }
    else
    {
        return false;
    }
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

