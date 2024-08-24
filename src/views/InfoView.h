#include <lvgl.h>
#include <esp_wifi.h>
void updateListInfo();
static void eventManager_info(byte event);

static lv_obj_t * listInfo;

static void eventManager_info(byte event){
     if(event == EVENT_CONNECTWIFI_OK ){
        updateListInfo();

    }
    else if(event == EVENT_CONNECTWIFI_ERROR ){
        updateListInfo();
    }
}

void createInfoView(lv_obj_t *parent)
{
   /*Create a list*/
    listInfo = lv_list_create(parent);
    lv_obj_set_size(listInfo, lv_pct(100),  lv_pct(100));
    lv_obj_center(listInfo);
    // Style
    static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_radius(&layout_style, 0);
	lv_style_set_pad_all(&layout_style, 10);
    lv_style_set_outline_pad(&layout_style, 10);
	lv_style_set_outline_width(&layout_style, 10);
    lv_style_set_bg_opa(&layout_style, LV_OPA_TRANSP);
    lv_style_set_border_width(&layout_style, 0);
    lv_obj_add_style(listInfo, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    updateListInfo();
    EventsManager::shared().addHandler(eventManager_info);

   lv_obj_t *  label = lv_label_create(parent);
     lv_label_set_text(label,"Pool Controller by James ");
      lv_obj_set_style_text_font(label, &lv_font_montserrat_12,LV_PART_MAIN| LV_STATE_DEFAULT);
     lv_obj_align(label, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
}

void updateListInfo(){
       lv_obj_t * label;
    lv_obj_clean(listInfo);
    lv_list_add_text(listInfo, "Informations :");
    if(WiFi.status() != WL_CONNECTED){
           label = lv_label_create(listInfo);
           lv_label_set_text(label,"Pas connecté ");

    }else{

         label = lv_label_create(listInfo);
        lv_label_set_text_fmt(label,LV_SYMBOL_WIFI " Wifi :  %s ",WiFi.SSID());
        label = lv_label_create(listInfo);
        lv_label_set_text_fmt(label,"ip adress :  %s ",WiFi.localIP().toString());
    }
     label = lv_label_create(listInfo);
     lv_label_set_text_fmt(label,"mac :  %s ",WiFi.macAddress().c_str());
}