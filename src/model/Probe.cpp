
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
    Serial.println(voltage);
    return voltage;
    
}
float Probe::readPH(){
    Config config =  Config();
    Serial.printf("ph_a= %f , ph_b= %f \n\r",config.ph_a,config.ph_b);
    float voltage = readPHVoltage();
    float ph = voltage * config.ph_a + config.ph_b;
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
    float  voltage1   = this->readPHVoltage();

    gfx->fillScreen(WHITE);
    gfx->setCursor(8, gfx->height()/2);
     gfx->setTextColor(RED);
     gfx->printf("put PH 9.18 in %d sec", timeProbing );
    delay(timeProbing * 1000);

    // read voltage ph = 9.18
    float ph2 = 9.18;
    float  voltage2   = this->readPHVoltage();

    //find a and b x1 - x2 / y1 - Y2
    float a  =   (voltage2 - voltage1) / (ph2 -ph1);
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
        delay(10*1000);
    }
    else{
        gfx->setTextColor(WHITE,RED);
        gfx->println("Calibration Error");
    }   
}

bool Probe::checkCalibrationOK(float voltage1,float voltage2){
    return true;
}

void Probe::staticFunction(float t){

}

