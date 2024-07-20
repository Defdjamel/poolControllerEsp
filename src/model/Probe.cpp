
#include "Probe.h"

Probe::Probe(uint8_t analogpin,byte type ){
pinMode(analogpin,OUTPUT);
}

float Probe::readPHVoltage(){
     int measurings=0;

    for (int i = 0; i < sampless; i++)
    {
        measurings += analogRead(_pin);
        delay(10);

    }

    float voltage = 5 / adc_resolutions * measurings/sampless;
    Serial.print("pH= ");
    return voltage;
    
}