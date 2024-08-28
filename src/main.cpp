
//GLOBAL VAR
float phVal = 0;
float orpVal = 0;
int phAuto = 0;//O: auto 1: PH FORCE 2: CHLORE FORCE
double phDosage = 0;
double orpDosage = 0;

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
 


createMainView();
String passwords = preferences.getString(PWD_KEY, "");
String ssid = preferences.getString(SSID_KEY, "");


tryConnectWifi();
static uint32_t user_data = 10;
lv_timer_t * my_timer_update_ph = lv_timer_create(timer_update_data, UPDATE_DATE_TIME,  &user_data);
send_data();

  
}


void loop()
{     
  if(WiFi.isConnected())Blynk.run();
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);

}

void readOrp(){
  //float orpVal = orpProbe.readVoltage();
}

void pumpActive(float second, int8_t pump) {
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
}


void sendPhToServer(){
   Blynk.virtualWrite(PH_VAL,phVal);
// String n[2][2] = {{"mac",WiFi.macAddress().c_str()},{"ph",String(phVal)}};
  // sendPostRequest(SERVER_API_PH, "", SERVER_PORT,  n, 2 )  ;
 
}

void sendOrpToServer(){
   Blynk.virtualWrite(ORP_VAL, random(100, 200));
//  String n[2][2] = {{"mac",WiFi.macAddress().c_str()},{"orp",String(orpVal)}};
// sendPostRequest(SERVER_API_ORP, "", SERVER_PORT, n, 2 )  ;
}



void timer_activate_pump(lv_timer_t * timerlv)
{
  if(phAuto == 1){//force ph

  //calculate nbr injection pour TIMER_PUMP_SECONd ORP_dosage 50ml/h
  float nbrInjection_perHour = 60/TIMER_PUMP_SECOND*60 ;//12
  float mlPerinjection = phDosage/nbrInjection_perHour;// 200/12 ~= 16ml/injection
  float timePerinjection = mlPerinjection/PUMP_ML_PERSECOND ;//1.6s per injection

  pumpActive(timePerinjection , PH_PUMP);

  }
  if(phAuto==2){//force Orp
  
  //calculate nbr injection pour TIMER_PUMP_SECONd ORP_dosage 50ml/h
  float nbrInjection_perHour = 60/TIMER_PUMP_SECOND*60 ;//12
  float mlPerinjection = orpDosage/nbrInjection_perHour;// 200/12 ~= 16ml/injection
  float timePerinjection = mlPerinjection/PUMP_ML_PERSECOND ;//1.6s per injection

  pumpActive(timePerinjection , ORP_PUMP);


  }
  if(phAuto == 0){//auto

  }

}