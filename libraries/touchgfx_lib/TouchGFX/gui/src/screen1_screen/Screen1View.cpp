#include <gui/screen1_screen/Screen1View.hpp>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "string.h"

#define LED_PIN GET_PIN(I, 8)

#define REST_PIN GET_PIN(D, 3)

static bool flag=1;
extern char result_Face[20];

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}
void Screen1View::ToggleLED()
{
    if(flag==1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        flag=0;
    }
    else
    {
        rt_pin_write(LED_PIN, PIN_LOW);
        flag=1;
    }

}
void Screen1View::handleTickEvent()
{
    if(strcmp(result_Face,"chenhan")==0)
    {
        textArea3.setVisible(true);
        textArea3.invalidate();
    }

}
