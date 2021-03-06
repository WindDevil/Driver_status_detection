/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAINVIEWBASE_HPP
#define MAINVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TiledImage.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/BoxWithBorder.hpp>
#include <touchgfx/widgets/graph/GraphWrapAndClear.hpp>
#include <touchgfx/widgets/graph/GraphElements.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/graph/GraphLabels.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/Button.hpp>

class MainViewBase : public touchgfx::View<MainPresenter>
{
public:
    MainViewBase();
    virtual ~MainViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::TiledImage tiledImage1;
    touchgfx::Image background;
    touchgfx::BoxWithBorder graphBackground;
    touchgfx::GraphWrapAndClear<100> graph;
    touchgfx::GraphElementLine graphLine1;
    touchgfx::PainterRGB888 graphLine1Painter;
    touchgfx::GraphElementGridY graphMajorYAxisGrid;
    touchgfx::GraphLabelsX graphMajorXAxisLabel;
    touchgfx::GraphLabelsY graphMajorYAxisLabel;
    touchgfx::Slider sliderResolution;
    touchgfx::Button button1;
    touchgfx::Button button2;
    touchgfx::Button button3;
    touchgfx::Button button4;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<MainViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 15360;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // MAINVIEWBASE_HPP
