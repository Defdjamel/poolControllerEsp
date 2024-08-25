// PH4502C
#ifndef USE_PROBE_H
#define USE_PROBE_H

#include "helper/Config.h"




#include "Arduino.h"

enum {PROBE_PH, ORP_PH };


class Probe  
{
public:

Probe(uint8_t analogpin,byte type = PROBE_PH);
float readVoltage();
float readPH(Preferences *pref);
void startCalibrationPH();
bool checkCalibrationOK( float voltage1, float voltage2);


private:
    int _pin ;
    byte _type ;
    int sampless = 10;
    float adc_resolutions = 4095.0;
    Config configProbe ;    


};
#endif