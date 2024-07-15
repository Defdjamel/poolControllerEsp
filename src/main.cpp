
#include <Arduino_GFX_Library.h>
#include <U8g2lib.h>
#include "wifi.h"

#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

// 8266 various dev board   : CS: 15, DC:  4, RST:  2, BL:  5, SCK: 14, MOSI: 13, MISO: 12
/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
#define TFT_CS 15 // GFX_NOT_DEFINED for display without CS pin
#define TFT_DC 5
#define TFT_RST 4


Arduino_DataBus *bus = create_default_Arduino_DataBus();

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
// Arduino_GFX *gfx = new Arduino_ILI9341(bus, DF_GFX_RST, 0 /* rotation */, false /* IPS */);
Arduino_GFX *gfx = new Arduino_ILI9225(bus, 2 /* RST */,1 /* ROTATION*/);
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/
uint16_t colorBG  = 0x0000;

int xPos = 80;
int yPos = 64;

// direction and speed
int xDir = 1;
int yDir = 1;

// variables to keep track of the point's location
int xPrev = xPos;
int yPrev = yPos;
void testMotion();

void setup(void)
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Arduino_GFX Hello World example");

#ifdef GFX_EXTRA_PRE_INIT
  GFX_EXTRA_PRE_INIT();
#endif

  // Init Display
  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BLACK);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif
  String title = "Pool Controller" ;
  gfx->setCursor(gfx->width()/2 - title.length()*7 / 2 , 20);
  gfx->setTextColor(RED);
  
  gfx->setFont(u8g2_font_tenthinguys_t_all);
  gfx->println(title);
    gfx->setTextColor(WHITE);
      gfx->setFont(u8g2_font_helvB08_te);
   gfx->print( " screen: ");
   gfx->print( gfx->width());
   gfx->print( " x ");
   gfx->println( gfx->height());

  gfx->fillArc(50,60,20,25,45,360,WHITE);

  gfx->setCursor(8, gfx->height()-10);
 
  gfx->println("V1.0");
    // Set WiFi to station mode
  WiFi.mode(WIFI_STA);

  // Disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(2000);
  gfx->fillScreen(BLACK);
}


void loop()
{   

testMotion();
}


void testMotion(){
  // update the location of the dot
  int sizeCirlcle = 10;
  long colorCircle = GREEN;
 
  xPos = xPos + xDir;
  yPos = yPos + yDir;
  if(xPos >= gfx->width() || xPos <= 0){

    xDir = xDir*-1;

  }

  if(yPos >= gfx->height() || yPos <= 0){

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
  
  delay(2);
  

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
void testCircle(){

  // long color = random(0xffff);
// long minDelay = 100;
// for(int i = 0; 50; i++ ){
//   int size = random(50);
//   int x = random(gfx->width());
//   int y = random(gfx->height());
//   gfx->fillCircle(x, y,size,random(0xffff));
//     gfx->drawCircle(x, y,size,0xCCCC);
//   delay(40);
// }
// delay(100);

}
