#include "settings/Pin_settings.h"
#include "settings/Display_settings.h"
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Bitbang.h>

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

#ifndef USE_PROBE_H
#include "model/Probe.h"
#endif 


void pumpActive(int second, int8_t pump);
void setupDisplay();
void setupTouchScreen();
void lv_example_get_started_1();
void lv_example_msgbox_1();
static void slider_event_callback(lv_event_t * e) ;

unsigned long timer = millis();



Probe phProbe = Probe(PH_PIN, PROBE_PH);
// Probe orpProbe = Probe(PH_PIN, ORP_PH);

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
XPT2046_Bitbang touchscreen(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS);



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
  //  Serial.print("X = ");
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


void setup(void)
{  
  delay(10);
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Pool Controller V1.0");
 setupDisplay();
 setupTouchScreen();

    // Set WiFi to station mode
 // WiFi.mode(WIFI_STA);
  // Disconnect from an AP if it was previously connected
  //WiFi.disconnect();
  delay(2000);
  // pumpActive(2 , PH_PUMP);
  //delay(2000);
  // pumpActive(2 , ORP_PUMP);

 //phProbe.startCalibrationPH(gfx);
 //connectWifi(WIFI_ssid , WIFI_password);


}
lv_obj_t * labelTimer;
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

  

 lv_example_get_started_1();
  labelTimer = lv_label_create(lv_screen_active());
    lv_label_set_text(labelTimer, "Hello world");
    lv_obj_align(labelTimer, LV_ALIGN_TOP_LEFT, 5, 20);


}
void setupTouchScreen(){
    touchscreen.begin();
   //  // Initialize an LVGL input device object (Touchscreen)
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    // // Set the callback function to read Touchscreen input
    lv_indev_set_read_cb(indev, touchscreen_read);
}

void loop()
{   
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);   

  //read ph every 5 sec
 if(millis() > timer + 2000){
float phVoltage = phProbe.readVoltage();
char buffer[6];
sprintf(buffer, "%.2f", phVoltage);
 lv_label_set_text_fmt(labelTimer, "%d : %s", timer,buffer);
 timer = millis();
 }
  //  
  
  // delay(4000);
  // String n[2][2] = {{"A","Hello"},{"size",String(millis()/1000)}};
  // WifiHelper::sendPostRequest(SERVER_HOST, "/d", 80 , n);

}
void readOrp(){
 
  //float orpVal = orpProbe.readVoltage();
  
}

void pumpActive(int second, int8_t pump) {
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);   
  delay(second*1000);              
  digitalWrite(pump, HIGH);  


}


// void testWifi(){

// gfx->fillScreen(BLACK);
//  gfx->setCursor(10, 10);
// String wifiList[3]={"","",""};
 
//   gfx->print("SCANNING...");delay(100);
// scanForWifi(wifiList);
// gfx->fillScreen(BLACK);
//  gfx->setCursor(10, 10);
  
//   gfx->println("SCAN RESULT : ");
//  for(int i = 0; i<3; i++ ){
  
//   gfx->setTextColor(WHITE,BLUE);
 
//   gfx->setFont(u8g2_font_DigitalDisco_tf);
  
//   gfx->println(wifiList[i]);

//  }
//  delay(4000);
// }
static lv_obj_t * slider_label;

void lv_example_get_started_1(void)
{
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xecf0f1), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0x2c3e50), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);


// Create a slider aligned in the center bottom of the TFT display
  lv_obj_t * slider = lv_slider_create(lv_screen_active());
  lv_obj_align(slider, LV_ALIGN_CENTER, 0, 60);
  
  lv_obj_add_event_cb(slider, slider_event_callback, LV_EVENT_VALUE_CHANGED, NULL);
  lv_slider_set_range(slider, 0, 100);
  lv_obj_set_style_anim_duration(slider, 2000, 0);
  lv_obj_set_width(slider, 180);

  // Create a label below the slider to display the current slider value
  slider_label = lv_label_create(lv_screen_active());
  lv_label_set_text(slider_label, "0%");
  
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);



    /*Create a spinner*/
    lv_obj_t * spinner = lv_spinner_create(lv_screen_active());
    lv_obj_set_size(spinner, 30, 30);
    lv_obj_align(spinner, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_set_style_arc_width(spinner, 5, LV_PART_MAIN); // Changes background arc width
    lv_obj_set_style_arc_width(spinner, 5, LV_PART_INDICATOR); 
    lv_obj_set_style_arc_color(spinner,lv_palette_main(LV_PALETTE_RED),LV_PART_INDICATOR);
    lv_spinner_set_anim_params(spinner, 1000, 200);
    
}



// Callback that prints the current slider value on the TFT display and Serial Monitor for debugging purposes
static void slider_event_callback(lv_event_t * e) {
  lv_obj_t * slider = (lv_obj_t*) lv_event_get_target(e);
  int val = (int)lv_slider_get_value(slider);
  lv_label_set_text_fmt(slider_label, "val :  %d%%", (int)lv_slider_get_value(slider));
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  LV_LOG_USER("Slider changed to %d%%", (int)lv_slider_get_value(slider));
  if (val ==100){
    lv_example_msgbox_1();
  }
  
}


static void event_cb(lv_event_t * e)
{
    lv_obj_t * btn = (lv_obj_t*) lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    LV_UNUSED(label);
    LV_LOG_USER("Button %s clicked", lv_label_get_text(label));
  
    lv_obj_delete(btn);
}

void lv_example_msgbox_1(void)
{
    lv_obj_t * mbox1 = lv_msgbox_create(NULL);

    lv_msgbox_add_title(mbox1, "Hello");

    lv_msgbox_add_text(mbox1, "This is a message box with two buttons.");
    lv_msgbox_add_close_button(mbox1);

    lv_obj_t * btn;
    btn = lv_msgbox_add_footer_button(mbox1, "Apply");
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);
    btn = lv_msgbox_add_footer_button(mbox1, "Cancel");
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);
    return;
}