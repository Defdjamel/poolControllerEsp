
#include "Probe.h"

Probe::Probe(uint8_t analogpin,byte type ){
pinMode(analogpin,INPUT);
configProbe =  Config();
}


float Probe::readVoltage(){
     int measurings=0;
    for (int i = 0; i < sampless; i++)
    {
        measurings += analogRead(_pin);
        delay(10);
    }

    float voltage = 5 / adc_resolutions * measurings/sampless;
    Serial.print("voltage= ");
    Serial.println(voltage);
    return voltage;
    
}
float Probe::readPH(){
   
    Serial.printf("ph_a= %f , ph_b= %f \n\r",configProbe.ph_a,configProbe.ph_b);
    float voltage = readVoltage();
    float ph = voltage * configProbe.ph_a + configProbe.ph_b;
    Serial.printf("PH= %f \n\r",ph);
    return ph;
}

void Probe::startCalibrationPH(Arduino_GFX *gfx){
    int timeProbing =30;
    gfx->fillScreen(WHITE);
    gfx->setTextColor(BLACK,0);
    gfx->setCursor(8, gfx->height()/2);
    gfx->printf("put PH 4.01 in %d sec", timeProbing );
    delay(timeProbing * 1000);
    //read voltage ph = 4.01
    float ph1 = 4.01;
    float  voltage1   = this->readVoltage();

    gfx->fillScreen(WHITE);
    gfx->setCursor(8, gfx->height()/2);
     gfx->setTextColor(RED);
      float ph2 = 6.86;
     gfx->printf("put PH %f in %d sec",ph2, timeProbing );
    delay(timeProbing * 1000);

    // read voltage ph = 9.18
   
    float  voltage2   = this->readVoltage();

    //find a and b x1 - x2 / y1 - Y2
    float a  =  (ph2 -ph1) / (voltage2 - voltage1);
    float b   = ph2 - ( a * voltage2);
    bool isOk = checkCalibrationOK(voltage1, voltage2);
    if(isOk == true){
        gfx->setTextColor(BLACK);
        gfx->println("Calibration OK");
        gfx->print("A: ");
        gfx->println(a);
        gfx->print("B: ");
        gfx->println(b);
        Serial.printf("A= %f \r\n",a);
        Serial.printf("B= %f \r\n",b);
     
        Config config =  Config();
        config.ph_a = a;
        config.ph_b = b;
        config.saveConfig();
        configProbe = config;
        delay(10*1000);
    }
    else{
        gfx->setTextColor(WHITE,RED);
        gfx->println("Calibration Error");
    }   
}

void Probe::startCalibrationORP(Arduino_GFX *gfx){
}

bool Probe::checkCalibrationOK(float voltage1,float voltage2){
    return true;
}


