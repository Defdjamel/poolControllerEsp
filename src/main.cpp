
//GLOBAL VAR
float phVal = 0;
float orpVal = 0;
float tempWater = 0;
double phDosage = 0;
double orpDosage = 0;

#include "BlynkManager.h"
#include <BlynkSimpleEsp32.h>

#include <FS.h>
#include <WiFi.h>
#include <SPIFFS.h>

#include "Update.h"
#include <WiFiClientSecure.h>




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

#include "OTA/ota.h"

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

#ifndef USE_PROBE_H
#include "model/Probe.h"
#endif 




void my_log_cb(lv_log_level_t level, const char * buf);
void pumpActive(float second, int pump);
void sendPhToServer();
void sendOrpToServer();
void send_data();
void activatePumps();

void timer_update_data(lv_timer_t * timer);
void timer_activate_pump(lv_timer_t * timerlv);
void  testTft();



Probe phProbe  = Probe(PH_PIN, PROBE_PH);


void setup(void)
{     
  delay(0);
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Pool Controller V1.0");
   
  setupDisplay();
   

  // testTft();
  // return;
  setupTouchScreen();
  preferences.begin(APP_NSP, false); 
 


createMainView();
String passwords = preferences.getString(PWD_KEY, "");
String ssid = preferences.getString(SSID_KEY, "");


tryConnectWifi();
static uint32_t user_data = 10;
lv_timer_t * my_timer_update_ph = lv_timer_create(timer_update_data, UPDATE_DATE_TIME,  &user_data);
lv_timer_t * my_timer_pump = lv_timer_create(timer_activate_pump, TIMER_PUMP_SECOND *1000,  &user_data);
send_data();
  if(WiFi.isConnected())checkOTAUpdate();;
 
//  pumpActive(1 , PH_PUMP);
// pumpActive(2 , ORP_PUMP);
  
}

void testTft(){
   tft.init();
    tft.setRotation( 1 );

  tft.fillScreen(TFT_WHITE);
  tft.drawRect(0, 0, tft.width()/2, tft.height()/2, TFT_RED);
  tft.drawCircle(10,10,50,TFT_YELLOW);
}


void loop()
{     
  // if(WiFi.isConnected())Blynk.run();
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);

}

void readOrp(){
  //float orpVal = orpProbe.readVoltage();
}

void pumpActive(float second, int pump) {
   Serial.printf("pump active= %.1f , %d\r\n" , second,pump);
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

void timer_update_data(lv_timer_t * timerlv)
{
send_data();
}


void send_data(){
  if(!WiFi.isConnected())return;
sendPhToServer();
sendOrpToServer();
 Blynk.virtualWrite(TEMP_WATER,(float) random(100, 200)/10);
}


void sendPhToServer(){
   Blynk.virtualWrite(PH_VAL,phVal);
// String n[2][2] = {{"mac",WiFi.macAddress().c_str()},{"ph",String(phVal)}};
  // sendPostRequest(SERVER_API_PH, "", SERVER_PORT,  n, 2 )  ;
 
}

void sendOrpToServer(){
   Blynk.virtualWrite(ORP_VAL, orpVal*1000);
//  String n[2][2] = {{"mac",WiFi.macAddress().c_str()},{"orp",String(orpVal)}};
// sendPostRequest(SERVER_API_ORP, "", SERVER_PORT, n, 2 )  ;
}
void timer_activate_pump(lv_timer_t * timerlv)
{
  activatePumps();
}


void activatePumps()
{
  if(phDosage > 0){//force ph
   Serial.println("Force PH PUMP");

  //calculate nbr injection pour TIMER_PUMP_SECONd ORP_dosage 50ml/h
  float nbrInjection_perHour = 60 / (TIMER_PUMP_SECOND / 60) ;//12 for 5 min
  float mlPerinjection = phDosage/nbrInjection_perHour;// 200/12 ~= 16ml/injection
  float timePerinjection = mlPerinjection/PUMP_ML_PERSECOND ;//1.6s per injection

   Serial.printf("nbrInjection_perHour= %.2f \r\n mlPerinjection= %.2f \r\n timePerinjection= %.2f\n\r",nbrInjection_perHour,mlPerinjection,timePerinjection);

  pumpActive(timePerinjection , PH_PUMP);

  }
  if(orpDosage>0){//force Orp
  Serial.println("Force Orp PUMP");
  //calculate nbr injection pour TIMER_PUMP_SECONd ORP_dosage 50ml/h
  float nbrInjection_perHour = 60/( TIMER_PUMP_SECOND / 60) ;//12
  float mlPerinjection = orpDosage/nbrInjection_perHour;// 200/12 ~= 16ml/injection
  float timePerinjection = mlPerinjection/PUMP_ML_PERSECOND ;//1.6s per injection

  pumpActive(timePerinjection , ORP_PUMP);


  }
  if(phDosage == 0 && orpDosage == 0){
    //auto
  }
  

}