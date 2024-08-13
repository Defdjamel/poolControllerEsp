#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Bitbang.h>
#include "../helper/Fontawesome.c"
#include "../helper/FontIcons.h"
LV_FONT_DECLARE(Fontawesome);



#define TFT_HOR_RES   320
#define TFT_VER_RES  240

/*Set to your screen resolution*/
#define TFT_ROTATION  LV_DISPLAY_ROTATION_90
#define FONT_SIZE 1


#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
XPT2046_Bitbang touchscreen(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS);


void setupDisplay();
void setupTouchScreen();


// Get the Touchscreen data
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
    TouchPoint touch = touchscreen.getTouch();
 // if(touchscreen.tirqTouched() && touchscreen.touched()) {
   if (touch.zRaw != 0) {
    // Get Touchscreen points
    int x = map(touch.x, TFT_HOR_RES, 0, 1, TFT_HOR_RES);
    int y = map(touch.y, TFT_VER_RES, 0, 1, TFT_VER_RES);
    // x = touch.x;
    //   y = touch.y;
  //  z = p.z;

    data->state = LV_INDEV_STATE_PRESSED;

    // Set the coordinates
    data->point.x = x;
    data->point.y = y;

  //   // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
    // Serial.print("X = ");
  //   Serial.print(x);
  //   Serial.print(" | Y = ");
  //   Serial.print(y);
  //   Serial.print(" | Pressure = ");
  //   Serial.print(z);
  //   Serial.println();
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

void setupDisplay(){
  lv_init();
  lv_display_t * disp;
   //lv_disp_set_rotation(disp,TFT_ROTATION);
  #if LV_USE_TFT_ESPI
    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    
  #else
    /*Else create a display yourself*/
    disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
  #endif

}
void setupTouchScreen(){
    touchscreen.begin();
   //  // Initialize an LVGL input device object (Touchscreen)
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    // // Set the callback function to read Touchscreen input
    lv_indev_set_read_cb(indev, touchscreen_read);
}

