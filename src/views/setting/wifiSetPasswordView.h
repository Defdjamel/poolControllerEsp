#include <lvgl.h>
#include <WifiManager.h>
#include "helper/Config.h"

static void event_handler_wifi(lv_event_t * e);
static lv_obj_t * wifiSetPasswordView;
void createKeyboardWifiPassword();
void setPassword();


String  SSID ;
String  SSID_PWD;

void setPassword(){
 

    LV_LOG_USER("SAVE WIFI: %s %s" , SSID.c_str(), SSID_PWD.c_str());
   preferences.putString(SSID_KEY,SSID);
  preferences.putString(PWD_KEY, SSID_PWD);

  EventsManager::shared().callEvent(EVENT_UPDATEWIFICONFIG);


  //connect

  //go to home
  lv_obj_del(wifiSetPasswordView);
}

static void event_handler_wifisetPasswordBack(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if(code == LV_EVENT_CLICKED) {
    LV_LOG_USER("Clicked");
    lv_obj_del(wifiSetPasswordView);
  }
}

static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = (lv_obj_t *) lv_event_get_user_data(e);
    const char * txt = lv_textarea_get_text(ta);
     SSID_PWD = (char*)txt;
    // LV_LOG_USER("text aera event: %s", txt);
}

static void kb_event_cb(lv_event_t * e)
{
      lv_obj_t * kb = lv_event_get_target(e);
  uint32_t btn_id = lv_keyboard_get_selected_btn(kb);
  const char * txt = lv_keyboard_get_btn_text(kb, btn_id);
   LV_LOG_USER("key: %s" , txt);

  if(strcmp(txt, LV_SYMBOL_NEW_LINE  ) == 0 || strcmp(txt, LV_SYMBOL_OK  ) == 0) {

  

    setPassword();
  }
}

void createWifiSetPassword(const char*  _selected){
    SSID = String(_selected);
    
      LV_LOG_USER("SSID: %s" , SSID.c_str());
    wifiSetPasswordView =lv_win_create(lv_scr_act(),45);
    lv_win_add_title(wifiSetPasswordView, SSID.c_str());

    lv_obj_t * btn;
    btn = lv_win_add_btn(wifiSetPasswordView, LV_SYMBOL_LEFT, 46);
    lv_obj_add_event_cb(btn, event_handler_wifisetPasswordBack, LV_EVENT_CLICKED, NULL);

    //STYLE to container 
    lv_obj_t * cont = lv_win_get_content(wifiSetPasswordView); 
    static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_pad_all(&layout_style, 0);
    lv_obj_add_style(cont, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    

    createKeyboardWifiPassword();
}

void createKeyboardWifiPassword()
{   
    
  lv_obj_t * cont = lv_win_get_content(wifiSetPasswordView); 

  /*Create a keyboard to use it with an of the text areas*/
  lv_obj_t * kb = lv_keyboard_create(cont);
  lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 2);
  lv_obj_add_event_cb(kb, kb_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  //title:
  lv_obj_t * pwd_label = lv_label_create(cont);
  lv_label_set_text(pwd_label, LV_SYMBOL_OK "Password:");
  lv_obj_align( cont, LV_ALIGN_OUT_TOP_MID, 0, 0);
  /*Create a text area. The keyboard will write here*/
  lv_obj_t * ta;
  ta = lv_textarea_create(cont);
  lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 20);
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
  lv_textarea_set_placeholder_text(ta, "wifi Password");
  lv_textarea_set_one_line(ta, true);
  lv_obj_set_size(ta, 240, 40);
   
  lv_keyboard_set_textarea(kb, ta);
}