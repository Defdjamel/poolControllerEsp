#include "Config.h"
#include <nvs_flash.h>

Config::Config(){

//Preferences preferences;  


// EEPROM.begin(EEPROM_SIZE);
//   int address = 0;
// EEPROM.get(address, ph_a);
// address += sizeof(ph_a);
// EEPROM.get(address, ph_b);
// address += sizeof(ph_b);
// EEPROM.get(address, orp_offset);
}
void Config::saveConfig(){
    int address = 0;
    EEPROM.put(address, ph_a);
    address += sizeof(ph_a);
    EEPROM.put(address, ph_b);
    address += sizeof(ph_b);
    EEPROM.put(address, orp_offset);
    EEPROM.commit();


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