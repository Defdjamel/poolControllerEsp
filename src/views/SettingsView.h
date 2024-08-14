#include <lvgl.h>
// #include "wifiSettingsView.h"
static lv_obj_t * list1;
void createSettingView(lv_obj_t *parent);


 static char   Click_ph_calibration[] = "Click_ph_calibration";
 static char  Click_orp_calibration[] = "Click_orp_calibration";
 static char  Click_wifi_setting[] = "Click_wifi_setting";

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        LV_UNUSED(obj);
        LV_LOG_USER("Clicked: %s", lv_list_get_button_text(list1, obj));
         LV_LOG_USER( "userdata : %s",(char*) obj->user_data);
         //Serial.println((int*) obj->user_data);
         if((char*) obj->user_data == Click_ph_calibration)
          LV_LOG_USER("goto ph calibration");
           else if((char*) obj->user_data == Click_orp_calibration)
          LV_LOG_USER("goto Click_orp_calibration:");
           else if((char*) obj->user_data == Click_wifi_setting){
            LV_LOG_USER("goto Click_wifi_setting:");
            //createWifiSettingView(list1->parent);
           }
        
    }
}

void createSettingView(lv_obj_t *parent)
{
    /*Create a list*/
    list1 = lv_list_create(parent);
    lv_obj_set_size(list1, lv_pct(100),  lv_pct(100));
    lv_obj_center(list1);
    // Style
    static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_radius(&layout_style, 0);
	lv_style_set_pad_all(&layout_style, 0);
    lv_style_set_outline_pad(&layout_style, 10);
	lv_style_set_outline_width(&layout_style, 0);
    lv_style_set_bg_opa(&layout_style, LV_OPA_TRANSP);
    lv_obj_add_style(list1, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_style_set_border_width(&layout_style, 0);
    

    /*Add buttons to the list*/
    uint32_t type = 1;
    lv_obj_t * btn;
    lv_list_add_text(list1, "Sondes");
    btn = lv_list_add_btn(list1, LV_SYMBOL_SETTINGS, "Calibration PH");
    lv_obj_set_user_data(btn, &Click_ph_calibration);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED,NULL);
   
    
    btn = lv_list_add_btn(list1, LV_SYMBOL_SETTINGS, "Calibration Chlore");
    lv_obj_set_user_data(btn, &Click_orp_calibration);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED,  NULL);
     
   

    lv_list_add_text(list1, "Connection");
    btn = lv_list_add_btn(list1, LV_SYMBOL_WIFI, "Wifi");
    lv_obj_set_user_data(btn, &Click_wifi_setting);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
    

  
}


