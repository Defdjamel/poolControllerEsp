#include <lvgl.h>

Probe phProbe2 = Probe(PH_PIN, PROBE_PH);
void createHomeView(lv_obj_t *parent);
void sendPhToServer();
lv_obj_t * createBlockPh(lv_obj_t *parent);
lv_obj_t * createBlockOrp(lv_obj_t *parent);
void my_timer(lv_timer_t * timer);
 lv_obj_t * labelPH;
  lv_obj_t * labelORP;
  float PhVal = 0;

//  static lv_subject_t  phvalue;
//  static lv_subject_t orpvalue;



void createHomeView(lv_obj_t *parent){
    static uint32_t user_data = 10;

    // GRID
static lv_coord_t col_dsc[] = {100, 100, LV_GRID_TEMPLATE_LAST};
static lv_coord_t row_dsc[] = {100,100, LV_GRID_TEMPLATE_LAST};
 lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, lv_pct(100), lv_pct(100));
    lv_obj_center(cont);
    lv_obj_set_layout(cont, LV_LAYOUT_GRID);
// STYLE
    	static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_radius(&layout_style, 0);
	lv_style_set_pad_all(&layout_style, 0);
    lv_style_set_outline_pad(&layout_style, 0);
	lv_style_set_outline_width(&layout_style, 0);
    lv_style_set_bg_opa(&layout_style, LV_OPA_TRANSP);
    lv_obj_add_style(cont, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_style_set_border_width(&layout_style, 0);
    
   
// lv_subject_init_int(&phvalue, 7.1);
// lv_subject_init_int(&orpvalue, 300);
   uint32_t i;
    for(i = 0; i < 2; i++) {
        uint8_t col = i % 2;
        uint8_t row = i / 2;
         lv_obj_t *parent_1;
        if(col== 0) parent_1 = createBlockPh(cont);
        if(col== 1) parent_1 = createBlockOrp(cont);

 lv_obj_set_grid_cell(parent_1, LV_GRID_ALIGN_STRETCH, col, 1,
                             LV_GRID_ALIGN_STRETCH, row, 1);
    

   }
lv_timer_t * timerlv = lv_timer_create(my_timer, 2000,  &user_data);


}

lv_obj_t * createBlockPh(lv_obj_t *parent){

   
    lv_obj_t * obj;
    obj = lv_btn_create(parent);
    lv_obj_t *label = lv_label_create(obj);
    lv_label_set_text(label, "PH");
    lv_obj_set_align(label,LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_bg_color(obj,lv_color_hex(0xff0000), LV_PART_MAIN);//GREEN

    labelPH = lv_label_create(obj);
    // lv_label_bind_text(label, bindVal, " %d ");
      lv_label_set_text(labelPH, "...");
    lv_obj_center(labelPH);
    lv_obj_set_style_text_font(labelPH, &lv_font_montserrat_32, LV_PART_MAIN| LV_STATE_DEFAULT);

    static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_radius(&layout_style, 0);
    lv_obj_add_style(obj, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
   

    return obj; 
}


lv_obj_t * createBlockOrp(lv_obj_t *parent){

   lv_obj_t * obj;
    obj = lv_btn_create(parent);
    lv_obj_set_style_bg_color(obj,lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
    lv_obj_t *label = lv_label_create(obj);
    lv_label_set_text(label, "Chlore");
    lv_obj_set_align(label,LV_ALIGN_TOP_LEFT);

    labelORP = lv_label_create(obj);
    // lv_label_bind_text(label, bindVal, " %d ");
      lv_label_set_text(labelORP, "...");
    lv_obj_center(labelORP);
    lv_obj_set_style_text_font(labelORP, &lv_font_montserrat_32, LV_PART_MAIN| LV_STATE_DEFAULT);

    static lv_style_t layout_style;
	lv_style_init(&layout_style);
	lv_style_set_radius(&layout_style, 0);
    lv_obj_add_style(obj, &layout_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    

    return obj; 
}



void my_timer(lv_timer_t * timerlv)
{

 PhVal =  phProbe2.readPH(&preferences);
  /*Use the user_data*/
  uint32_t *user_data = (uint32_t*)timerlv->user_data;
//   printf("my_timer called with user data: %d\n", timerlv->last_run);
  lv_label_set_text_fmt(labelPH,"%.1f", PhVal);
  lv_label_set_text_fmt(labelORP,"%d", timerlv->last_run/100);
  sendPhToServer();

}

void sendPhToServer(){
String n[2][2] = {{"mac","Hello"},{"ph","12.3"}};
  sendPostRequest(SERVER_API_PH,"",SERVER_PORT, n,2)  ;
}