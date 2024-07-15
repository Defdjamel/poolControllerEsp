
#include "wifi.h"
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