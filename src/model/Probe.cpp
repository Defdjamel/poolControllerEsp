
#include "Probe.h"

Probe::Probe(uint8_t analogpin,byte type ){
_pin  = analogpin;
pinMode(_pin,INPUT);
}


float Probe::readVoltage(){
     int measurings=0;
    for (int i = 0; i < sampless; i++)
    {
        measurings += analogRead(_pin);
        delay(10);
    }

    float voltage = 5 / adc_resolutions * measurings/sampless;
     Serial.printf("voltage= %.2f \n\r",voltage);
    return voltage;
    
}
float Probe::readPH(Preferences *pref){
    float ph_a =  pref->getFloat(PH_KEY_A, ph_a);
    float ph_b =  pref->getFloat(PH_KEY_B, ph_b);

    Serial.printf("ph_a= %f , ph_b= %f \n\r",ph_a,ph_b);
    float voltage = readVoltage();
    float ph = voltage * ph_a + ph_b;
    Serial.printf("PH= %f \n\r",ph);
    return ph;
}

float Probe::readOrp(Preferences *pref){
    float voltage = readVoltage();
    Serial.printf("orpVoltage = %f  \n\r",voltage);
    //get offset
    float offset =  pref->getFloat(ORP_KEY_OFFSET, 0);
    offset = 3.223 - 0.256; 

    Serial.printf("offset= %f  \n\r",offset);
    float orpv = voltage - offset;
    return orpv;
}

void Probe::startCalibrationPH(){
    int timeProbing =30;
    // gfx->fillScreen(WHITE);
    // gfx->setTextColor(BLACK,0);
    // gfx->setCursor(8, gfx->height()/2);
    // gfx->printf("put PH 4.01 in %d sec", timeProbing );
    delay(timeProbing * 1000);
    //read voltage ph = 4.01
    float ph1 = 4.01;
    float  voltage1   = this->readVoltage();

    // gfx->fillScreen(WHITE);
    // gfx->setCursor(8, gfx->height()/2);
    //  gfx->setTextColor(RED);
      float ph2 = 6.86;
    //  gfx->printf("put PH %f in %d sec",ph2, timeProbing );
    delay(timeProbing * 1000);

    // read voltage ph = 9.18
   
    float  voltage2   = this->readVoltage();

    //find a and b x1 - x2 / y1 - Y2
    float a  =  (ph2 -ph1) / (voltage2 - voltage1);
    float b   = ph2 - ( a * voltage2);
    bool isOk = checkCalibrationOK(voltage1, voltage2);
    if(isOk == true){
        // gfx->setTextColor(BLACK);
        // gfx->println("Calibration OK");
        // gfx->print("A: ");
        // gfx->println(a);
        // gfx->print("B: ");
        // gfx->println(b);
        // Serial.printf("A= %f \r\n",a);
        // Serial.printf("B= %f \r\n",b);
     
       
        delay(10*1000);
    }
    else{
        // gfx->setTextColor(WHITE,RED);
        // gfx->println("Calibration Error");
    }   
}



bool Probe::checkCalibrationOK(float voltage1,float voltage2){
    return true;
}


