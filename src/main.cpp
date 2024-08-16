#include "events/EventsManager.h"
#include "WifiManager.h"

#include <Preferences.h>
#include "settings/Pin_settings.h"
#include "settings/Display_settings.h"
Preferences preferences;
#include "views/MainView.h"

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

#ifndef USE_PROBE_H
#include "model/Probe.h"
#endif 



void my_log_cb(lv_log_level_t level, const char * buf);
void pumpActive(int second, int8_t pump);
void testTFT();


unsigned long timer = millis();

Probe phProbe = Probe(PH_PIN, PROBE_PH);
// Probe orpProbe = Probe(PH_PIN, ORP_PH);

void setup(void)
{  
  delay(0);
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Pool Controller V1.0");
  setupDisplay();
  setupTouchScreen();
  preferences.begin(APP_NSP, false); 
 
  // Disconnect from an AP if it was previously connected
  //WiFi.disconnect();
  // pumpActive(2 , PH_PUMP);
  //delay(2000);
  // pumpActive(2 , ORP_PUMP);

 //phProbe.startCalibrationPH(gfx);
//  connectWifi("WIFI_ssid" , "WIFI_password");
  
  // We can now plot text on screen using the "print" class

createMainView();
 //int scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);


  // testTFT();
  
  
}
void testTFT(){
  tft.fillScreen(TFT_WHITE);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  tft.setTextColor(0x4c3c,TFT_BLACK);  tft.setTextSize(1);
  // We can now plot text on screen using the "print" class
  tft.println("Hello World!");
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
    // sprintf(buffer, "%.2f", phVoltage);
    timer = millis();
 } 
  
  
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
void my_log_cb(lv_log_level_t level, const char * buf)
{
  //serial_send(buf, strlen(buf));
   Serial.println(buf);
}