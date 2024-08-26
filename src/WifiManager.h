#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H
//library code here



#include "WiFi.h"
// #include <ESP8266WiFi.h>
// #include <WiFiClientSecure.h>
// #include <ESP8266HTTPClient.h>
#define MaxWifiScan 10
  void scanForWifi(String wifiList[MaxWifiScan]);
  void connectWifi(String ssid, String password);
  String sendPostRequest(char* host,char* url, int port, String params[][2],int paramsNbr); 
  String stringParams(String params[][2] , int c);

// class WifiHelper{
//     public:
//     static String sendPostRequest(char* host,char* url, int port, String params[][2]);
//     private:
//     static String stringParams(String params[][2] , int c);

// };
#endif