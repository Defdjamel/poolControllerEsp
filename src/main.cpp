 #define BLYNK_PRINT Serial
 #define BLYNK_TEMPLATE_ID "TMPL5SBIKrCyr"
#define BLYNK_TEMPLATE_NAME "Pool Controller"
 #define BLYNK_AUTH_TOKEN "E4I5fTOZjOggStL57OhplNxTd0oHZqyV"
#define BLYNK_FIRMWARE_VERSION        "0.2.0"

float phVal = 0;
float orpVal = 0;
bool phAuto = 1;
double phDosage = 0;

#include "BlynkManager.h"
#include <BlynkSimpleEsp32.h>



#include "events/EventsManager.h"
#include "WifiManager.h"
#include "helper/custom_font.c"
#include "helper/font.h"
#include "model/Probe.h"
#include "helper/Constants.h"

#include <Preferences.h>
Preferences preferences;
#include "settings/Pin_settings.h"
#include "settings/Display_settings.h"

#include "views/MainView.h"

/*Use the font*/

/*Free the font if not required anymore*/
// lv_font_free(my_font);


#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

#ifndef USE_PROBE_H
#include "model/Probe.h"
#endif 



void my_log_cb(lv_log_level_t level, const char * buf);
void pumpActive(int second, int8_t pump);
void sendPhToServer();
void sendOrpToServer();
void send_data();

void timer_update_data(lv_timer_t * timer);




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


createMainView();
String passwords = preferences.getString(PWD_KEY, "");
String ssid = preferences.getString(SSID_KEY, "");


tryConnectWifi();
static uint32_t user_data = 10;
lv_timer_t * my_timer_update_ph = lv_timer_create(timer_update_data, UPDATE_DATE_TIME,  &user_data);
send_data();

  
}


void loop()
{   Blynk.run();
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);

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


void my_log_cb(lv_log_level_t level, const char * buf)
{
  //serial_send(buf, strlen(buf));
   Serial.println(buf);
}


void send_data(){
  if(!WiFi.isConnected())return;
sendPhToServer();
// sendOrpToServer();
}


void timer_update_data(lv_timer_t * timerlv)
{
send_data();
}


void sendPhToServer(){
   Blynk.virtualWrite(phVal, millis()/10);
// String n[2][2] = {{"mac",WiFi.macAddress().c_str()},{"ph",String(phVal)}};
  // sendPostRequest(SERVER_API_PH, "", SERVER_PORT,  n, 2 )  ;
 
}

void sendOrpToServer(){
//  String n[2][2] = {{"mac",WiFi.macAddress().c_str()},{"orp",String(orpVal)}};
// sendPostRequest(SERVER_API_ORP, "", SERVER_PORT, n, 2 )  ;
}

