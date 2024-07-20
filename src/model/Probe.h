// PH4502C
#include "Arduino.h"
enum {PROBE_PH, ORP_PH };


class Probe  
{
public:

Probe(uint8_t analogpin,byte type = PROBE_PH);
 void init(uint8_t analogpin,byte type = PROBE_PH);
 void calibration();
 float readPHVoltage();

private:
    int _pin ;
    byte _type ;
    int sampless = 10;
    float adc_resolutions = 1024.0;     


};