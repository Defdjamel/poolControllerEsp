#include <Arduino_GFX_Library.h>
#include "model/Probe.h"

void startCalibrationPH(Arduino_GFX *gfx, Probe *probe){
    gfx->setCursor(8, gfx->height()-10);
    gfx->println("put PH 4.01 for 30 sec");
    delay(30 * 1000);
    //read voltage ph = 4.01
    float ph1 = 4.01;
    float  voltage1   = probe->readPHVoltage();


    gfx->setCursor(8, gfx->height()-10);
    gfx->println("put PH 9.01 for 30 sec");
    delay(30 * 1000);

    // read voltage ph = 9.18
    float ph2 = 9.19;
    float  voltage2   = probe->readPHVoltage();

    //find a and b x1 - x2 / y1 - Y2
    float a  =   voltage1 - voltage1 / (ph1 -ph2);
    float b   = ph2 - ( a * voltage2);
    bool isOk = checkCalibrationOK(voltage1, voltage1);
    if(isOk == true){
        gfx->println("Calibration OK");
    }
    else{
        gfx->setTextColor(WHITE,RED);
        gfx->println("Calibration Error");
    }

  
     
}

bool checkCalibrationOK(float voltage1,float voltage2){
    return true;

}