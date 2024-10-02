#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H
//library code here



#include "WiFi.h"

#include <lvgl.h>
#define MaxWifiScan 10
  void scanForWifi(String wifiList[MaxWifiScan]);
   void scanTest();
  void connectWifi(String ssid, String password);
  String sendPostRequest(const char* host , const char* url, int port, String params[][2], int paramsNbr); 
  String stringParams(String params[][2] , int c);


#endif