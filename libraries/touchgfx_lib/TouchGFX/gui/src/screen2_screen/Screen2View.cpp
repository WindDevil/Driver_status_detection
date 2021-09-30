#include <gui/screen2_screen/Screen2View.hpp>
#include <math.h>
#include <stdlib.h>
#include "usart1.h"

static int ECG_ALL[100];
static int j;
Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::handleTickEvent()
{
    tickCounter++;
    int i=0;
    if (tickCounter % 2 == 0)
    {
        for(i=0;i<10;i++)
        {
           if(ECG[i]<10000)
           {
               if(j<100)
               {
                   ECG_ALL[j++]=ECG[i];
               }
               else
               {
                   j=0;
                   ECG_ALL[j++]=ECG[i];
               }
           }
        }
        for(i=0;i<100;i++)
        {
            dynamicGraph2.addDataPoint(ECG_ALL[i]);
        }
    }
}
