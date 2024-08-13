#include <lvgl.h>
static lv_obj_t * wifiView;

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
    lv_obj_t * list =lv_list_create(wifiView);
    lv_obj_set_size(list, lv_pct(100), lv_pct(100));
    lv_obj_center(list);


     lv_list_add_text(list, "WIFI VIEW");
     static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_radius(&layout_style, 0);
	lv_style_set_pad_all(&layout_style, 0);
    lv_style_set_outline_pad(&layout_style, 10);
	lv_style_set_outline_width(&layout_style, 0);
     lv_style_set_border_width(&layout_style, 0);
    lv_obj_add_style(list, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
   
 }

 void getWifi(){

 }