#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Bitbang.h>

#define TFT_HOR_RES   320
#define TFT_VER_RES  240

/*Set to your screen resolution*/
#define TFT_ROTATION  LV_DISPLAY_ROTATION_90
#define FONT_SIZE 1



static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ TFT_HOR_RES * TFT_VER_RES / 10 ];

TFT_eSPI tft = TFT_eSPI(TFT_HOR_RES, TFT_VER_RES);
XPT2046_Bitbang touchscreen(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS);



void setupDisplay();
void setupTouchScreen();
void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data );

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->ch, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

// Get the Touchscreen data
// void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data ){
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

      tft.begin();          /* TFT init */
      tft.setRotation(3 ); /* Landscape orientation, flipped */

      lv_disp_draw_buf_init( &draw_buf, buf, NULL, TFT_HOR_RES * TFT_VER_RES / 10 );

      /*Initialize the display*/
      static lv_disp_drv_t disp_drv;
      lv_disp_drv_init( &disp_drv );
      /*Change the following line to your display resolution*/
      disp_drv.hor_res = TFT_HOR_RES;
      disp_drv.ver_res = TFT_VER_RES;
      disp_drv.flush_cb = my_disp_flush;
      disp_drv.draw_buf = &draw_buf;
      lv_disp_drv_register( &disp_drv );


}
void setupTouchScreen(){
    touchscreen.begin();
   //  // Initialize an LVGL input device object (Touchscreen)
    // lv_indev_t * indev = lv_indev_create();
    // lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    // // // Set the callback function to read Touchscreen input
    // lv_indev_set_read_cb(indev, touchscreen_read);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );
}

