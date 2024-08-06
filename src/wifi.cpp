
#include "wifi.h"
void connectWifi(String ssid, String  password){
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  int delayMax = 30;
  while (WiFi.status() != WL_CONNECTED && i < delayMax ) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  if( i >= delayMax){
     Serial.println("Connection Error :(");  
     return;
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());   

};


void scanForWifi(String wifiList[3]){
   String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t* bssid;
  int32_t channel;
  bool hidden;
  int scanResult;



  Serial.println(F("Starting WiFi scan..."));

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0) {
    Serial.println(F("No networks found"));
  } else if (scanResult > 0) {
    Serial.printf(PSTR("%d networks found:\n"), scanResult);

    // Print unsorted scan results
    for (int8_t i = 0; i < scanResult; i++) {
     
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
     
    Serial.println(ssid.c_str());
    wifiList[i] = ssid.c_str();
      // Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
      //               i,
      //               channel,
      //               bssid[0], bssid[1], bssid[2],
      //               bssid[3], bssid[4], bssid[5],
      //               rssi,
      //               (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
      //               hidden ? 'H' : 'V',
      //               ssid.c_str());
      delay(0);
    }
  } else {
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }

}



String WifiHelper::sendPostRequest(char* host,char* url, int port, String params[][2]){
   if ((WiFi.status() != WL_CONNECTED)) return "";
    WiFiClient client;
    //WiFiClientSecure client;
    //client.setInsecure();
    // client.setFingerprint(fingerprint);
  HTTPClient http; 
 
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
       delay(5000);
      return "";
    }

    String webUrl =  "http://" + String(host)  ;

    

    String msg = "{\"hello\":\"insecure\"}";
    http.begin(client,webUrl );
    http.addHeader("Content-Type", "application/json"); // e.g.
    http.setUserAgent( "ESP_POOL_CONTROLLER"); // e.g.
    int httpCode = http.POST(WifiHelper::stringParams(params,2)); // e.g. a=4&b=6&c=something
    
      if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    
          // file found at server
          if (httpCode == HTTP_CODE_OK) {
             String payload = http.getString();
              http.end();
             return payload;
          }
        } else {
          String s  =  http.errorToString(httpCode).c_str();
          
          delay(5000);
        }
    
    http.end();
    
    return "";
       
    
}
String WifiHelper::stringParams(String params[][2] , int c){
   String msg = "";
  
for (int i = 0; i < c ;  i++ ){

  String key = params[i][0];
  String val = params[i][1];
  msg = msg + "\"" + key + "\":" + "\"" + val + "\"";
  if(i+1<c) msg+= ",";
  
}
  
  return "{" + msg + "}";
}