#include <lvgl.h>
#include "HomeView.h"
#include "SettingsView.h"
#include "InfoView.h"


  lv_obj_t * tabview;
  lv_obj_t * iconWifi ;
  static void eventManager_handler_mainView(byte event);
  void createMainView();



void createMainView(){
  tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 50);
  lv_obj_t * tab1 = lv_tabview_add_tab(tabview, MY_HOME_SYMBOL);
  lv_obj_t * tab2 = lv_tabview_add_tab(tabview,MY_SETTING_SYMBOL );
  lv_obj_t * tab3 = lv_tabview_add_tab(tabview,MY_INFO_SYMBOL );

  lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
  lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 10), 0);
  lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 1), LV_PART_ITEMS | LV_STATE_CHECKED);
  lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);
  lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
  lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_RED, 5),  LV_STATE_CHECKED);

  lv_obj_set_style_text_font(tab_btns, &font_info, LV_PART_MAIN| LV_STATE_DEFAULT);

  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_text_font(&style, &lv_font_montserrat_16);
  lv_obj_add_style(tab2,  &style, LV_PART_MAIN| LV_STATE_DEFAULT);
  lv_obj_add_style(tab3,  &style, LV_PART_MAIN| LV_STATE_DEFAULT);

  //Style
  static lv_style_t layout_style;
  lv_style_init(&layout_style);
  lv_style_set_pad_all(&layout_style, 0);
  lv_obj_add_style(tab3, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_style_set_border_width(&layout_style, 0);

  lv_obj_t * spinner = lv_spinner_create(tab_btns,1000, 200);
  lv_obj_set_size(spinner, 10, 10);
  lv_obj_align(spinner, LV_ALIGN_TOP_LEFT, 4, 4);
  lv_obj_set_style_arc_width(spinner, 1, LV_PART_MAIN); // Changes background arc width
  lv_obj_set_style_arc_width(spinner, 1, LV_PART_INDICATOR); 
  lv_obj_set_style_arc_color(spinner,lv_palette_main(LV_PALETTE_RED),LV_PART_INDICATOR);


  iconWifi = lv_label_create(tab_btns);
  lv_obj_align(iconWifi, LV_ALIGN_TOP_LEFT, 20, 4);
  lv_obj_set_style_text_font(iconWifi,&lv_font_montserrat_8,LV_PART_MAIN);
  lv_label_set_text(iconWifi, LV_SYMBOL_WIFI);
  lv_obj_add_flag(iconWifi, LV_OBJ_FLAG_HIDDEN);

 lv_tabview_set_act(tabview, 1, LV_ANIM_ON);

  EventsManager::shared().addHandler(eventManager_handler_mainView);

  createHomeView(tab1);
  createSettingView(tab2);
  createInfoView(tab3);
  lv_obj_scroll_to_view_recursive(tab1, LV_ANIM_OFF);
}

void displayWifiConnected(bool _isConnected){
  if(_isConnected == true) 
    lv_obj_clear_flag(iconWifi, LV_OBJ_FLAG_HIDDEN);
  else {
    lv_obj_add_flag(iconWifi, LV_OBJ_FLAG_HIDDEN);
  }
    
}
static void eventManager_handler_mainView(byte event){

   if(event == EVENT_CONNECTWIFI_OK ){
        displayWifiConnected(true);

    }

     if(event == EVENT_CONNECTWIFI_ERROR ){
        displayWifiConnected(false);

    }

}