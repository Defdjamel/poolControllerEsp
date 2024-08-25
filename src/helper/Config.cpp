#include "Config.h"
#include <nvs_flash.h>

Config::Config(){
   preferences.begin(APP_NSP, false); 

ph_a =  preferences.getFloat(PH_KEY_A, ph_a);
ph_b =  preferences.getFloat(PH_KEY_B, ph_b);
}
void Config::saveConfig(){

  preferences.putFloat(PH_KEY_A, ph_a);
  preferences.putFloat(PH_KEY_B, ph_b);


}

void Config::saveWifi(String SSID, String PWD){

  preferences.putString(SSID_KEY, SSID);
  preferences.putString(PWD_KEY, PWD);

}

String Config::get_PWD(){
  	return preferences.getString(PWD_KEY, "");
}

String Config::get_SSID(){
  return preferences.getString(SSID_KEY, "");

}