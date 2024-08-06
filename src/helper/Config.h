#include <EEPROM.h>
#include <Arduino.h>
#ifndef USE_CONFIG_H
#define USE_CONFIG_H
#endif

#define EEPROM_SIZE 12

class Config{
    public:
        Config();  
        float ph_a;
        float ph_b;
        float orp_offset;
       
        void saveConfig();
    private:
};

