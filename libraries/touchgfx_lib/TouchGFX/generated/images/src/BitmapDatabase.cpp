// 4.15.0 0xbbeaadc7
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_back[]; // BITMAP_BACK_ID = 0, Size: 200x200 pixels
extern const unsigned char image_back2[]; // BITMAP_BACK2_ID = 1, Size: 32x32 pixels
extern const unsigned char image_blue_backgrounds_main_bg_480x272px[]; // BITMAP_BLUE_BACKGROUNDS_MAIN_BG_480X272PX_ID = 2, Size: 480x272 pixels
extern const unsigned char image_blue_progressindicators_bg_medium_circle_indicator_bg_line_full[]; // BITMAP_BLUE_PROGRESSINDICATORS_BG_MEDIUM_CIRCLE_INDICATOR_BG_LINE_FULL_ID = 3, Size: 104x104 pixels
extern const unsigned char image_blue_slider_vertical_small_indicators_slider3_vertical_round_nob[]; // BITMAP_BLUE_SLIDER_VERTICAL_SMALL_INDICATORS_SLIDER3_VERTICAL_ROUND_NOB_ID = 4, Size: 34x54 pixels
extern const unsigned char image_blue_slider_vertical_small_slider3_vertical_round_back[]; // BITMAP_BLUE_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_BACK_ID = 5, Size: 20x172 pixels
extern const unsigned char image_blue_slider_vertical_small_slider3_vertical_round_fill[]; // BITMAP_BLUE_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_FILL_ID = 6, Size: 20x172 pixels
extern const unsigned char image_ppbg[]; // BITMAP_PPBG_ID = 7, Size: 1024x600 pixels
extern const unsigned char image_yac[]; // BITMAP_YAC_ID = 8, Size: 200x200 pixels
extern const unsigned char image_yht[]; // BITMAP_YHT_ID = 9, Size: 200x200 pixels
extern const unsigned char image_yid[]; // BITMAP_YID_ID = 10, Size: 200x200 pixels
extern const unsigned char image_yrd[]; // BITMAP_YRD_ID = 11, Size: 200x200 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] =
{
    { image_back, 0, 200, 200, 17, 35, 108, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 7, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_back2, 0, 32, 32, 9, 26, 11, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 1, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_backgrounds_main_bg_480x272px, 0, 480, 272, 0, 0, 480, (uint8_t)(touchgfx::Bitmap::RGB888) >> 3, 272, (uint8_t)(touchgfx::Bitmap::RGB888) & 0x7 },
    { image_blue_progressindicators_bg_medium_circle_indicator_bg_line_full, 0, 104, 104, 85, 28, 13, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 48, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_slider_vertical_small_indicators_slider3_vertical_round_nob, 0, 34, 54, 5, 7, 24, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 38, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_slider_vertical_small_slider3_vertical_round_back, 0, 20, 172, 0, 10, 20, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 152, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_slider_vertical_small_slider3_vertical_round_fill, 0, 20, 172, 0, 10, 20, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 152, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_ppbg, 0, 1024, 600, 0, 0, 1024, (uint8_t)(touchgfx::Bitmap::RGB888) >> 3, 600, (uint8_t)(touchgfx::Bitmap::RGB888) & 0x7 },
    { image_yac, 0, 200, 200, 66, 89, 6, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 91, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_yht, 0, 200, 200, 27, 29, 146, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 28, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_yid, 0, 200, 200, 36, 44, 128, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 12, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_yrd, 0, 200, 200, 100, 18, 29, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 67, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
}
