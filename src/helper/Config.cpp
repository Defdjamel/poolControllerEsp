#include "Config.h"

Config::Config(){
EEPROM.begin(EEPROM_SIZE);
  int address = 0;
EEPROM.get(address, ph_a);
address += sizeof(ph_a);
EEPROM.get(address, ph_b);
}
void Config::saveConfig(){
    int address = 0;
    EEPROM.put(address, ph_a);
    address += sizeof(ph_a);
    EEPROM.put(address, ph_b);
    EEPROM.commit();


}