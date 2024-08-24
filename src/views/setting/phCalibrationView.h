#include <lvgl.h>

lv_obj_t * phLevel_label;
float phValue = 0.0;

static void event_handler_back(lv_event_t * e);

static void event_handler_back(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    lv_obj_del((lv_obj_t*)obj->user_data);

    }
}

static void event_handler_calibration_next(lv_event_t * e){
    //save ph value

}

void createCalibrationPHView(){
     lv_obj_t * phCalibView;
     phCalibView =lv_win_create(lv_scr_act(),45);
    lv_win_add_title(phCalibView, "Ph calibration");
    
    lv_obj_t * btn;
    btn = lv_win_add_btn(phCalibView, LV_SYMBOL_LEFT, 46);
    lv_obj_add_event_cb(btn, event_handler_back, LV_EVENT_CLICKED, NULL);
    lv_obj_set_user_data(btn, phCalibView);

    lv_obj_t * cont = lv_win_get_content(phCalibView); 

    // LABEL MESSAGE
    lv_obj_t * message_label = lv_label_create(cont);
    lv_label_set_text(message_label,  "Please put PH to 4.O1 ");
    lv_obj_align( message_label, LV_ALIGN_CENTER, 0, 0);

    //btn next
    lv_obj_t * btnNext = lv_btn_create(cont);
    lv_obj_t * label = lv_label_create(btnNext);
    lv_label_set_text(label, "OK");
    lv_obj_center(label);
    lv_obj_align_to(btnNext, message_label,LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    phLevel_label = lv_label_create(cont);
    lv_label_set_text(phLevel_label,  "Ph: 6.01");
    lv_obj_align_to( phLevel_label,cont, LV_ALIGN_TOP_LEFT, 0, 0);

}