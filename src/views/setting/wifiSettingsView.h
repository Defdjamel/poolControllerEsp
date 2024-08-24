#include <lvgl.h>
#include "wifiSetPasswordView.h"

static lv_obj_t * wifiView;
static lv_obj_t * listWifi;


void searchWifi();



static void event_handler_wifi(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
      lv_obj_del(wifiView);
    }
}

static void event_handler_select_wifi(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
          LV_LOG_USER("Clicked: %s", lv_list_get_btn_text(listWifi, obj));
          const char* text = lv_list_get_btn_text(listWifi, obj);
          createWifiSetPassword(text);
           
    }
}

 void createWifiSettingView(lv_obj_t *previousScreen){
    /* MAIN CONT */
    wifiView =lv_win_create(lv_scr_act(),45);
    lv_win_add_title(wifiView, "WIFI SETTING");
   
    lv_obj_t * btn;
    btn = lv_win_add_btn(wifiView, LV_SYMBOL_LEFT, 46);
    lv_obj_add_event_cb(btn, event_handler_wifi, LV_EVENT_CLICKED, NULL);

    /*Create a list*/
    lv_obj_t * cont = lv_win_get_content(wifiView); 
    listWifi =lv_list_create(cont);
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
    String wifiList[MaxWifiScan] ; 
    lv_obj_t * cont = lv_win_get_content(wifiView); 
    lv_obj_clean(listWifi);

    scanForWifi(wifiList);

    lv_obj_t * btn;
    
     lv_list_add_text(listWifi, "Select a network :");
      for (int8_t i = 0; i < MaxWifiScan; i++) {
        if(wifiList[i] != "")
   btn = lv_list_add_btn(listWifi, LV_SYMBOL_WIFI, wifiList[i].c_str());
    lv_obj_add_event_cb(btn, event_handler_select_wifi, LV_EVENT_CLICKED, NULL);
      }
}