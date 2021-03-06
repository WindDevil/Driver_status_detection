/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

Screen1ViewBase::Screen1ViewBase() :
    buttonCallback(this, &Screen1ViewBase::buttonCallbackHandler)
{

    __background.setPosition(0, 0, 1024, 600);
    __background.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    tiledImage1.setBitmap(touchgfx::Bitmap(BITMAP_PPBG_ID));
    tiledImage1.setPosition(0, 0, 1024, 600);
    tiledImage1.setOffset(0, 0);

    button1.setXY(935, 549);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_BACK2_ID), touchgfx::Bitmap(BITMAP_BACK2_ID));
    button1.setAction(buttonCallback);

    textArea1.setXY(123, 239);
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 186, 0));
    textArea1.setLinespacing(0);
    textArea1Buffer[0] = 0;
    textArea1.setWildcard(textArea1Buffer);
    textArea1.resizeToCurrentText();
    textArea1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID22));

    textArea2.setXY(37, 92);
    textArea2.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 186, 0));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID23));

    textArea3.setXY(621, 239);
    textArea3.setVisible(false);
    textArea3.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textArea3.setLinespacing(0);
    textArea3.setTypedText(touchgfx::TypedText(T_SINGLEUSEID24));

    add(__background);
    add(tiledImage1);
    add(button1);
    add(textArea1);
    add(textArea2);
    add(textArea3);
}

void Screen1ViewBase::setupScreen()
{

}

void Screen1ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Interaction1
        //When button1 clicked change screen to Main
        //Go to Main with no screen transition
        application().gotoMainScreenNoTransition();
    }
}
