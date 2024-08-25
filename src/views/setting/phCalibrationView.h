#include <lvgl.h>

lv_obj_t * phLevel_label;
lv_obj_t * message_label ;
lv_timer_t * timerCalibration;
void timerPhValue(lv_timer_t * timerlv);
float phValue = 0.0;
static float ph1 = 4.01;
static float ph2 = 6.86;
int step = 1;
Probe probePh = Probe(PH_PIN,PROBE_PH);

static void event_handler_back(lv_event_t * e);
void step_1();
void step_2();

static void event_handler_back(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        lv_timer_pause(timerCalibration);
        lv_timer_del(timerCalibration);
     lv_obj_del((lv_obj_t*)obj->user_data);

    }
}

static void event_handler_calibration_next(lv_event_t * e){
    //save ph value
    if(step==1){

        step_2();
        step = 2;
    }
    if(step==2){

    }
   

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
    message_label = lv_label_create(cont);
    lv_obj_align( message_label, LV_ALIGN_CENTER, 0, 0);

    //btn next
    lv_obj_t * btnNext = lv_btn_create(cont);
    lv_obj_t * label = lv_label_create(btnNext);
    lv_label_set_text(label, "OK");
    lv_obj_center(label);
    lv_obj_align_to(btnNext, message_label,LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_add_event_cb(btnNext, event_handler_calibration_next, LV_EVENT_CLICKED, NULL);

    phLevel_label = lv_label_create(cont);
    lv_label_set_text(phLevel_label,  "Ph: 6.01");
    lv_obj_align_to( phLevel_label,cont, LV_ALIGN_TOP_LEFT, 0, 0);
    timerCalibration = lv_timer_create(timerPhValue, 500,  NULL);

  
    step_1();

}

void step_1(){
     lv_label_set_text_fmt(message_label,  "Please put PH to %.1f",ph1);
}
void step_2(){
     lv_label_set_text_fmt(message_label,  "Please put PH to %.1f",ph2);
}

void saveAndExit(){

}


void timerPhValue(lv_timer_t * timerlv)
{

   float _ph=  probePh.readPH(&preferences);
      lv_label_set_text_fmt(phLevel_label,"%.1f", _ph);
}