// PH4502C
#ifndef USE_PROBE_H
#define USE_PROBE_H
#endif

#ifndef _ARDUINO_GFX_LIBRARIES_H_
#include <Arduino_GFX_Library.h>
#endif 

#ifndef USE_CONFIG_H
#include "helper/Config.h"
#endif


#include "Arduino.h"

enum {PROBE_PH, ORP_PH };


class Probe  
{
public:

Probe(uint8_t analogpin,byte type = PROBE_PH);
float readPHVoltage();
void startCalibrationPH(Arduino_GFX *gfx);
bool checkCalibrationOK( float voltage1, float voltage2);
static void staticFunction(float f);

private:
    int _pin ;
    byte _type ;
    int sampless = 10;
    float adc_resolutions = 1024.0;     


};
