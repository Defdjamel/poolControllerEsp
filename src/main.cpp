
#include <Arduino_GFX_Library.h>
#include <U8g2lib.h>
#include "wifi.h"

#ifndef USE_PROBE_H
#include "model/Probe.h"
#endif 


#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

// 8266 various dev board   : CS: 15, DC:  4, RST:  2, BL:  5, SCK: 14, MOSI: 13, MISO: 12
/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
//#define TFT_CS 15 // GFX_NOT_DEFINED for display without CS pin
//#define TFT_DC 4
#define TFT_RST 2

// MISO , CS(to gnd) not need
Arduino_DataBus *bus = create_default_Arduino_DataBus();

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
// Arduino_GFX *gfx = new Arduino_ILI9341(bus, DF_GFX_RST, 0 /* rotation */, false /* IPS */);
Arduino_GFX *gfx = new Arduino_ILI9341(bus, TFT_RST /* RST */,1 /* ROTATION*/);
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/
uint16_t colorBG  = 0xCECE;

int xPos = 80;
int yPos = 64;

// direction and speed
int xDir = 1;
int yDir = 1;

// variables to keep track of the point's location
int xPrev = xPos;
int yPrev = yPos;
void testMotion();
void pumpActive(int second, int8_t pump);
void setupDisplay();

#define PH_PUMP  16
#define ORP_PUMP   5
#define PH_PIN  A0
Probe phProbe = Probe(PH_PIN,PROBE_PH);

void setup(void)
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Pool Controller V1.0");
  setupDisplay();

    // Set WiFi to station mode
  WiFi.mode(WIFI_STA);
  // Disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(2000);
  gfx->fillScreen(LIGHTGREY);
//  pumpActive(2 , PH_PUMP);
//  pumpActive(2 , ORP_PUMP);

float test = -5.6;
 Serial.println(test);
 phProbe.startCalibrationPH(gfx);

}
void setupDisplay(){

#ifdef GFX_EXTRA_PRE_INIT
  GFX_EXTRA_PRE_INIT();
#endif

  // Init Display
  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(WHITE);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif
  String title = "Pool Controller" ;
  gfx->setCursor(gfx->width()/2 - title.length()*7 / 2 , 20);
  gfx->setTextColor(RED);
  
  gfx->setFont(u8g2_font_tenthinguys_t_all);
  gfx->println(title);
    gfx->setTextColor(BLACK);
      gfx->setFont(u8g2_font_helvB08_te);
   gfx->print( " screen: ");
   gfx->print( gfx->width());
   gfx->print( " x ");
   gfx->println( gfx->height());

  gfx->fillArc(50,60,20,25,45,360,WHITE);

  gfx->setCursor(8, gfx->height()-10);
 
  gfx->println("V1.0");
  delay(2000);
   
}


void loop()
{   
  gfx->fillScreen(WHITE);
  float phVoltage = phProbe.readPH();
  gfx->setTextColor(BLACK,0);
  gfx->setCursor(8, gfx->height()/2);
  gfx->print("ph : ");
  gfx->print(phVoltage);
  gfx->print("");
  gfx->println(millis());
  delay(4000);

}

void pumpActive(int second, int8_t pump) {
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);   
  delay(second*1000);              
  digitalWrite(pump, HIGH);  


}

void testMotion(){
  // update the location of the dot
  int sizeCirlcle = 10;
  long colorCircle = YELLOW;
 
  xPos = xPos + xDir;
  yPos = yPos + yDir;
  if(xPos >=(gfx->width() - sizeCirlcle)|| xPos <= (0+ sizeCirlcle)){

    xDir = xDir*-1;

  }

  if(yPos >= (gfx->height() - sizeCirlcle) || yPos <= (0 + sizeCirlcle)){

   yDir = yDir*-1;

  }
  //erase previous circle
  if(xPos != xPrev || yPos != yPrev){

     gfx->fillCircle(xPrev,yPrev,sizeCirlcle,BLACK);
    

  }

  
// draw circle
  gfx->fillCircle(xPos,yPos,sizeCirlcle,colorCircle);
 xPrev = xPos;
  yPrev = yPos;
  
  delay(10);
  

}

void testWifi(){

gfx->fillScreen(BLACK);
 gfx->setCursor(10, 10);
String wifiList[3]={"","",""};
 
  gfx->print("SCANNING...");delay(100);
scanForWifi(wifiList);
gfx->fillScreen(BLACK);
 gfx->setCursor(10, 10);
  
  gfx->println("SCAN RESULT : ");
 for(int i = 0; i<3; i++ ){
  
  gfx->setTextColor(WHITE,BLUE);
 
  gfx->setFont(u8g2_font_DigitalDisco_tf);
  
  gfx->println(wifiList[i]);

 }
 delay(4000);
}
