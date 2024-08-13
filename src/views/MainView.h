#include <lvgl.h>
#include "HomeView.h"
#include "SettingsView.h"


void createMainView();



void createMainView(){
     lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_screen_active());
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, LV_SYMBOL_HOME);
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview,LV_SYMBOL_CHARGE );
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, LV_SYMBOL_SETTINGS);

   static lv_style_t style;
lv_style_init(&style);
lv_style_set_text_font(&style, &lv_font_montserrat_16);
lv_obj_add_style(tab2,  &style, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_style(tab3,  &style, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(tab2, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

    
    lv_tabview_set_tab_bar_position(tabview, LV_DIR_LEFT);
    lv_tabview_set_tab_bar_size(tabview, 50);
      //Style
    static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_pad_all(&layout_style, 0);
    lv_obj_add_style(tab3, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_style_set_border_width(&layout_style, 0);

   

    createHomeView(tab1);
    createSettingView(tab3);

    lv_obj_t * label ;
    label = lv_label_create(tab2);
    lv_label_set_text(label, "Second tab");

  ;

    lv_obj_t * spinner = lv_spinner_create(lv_screen_active());
    lv_obj_set_size(spinner, 30, 30);
    lv_obj_align(spinner, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_set_style_arc_width(spinner, 3, LV_PART_MAIN); // Changes background arc width
    lv_obj_set_style_arc_width(spinner, 3, LV_PART_INDICATOR); 
    lv_obj_set_style_arc_color(spinner,lv_palette_main(LV_PALETTE_RED),LV_PART_INDICATOR);
    lv_spinner_set_anim_params(spinner, 1000, 200);

    //lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);

}