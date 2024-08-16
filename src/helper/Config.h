#include <Preferences.h>
#include <EEPROM.h>
#include <Arduino.h>
#ifndef USE_CONFIG_H
#define USE_CONFIG_H
#endif

#define EEPROM_SIZE 12
#define APP_NSP "NSP"
#define PH_KEY "Ph_KEY"
#define SSID_KEY "SSID_KEY"
#define PWD_KEY "PWD_KEY"



class Config{
    public:
        Config();  
        void saveWifi(String SSID, String PWD);
        String get_PWD() ;
        String get_SSID() ;
        float ph_a;
        float ph_b;
        float orp_offset;
       
        void saveConfig();
    private:
        Preferences preferences;  
};

