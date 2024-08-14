#include <lvgl.h>


static lv_obj_t * wifiView;
static lv_obj_t * listWifi;

void searchWifi();
void scanForWifi2();

static void event_handler_wifi(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target_obj(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
      lv_obj_del(wifiView);
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}


 void createWifiSettingView(lv_obj_t *previousScreen){
    /* MAIN CONT */
      
    wifiView =lv_win_create(lv_screen_active());
   
    lv_obj_t * btn;
    btn = lv_win_add_button(wifiView, LV_SYMBOL_LEFT, 40);
    lv_obj_add_event_cb(btn, event_handler_wifi, LV_EVENT_CLICKED, NULL);
     lv_win_add_title(wifiView, "WIFI SETTING");

 /*Create a list*/
    listWifi =lv_list_create(wifiView);
    lv_obj_set_size(listWifi, lv_pct(100), lv_pct(100));
    lv_obj_center(listWifi);


     lv_list_add_text(listWifi, "WIFI VIEW");
     static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_radius(&layout_style, 0);
	lv_style_set_pad_all(&layout_style, 0);
    lv_style_set_outline_pad(&layout_style, 10);
	lv_style_set_outline_width(&layout_style, 0);
     lv_style_set_border_width(&layout_style, 0);
    lv_obj_add_style(listWifi, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
   
   searchWifi();
 }

void searchWifi(){
 // char* wifiList[10] ; 
     scanForWifi2();
//     lv_obj_clean(listWifi);
//      lv_obj_t * btn;
//     //delete all list
//       for (int8_t i = 0; i < MaxWifiScan; i++) {
//    btn = lv_list_add_button(listWifi, LV_SYMBOL_FILE, wifiList[i]);
//       }

}
void scanForWifi2(){
   String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t* bssid;
  int32_t channel;
  int scanResult;



//   Serial.println(F("Starting WiFi scan..."));

  //scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

//   if (scanResult == 0) {
//     Serial.println(F("No networks found"));
//   } else if (scanResult > 0) {
//     Serial.printf(PSTR("%d networks found:\n"), scanResult);

//     // Print unsorted scan results
//     for (int8_t i = 0; i < scanResult; i++) {
     
//       WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel);
     
//     Serial.println(ssid.c_str());
//    // wifiList[i] = "dsds";
//       // Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
//       //               i,
//       //               channel,
//       //               bssid[0], bssid[1], bssid[2],
//       //               bssid[3], bssid[4], bssid[5],
//       //               rssi,
//       //               (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
//       //               hidden ? 'H' : 'V',
//       //               ssid.c_str());
//       delay(0);
//     }
//   } else {
//     Serial.printf(PSTR("WiFi scan error %d"), scanResult);
//   }

}
