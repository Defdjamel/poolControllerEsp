// Touchscreen pins
//#define XPT2046_IRQ 36   // T_IRQ
// #define XPT2046_MOSI  32  // T_DIN
// #define XPT2046_MISO  39  // T_OUT
// #define XPT2046_CLK  25   // T_CLK
// #define XPT2046_CS  33    // T_CS

//esP32s3
#define XPT2046_MOSI 15//esp32 32  // T_DIN
#define XPT2046_MISO 5 //esp32 39  // T_OUT
#define XPT2046_CLK  17 //esp32 25   // T_CLK
#define XPT2046_CS  16 //esp32 33    // T_CS

// pumps
#define PH_PUMP   40 //19
#define ORP_PUMP  39 //18

// //Probe
#define PH_PIN  36
#define ORP_PIN  34
//ESP32S3
// #define PH_PIN 4 
// #define ORP_PIN  6 


// 21 22 I2C !

/*
Display in user setup
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

#define TOUCH_CS 33     // Chip select pin (T_CS) of touch screen
#define TFT_BL   21    
*/