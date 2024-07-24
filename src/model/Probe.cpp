
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
    Serial.print("voltage= ");
     Serial.print(measurings/sampless);
    return voltage;
    
}

void Probe::startCalibrationPH(Arduino_GFX *gfx){
    gfx->fillScreen(WHITE);
    gfx->setTextColor(BLACK,0);
    gfx->setCursor(8, gfx->height()/2);
    gfx->println("put PH 4.01 for 30 sec");
    delay(10 * 1000);
    //read voltage ph = 4.01
    float ph1 = 4.01;
    float  voltage1   = this->readPHVoltage();

    gfx->fillScreen(WHITE);
    gfx->setCursor(8, gfx->height()/2);
     gfx->setTextColor(RED);
    gfx->println("put PH 9.01 for 30 sec");
    delay(10 * 1000);

    // read voltage ph = 9.18
    float ph2 = 9.19;
    float  voltage2   = this->readPHVoltage();

    //find a and b x1 - x2 / y1 - Y2
    float a  =   voltage1 - voltage1 / (ph1 -ph2);
    float b   = ph2 - ( a * voltage2);
    bool isOk = checkCalibrationOK(voltage1, voltage1);
    if(isOk == true){
          gfx->setTextColor(BLACK);
        gfx->println("Calibration OK");
         gfx->print("A: ");
         gfx->println(a);
          gfx->print("B: ");
          gfx->println(b);
          delay(30*1000);
    }
    else{
        gfx->setTextColor(WHITE,RED);
        gfx->println("Calibration Error");
    }   
}

bool Probe::checkCalibrationOK(float voltage1,float voltage2){
    return true;
}

void Probe::staticFunction(float f){

}

