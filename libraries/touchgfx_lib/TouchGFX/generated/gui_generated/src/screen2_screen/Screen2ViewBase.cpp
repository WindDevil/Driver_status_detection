/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

Screen2ViewBase::Screen2ViewBase() :
    buttonCallback(this, &Screen2ViewBase::buttonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 1024, 600);
    __background.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    tiledImage1.setBitmap(touchgfx::Bitmap(BITMAP_PPBG_ID));
    tiledImage1.setPosition(0, 0, 1024, 600);
    tiledImage1.setOffset(0, 0);

    boxWithBorder1.setPosition(144, 56, 737, 488);
    boxWithBorder1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    boxWithBorder1.setBorderColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    boxWithBorder1.setBorderSize(0);

    dynamicGraph2.setScale(1);
    dynamicGraph2.setGraphRangeX(0, 50);
    dynamicGraph2.setPosition(192, 116, 640, 388);
    dynamicGraph2.setGraphAreaMargin(20, 70, 20, 30);
    dynamicGraph2.setGraphAreaPadding(0, 0, 0, 0);
    dynamicGraph2.setGraphRangeY(0, 10000);

    dynamicGraph2MajorYAxisGrid.setScale(1);
    dynamicGraph2MajorYAxisGrid.setColor(touchgfx::Color::getColorFrom24BitRGB(20, 151, 197));
    dynamicGraph2MajorYAxisGrid.setInterval(2000);
    dynamicGraph2MajorYAxisGrid.setLineWidth(1);
    dynamicGraph2.addGraphElement(dynamicGraph2MajorYAxisGrid);

    dynamicGraph2MajorYAxisLabel.setScale(1);
    dynamicGraph2MajorYAxisLabel.setInterval(2000);
    dynamicGraph2MajorYAxisLabel.setLabelTypedText(touchgfx::TypedText(T_SINGLEUSEID21));
    dynamicGraph2MajorYAxisLabel.setColor(touchgfx::Color::getColorFrom24BitRGB(20, 151, 197));
    dynamicGraph2.addLeftElement(dynamicGraph2MajorYAxisLabel);

    dynamicGraph2Line1.setScale(1);
    dynamicGraph2Line1Painter.setColor(touchgfx::Color::getColorFrom24BitRGB(20, 151, 197));
    dynamicGraph2Line1.setPainter(dynamicGraph2Line1Painter);
    dynamicGraph2Line1.setLineWidth(2);
    dynamicGraph2.addGraphElement(dynamicGraph2Line1);

    dynamicGraph2.addDataPoint(4184.88637331318f);
    dynamicGraph2.addDataPoint(3837.30339228702f);
    dynamicGraph2.addDataPoint(3992.2697213031f);
    dynamicGraph2.addDataPoint(4699.64219653493f);
    dynamicGraph2.addDataPoint(5861.842922892f);
    dynamicGraph2.addDataPoint(7254.73540057343f);
    dynamicGraph2.addDataPoint(8580.09236152842f);
    dynamicGraph2.addDataPoint(9536.90619137549f);
    dynamicGraph2.addDataPoint(9894.14952245861f);
    dynamicGraph2.addDataPoint(9547.20993587515f);
    dynamicGraph2.addDataPoint(8544.18622617581f);
    dynamicGraph2.addDataPoint(7075.58131912159f);
    dynamicGraph2.addDataPoint(5429.85562862347f);
    dynamicGraph2.addDataPoint(3925.63690775495f);
    dynamicGraph2.addDataPoint(2837.06990084173f);
    dynamicGraph2.addDataPoint(2330.44908323309f);
    dynamicGraph2.addDataPoint(2427.50017260248f);
    dynamicGraph2.addDataPoint(3004.13898364561f);
    dynamicGraph2.addDataPoint(3824.85166967544f);
    dynamicGraph2.addDataPoint(4604.11731872083f);
    dynamicGraph2.addDataPoint(5079.68537272793f);
    dynamicGraph2.addDataPoint(5079.63284093694f);
    dynamicGraph2.addDataPoint(4566.66870604719f);
    dynamicGraph2.addDataPoint(3648.75157746704f);
    dynamicGraph2.addDataPoint(2553.36053367236f);
    dynamicGraph2.addDataPoint(1571.6911120125f);
    dynamicGraph2.addDataPoint(986.443070290573f);
    dynamicGraph2.addDataPoint(1000.91749061929f);
    dynamicGraph2.addDataPoint(1686.848890645f);
    dynamicGraph2.addDataPoint(2963.84104930871f);
    dynamicGraph2.addDataPoint(4615.56086356738f);
    dynamicGraph2.addDataPoint(6338.86374347909f);
    dynamicGraph2.addDataPoint(7813.97811087802f);
    dynamicGraph2.addDataPoint(8778.7235668557f);
    dynamicGraph2.addDataPoint(9088.75596017796f);
    dynamicGraph2.addDataPoint(8749.24582031922f);
    dynamicGraph2.addDataPoint(7910.37979169433f);
    dynamicGraph2.addDataPoint(6827.91666192621f);
    dynamicGraph2.addDataPoint(5798.56000895405f);
    dynamicGraph2.addDataPoint(5086.05198998098f);
    dynamicGraph2.addDataPoint(4856.13277773824f);
    dynamicGraph2.addDataPoint(5136.30887372826f);
    dynamicGraph2.addDataPoint(5810.2659239645f);
    dynamicGraph2.addDataPoint(6648.24900591236f);
    dynamicGraph2.addDataPoint(7365.89586662979f);
    dynamicGraph2.addDataPoint(7697.01581845859f);
    dynamicGraph2.addDataPoint(7462.37042383837f);
    dynamicGraph2.addDataPoint(6617.47020888981f);
    dynamicGraph2.addDataPoint(5267.53174488522f);
    dynamicGraph2.addDataPoint(3645.76906768538f);
    dynamicGraph2.addDataPoint(2060.17360886525f);
    dynamicGraph2.addDataPoint(821.65859957103f);
    dynamicGraph2.addDataPoint(171.017591550376f);
    dynamicGraph2.addDataPoint(222.459445855639f);
    dynamicGraph2.addDataPoint(937.443524406299f);
    dynamicGraph2.addDataPoint(2135.15019844319f);
    dynamicGraph2.addDataPoint(3536.98159016447f);
    dynamicGraph2.addDataPoint(4834.18841687742f);
    dynamicGraph2.addDataPoint(5762.08840203051f);
    dynamicGraph2.addDataPoint(6162.76001301681f);
    dynamicGraph2.addDataPoint(6020.94609414241f);
    dynamicGraph2.addDataPoint(5464.48621493031f);
    dynamicGraph2.addDataPoint(4729.30548517951f);
    dynamicGraph2.addDataPoint(4097.67726503537f);
    dynamicGraph2.addDataPoint(3825.03553053621f);
    dynamicGraph2.addDataPoint(4073.41769104129f);
    dynamicGraph2.addDataPoint(4867.99300647853f);
    dynamicGraph2.addDataPoint(6087.47313566189f);
    dynamicGraph2.addDataPoint(7490.8869681195f);
    dynamicGraph2.addDataPoint(8774.28255258285f);
    dynamicGraph2.addDataPoint(9643.56429231988f);
    dynamicGraph2.addDataPoint(9885.69553507049f);
    dynamicGraph2.addDataPoint(9420.86559293794f);
    dynamicGraph2.addDataPoint(8322.84856430884f);
    dynamicGraph2.addDataPoint(6802.53684476014f);
    dynamicGraph2.addDataPoint(5158.61708388793f);
    dynamicGraph2.addDataPoint(3707.37351443877f);
    dynamicGraph2.addDataPoint(2708.68656025267f);
    dynamicGraph2.addDataPoint(2306.21017642686f);
    dynamicGraph2.addDataPoint(2496.22118127291f);
    dynamicGraph2.addDataPoint(3132.60761261815f);
    dynamicGraph2.addDataPoint(3966.61289098562f);
    dynamicGraph2.addDataPoint(4711.44486632227f);
    dynamicGraph2.addDataPoint(5115.7859992489f);
    dynamicGraph2.addDataPoint(5028.07360428688f);
    dynamicGraph2.addDataPoint(4435.70331057682f);
    dynamicGraph2.addDataPoint(3469.47374199996f);
    dynamicGraph2.addDataPoint(2372.12981452847f);
    dynamicGraph2.addDataPoint(1438.68411201551f);
    dynamicGraph2.addDataPoint(943.137208664284f);
    dynamicGraph2.addDataPoint(1069.58052755801f);
    dynamicGraph2.addDataPoint(1864.62168813494f);
    dynamicGraph2.addDataPoint(3222.88166931987f);
    dynamicGraph2.addDataPoint(4909.23576058158f);
    dynamicGraph2.addDataPoint(6612.49637899569f);
    dynamicGraph2.addDataPoint(8017.54869312132f);
    dynamicGraph2.addDataPoint(8878.43865619617f);
    dynamicGraph2.addDataPoint(9074.68290381271f);
    dynamicGraph2.addDataPoint(8637.16706495825f);
    dynamicGraph2.addDataPoint(7737.43721736299f);

    button1.setXY(928, 551);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_BACK2_ID), touchgfx::Bitmap(BITMAP_BACK2_ID));
    button1.setAction(buttonCallback);

    add(__background);
    add(tiledImage1);
    add(boxWithBorder1);
    add(dynamicGraph2);
    add(button1);
}

void Screen2ViewBase::setupScreen()
{

}

void Screen2ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Interaction1
        //When button1 clicked change screen to Main
        //Go to Main with no screen transition
        application().gotoMainScreenNoTransition();
    }
}
