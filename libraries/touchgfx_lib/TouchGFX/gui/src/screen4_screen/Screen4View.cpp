#include <gui/screen4_screen/Screen4View.hpp>
#include "usart1.h"
Screen4View::Screen4View()
{

}

void Screen4View::setupScreen()
{
    Screen4ViewBase::setupScreen();
}

void Screen4View::tearDownScreen()
{
    Screen4ViewBase::tearDownScreen();
}

void Screen4View::handleTickEvent()
{
    Unicode::snprintfFloat(textArea1Buffer,TEXTAREA1_SIZE,"%.3f",HX711_Weight);
    textArea1.invalidate();
    Unicode::snprintf(textArea11Buffer,TEXTAREA11_SIZE,"%d",temp);
    textArea11.invalidate();
    circleProgress1.setValue(((MQ3_adc[0]*0.4*1000)/4096-20)/10);
    circleProgress1.invalidate();
    circleProgress1_1.setValue(((MQ3_adc[1]*0.4*1000)/4096-20)/10);
    circleProgress1_1.invalidate();
    circleProgress1_2.setValue(((MQ3_adc[2]*0.4*1000)/4096-20)/10);
    circleProgress1_2.invalidate();
    circleProgress1_3.setValue(((MQ3_adc[3]*0.4*1000)/4096-20)/10);
    circleProgress1_3.invalidate();
    circleProgress1_4.setValue(((MQ3_adc[4]*0.4*1000)/4096-20)/10);
    circleProgress1_4.invalidate();
    circleProgress1_5.setValue(((MQ3_adc[5]*0.4*1000)/4096-20)/10);
    circleProgress1_5.invalidate();
    dynamicGraph1.addDataPoint(diastolicPressure);
    dynamicGraph1.addDataPoint(systolicPressure);
    dynamicGraph1.addDataPoint(pulseRate);

}
