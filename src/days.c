#include <pebble.h>
#include "days.h"

static Layer *s_days_layer;

static GFont s_smalldays_font;

GColor color_days_fondo;
GColor color_days_texto;
GColor color_grafico_max;
GColor color_grafico_min;
GColor color_days_marco_grafico;

static TextLayer *s_cabecera1days_layer;
static TextLayer *s_cabecera2days_layer;
static TextLayer *s_cabecera3days_layer;
static TextLayer *s_cabecera4days_layer;
static TextLayer *s_tempmax1days_layer;
static TextLayer *s_tempmax2days_layer;
static TextLayer *s_tempmax3days_layer;
static TextLayer *s_tempmax4days_layer;
static TextLayer *s_tempmin1days_layer;
static TextLayer *s_tempmin2days_layer;
static TextLayer *s_tempmin3days_layer;
static TextLayer *s_tempmin4days_layer;
static TextLayer *s_lluvia1days_layer;
static TextLayer *s_lluvia2days_layer;
static TextLayer *s_lluvia3days_layer;
static TextLayer *s_lluvia4days_layer;

static BitmapLayer *s_icon1days_layer;
static GBitmap *s_icon1days_bitmap;
static BitmapLayer *s_icon2days_layer;
static GBitmap *s_icon2days_bitmap;
static BitmapLayer *s_icon3days_layer;
static GBitmap *s_icon3days_bitmap;
static BitmapLayer *s_icon4days_layer;
static GBitmap *s_icon4days_bitmap;

//grafico
static TextLayer *s_tempmaxgraph_layer;
static TextLayer *s_tempmingraph_layer;
static Layer *s_path_layer;
static TextLayer *s_etiqueta1graph_layer;
static TextLayer *s_etiqueta2graph_layer;
static TextLayer *s_fondo_graph_layer;

struct data_days{
  char cabecera1[6];
  char cabecera2[6];
  char cabecera3[6];
  char cabecera4[6];
  char icon1[4];
  char icon2[4];
  char icon3[4];
  char icon4[4];
  char tempmax1[6];
  char tempmax2[6];
  char tempmax3[6];
  char tempmax4[6];
  char tempmin1[6];
  char tempmin2[6];
  char tempmin3[6];
  char tempmin4[6];
  char lluvia1[5];
  char lluvia2[5];
  char lluvia3[5];
  char lluvia4[5];
  int tempsmax[10];
  int tempsmin[10];
  char stempmax[4];
  char stempmin[4];
  int tempmax;
  int tempmin;
  char etiquetas[2][3];
};

struct data_days data;
/************************************************************************/

void get_data_days(){
  if(persist_exists(1)){
    persist_read_string(35, data.cabecera1, sizeof(data.cabecera1));
    persist_read_string(36, data.cabecera2, sizeof(data.cabecera2));
    persist_read_string(37, data.cabecera3, sizeof(data.cabecera3));
    persist_read_string(38, data.cabecera4, sizeof(data.cabecera4));
    persist_read_string(39, data.tempmax1, sizeof(data.tempmax1));
    persist_read_string(40, data.tempmax2, sizeof(data.tempmax2));
    persist_read_string(41, data.tempmax3, sizeof(data.tempmax3));
    persist_read_string(42, data.tempmax4, sizeof(data.tempmax4));
    persist_read_string(43, data.tempmin1, sizeof(data.tempmin1));
    persist_read_string(44, data.tempmin2, sizeof(data.tempmin2));
    persist_read_string(45, data.tempmin3, sizeof(data.tempmin3));
    persist_read_string(46, data.tempmin4, sizeof(data.tempmin4));
    persist_read_string(47, data.lluvia1, sizeof(data.lluvia1));
    persist_read_string(48, data.lluvia2, sizeof(data.lluvia2));
    persist_read_string(49, data.lluvia3, sizeof(data.lluvia3));
    persist_read_string(50, data.lluvia4, sizeof(data.lluvia4));
    persist_read_string(55, data.icon1, sizeof(data.icon1));
    persist_read_string(56, data.icon2, sizeof(data.icon2));
    persist_read_string(57, data.icon3, sizeof(data.icon3));
    persist_read_string(58, data.icon4, sizeof(data.icon4));
    for(int i = 0;i < 10;i++){
      data.tempsmax[i] = persist_read_int(84+i);
      data.tempsmin[i] = persist_read_int(84+10+i);
    }
    data.tempmax = persist_read_int(104);
    data.tempmin = persist_read_int(105);
    persist_read_string(106, data.stempmax, sizeof(data.stempmax));
    persist_read_string(107, data.stempmin, sizeof(data.stempmin));
    persist_read_string(111, data.etiquetas[0], sizeof(data.etiquetas[0]));
    persist_read_string(112, data.etiquetas[1], sizeof(data.etiquetas[1]));
  }
}

void changeicon_days(GBitmap* bitmap, char dataicon[]){
  if(strcmp(dataicon,"cle")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  }else if(strcmp(dataicon,"clo")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLOUDY36);
  }else if(strcmp(dataicon,"flu")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_FLURRIES36);
  }else if(strcmp(dataicon,"fog")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_FOG36);
  }else if(strcmp(dataicon,"hzy")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HAZY36);
  }else if(strcmp(dataicon,"mcl")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MOSTLYCLOUDY36);
  }else if(strcmp(dataicon,"msu")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MOSTLYCLEAR36);
  }else if(strcmp(dataicon,"rai")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_RAIN36);
  }else if(strcmp(dataicon,"snw")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SNOW36);
  }else if(strcmp(dataicon,"str")==0){
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_STORM36);
  }
}

/************************************************************************/

// This is the layer update callback which is called on render updates
static void path_layer_update_callback(Layer *layer, GContext *ctx) {
  graphics_context_set_stroke_color(ctx, color_days_marco_grafico);
  graphics_draw_line(ctx, GPoint(12, 0), GPoint(12, 51));
  graphics_draw_line(ctx, GPoint(0, 41), GPoint(143, 41));
  //puntos de las horas
  for(int i = 0;i< 10;i++){
    if((i!=0)&&(i!=7)){
      graphics_draw_pixel(ctx, GPoint(18+i*13,42));
    }
  }
  int rango = data.tempmax -data.tempmin;
  for(int i=0;i<9;i++){
    graphics_context_set_stroke_color(ctx, color_grafico_max);
    graphics_draw_line(ctx, GPoint(18+i*13, (int)(40-40*(data.tempsmax[(i)]-data.tempmin)/rango)), GPoint(18+(i+1)*13, (int)(40-40*(data.tempsmax[i+1]-data.tempmin)/rango))); 
    graphics_context_set_stroke_color(ctx, color_grafico_min);
    graphics_draw_line(ctx, GPoint(18+i*13, (int)(40-40*(data.tempsmin[(i)]-data.tempmin)/rango)), GPoint(18+(i+1)*13, (int)(40-40*(data.tempsmin[i+1]-data.tempmin)/rango))); 
  }
}


/************************************************************************/

void load_days_layer(Window *window){
  //datos
  get_data_days();
  //capa general
  s_days_layer = layer_create(GRect(0,16,144,152));
  layer_add_child(window_get_root_layer(window),s_days_layer);
  //fuentes
  s_smalldays_font = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  
  #ifdef PBL_BW
    color_days_fondo = GColorBlack;
    color_days_texto = GColorWhite;
    color_grafico_max = GColorWhite;
    color_grafico_min = GColorWhite;
    color_days_marco_grafico = GColorWhite;
  #else
    //color_days_fondo = GColorElectricBlue;
    color_days_fondo = GColorWhite;
    color_days_texto = GColorBlack;
    color_grafico_max = GColorRed;
    color_grafico_min = GColorBlue;
    color_days_marco_grafico = GColorBlack;
  #endif
  
  //Cabecera
  //1
  s_cabecera1days_layer = text_layer_create(GRect(0, 0, 36, 16));
  text_layer_set_font(s_cabecera1days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_cabecera1days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_cabecera1days_layer, color_days_fondo);
  text_layer_set_text_color(s_cabecera1days_layer, color_days_texto);
  text_layer_set_text(s_cabecera1days_layer, data.cabecera1);
  layer_add_child(s_days_layer, text_layer_get_layer(s_cabecera1days_layer));
  //2
  s_cabecera2days_layer = text_layer_create(GRect(36, 0, 36, 16));
  text_layer_set_font(s_cabecera2days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_cabecera2days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_cabecera2days_layer, color_days_fondo);
  text_layer_set_text_color(s_cabecera2days_layer, color_days_texto);
  text_layer_set_text(s_cabecera2days_layer, data.cabecera2);
  layer_add_child(s_days_layer, text_layer_get_layer(s_cabecera2days_layer));
  //3
  s_cabecera3days_layer = text_layer_create(GRect(72, 0, 36, 16));
  text_layer_set_font(s_cabecera3days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_cabecera3days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_cabecera3days_layer, color_days_fondo);
  text_layer_set_text_color(s_cabecera3days_layer, color_days_texto);
  text_layer_set_text(s_cabecera3days_layer, data.cabecera3);
  layer_add_child(s_days_layer, text_layer_get_layer(s_cabecera3days_layer));
  //4
  s_cabecera4days_layer = text_layer_create(GRect(108, 0, 36, 16));
  text_layer_set_font(s_cabecera4days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_cabecera4days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_cabecera4days_layer, color_days_fondo);
  text_layer_set_text_color(s_cabecera4days_layer, color_days_texto);
  text_layer_set_text(s_cabecera4days_layer, data.cabecera4);
  layer_add_child(s_days_layer, text_layer_get_layer(s_cabecera4days_layer));
  
  //Iconos
  //1
  s_icon1days_layer = bitmap_layer_create(GRect(0,16,36,36));
  bitmap_layer_set_compositing_mode(s_icon1days_layer, GCompOpSet);
  s_icon1days_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  changeicon_days(s_icon1days_bitmap,data.icon1);
  bitmap_layer_set_bitmap(s_icon1days_layer, s_icon1days_bitmap);
  layer_add_child(s_days_layer, bitmap_layer_get_layer(s_icon1days_layer));  
  //2
  s_icon2days_layer = bitmap_layer_create(GRect(36,16,36,36));
  bitmap_layer_set_compositing_mode(s_icon2days_layer, GCompOpSet);
  s_icon2days_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  changeicon_days(s_icon2days_bitmap,data.icon2);
  bitmap_layer_set_bitmap(s_icon2days_layer, s_icon2days_bitmap);
  layer_add_child(s_days_layer, bitmap_layer_get_layer(s_icon2days_layer));  
  //3
  s_icon3days_layer = bitmap_layer_create(GRect(72,16,36,36));
  bitmap_layer_set_compositing_mode(s_icon3days_layer, GCompOpSet);
  s_icon3days_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  changeicon_days(s_icon3days_bitmap,data.icon3);
  bitmap_layer_set_bitmap(s_icon3days_layer, s_icon3days_bitmap);
  layer_add_child(s_days_layer, bitmap_layer_get_layer(s_icon3days_layer));  
  //4
  s_icon4days_layer = bitmap_layer_create(GRect(108,16,36,36));
  bitmap_layer_set_compositing_mode(s_icon4days_layer, GCompOpSet);
  s_icon4days_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  changeicon_days(s_icon4days_bitmap,data.icon4);
  bitmap_layer_set_bitmap(s_icon4days_layer, s_icon4days_bitmap);
  layer_add_child(s_days_layer, bitmap_layer_get_layer(s_icon4days_layer));  
  
  //Temperatura max
  //1
  s_tempmax1days_layer = text_layer_create(GRect(0, 52, 36, 16));
  text_layer_set_font(s_tempmax1days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmax1days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_tempmax1days_layer, color_days_fondo);
  text_layer_set_text_color(s_tempmax1days_layer, color_grafico_max);
  text_layer_set_text(s_tempmax1days_layer, data.tempmax1);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmax1days_layer));
  //2
  s_tempmax2days_layer = text_layer_create(GRect(36, 52, 36, 16));
  text_layer_set_font(s_tempmax2days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmax2days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_tempmax2days_layer, color_days_fondo);
  text_layer_set_text_color(s_tempmax2days_layer, color_grafico_max);
  text_layer_set_text(s_tempmax2days_layer, data.tempmax2);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmax2days_layer));
  //3
  s_tempmax3days_layer = text_layer_create(GRect(72, 52, 36, 16));
  text_layer_set_font(s_tempmax3days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmax3days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_tempmax3days_layer, color_days_fondo);
  text_layer_set_text_color(s_tempmax3days_layer, color_grafico_max);
  text_layer_set_text(s_tempmax3days_layer, data.tempmax3);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmax3days_layer));
  //4
  s_tempmax4days_layer = text_layer_create(GRect(108, 52, 36, 16));
  text_layer_set_font(s_tempmax4days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmax4days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_tempmax4days_layer, color_days_fondo);
  text_layer_set_text_color(s_tempmax4days_layer, color_grafico_max);
  text_layer_set_text(s_tempmax4days_layer, data.tempmax4);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmax4days_layer));
  
  //Temperatura min
  //1
  s_tempmin1days_layer = text_layer_create(GRect(0, 68, 36, 16));
  text_layer_set_font(s_tempmin1days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmin1days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_tempmin1days_layer, color_days_fondo);
  text_layer_set_text_color(s_tempmin1days_layer, color_grafico_min);
  text_layer_set_text(s_tempmin1days_layer, data.tempmin1);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmin1days_layer));
  //2
  s_tempmin2days_layer = text_layer_create(GRect(36, 68, 36, 16));
  text_layer_set_font(s_tempmin2days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmin2days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_tempmin2days_layer, color_days_fondo);
  text_layer_set_text_color(s_tempmin2days_layer, color_grafico_min);
  text_layer_set_text(s_tempmin2days_layer, data.tempmin2);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmin2days_layer));
  //3
  s_tempmin3days_layer = text_layer_create(GRect(72, 68, 36, 16));
  text_layer_set_font(s_tempmin3days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmin3days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_tempmin3days_layer, color_days_fondo);
  text_layer_set_text_color(s_tempmin3days_layer, color_grafico_min);
  text_layer_set_text(s_tempmin3days_layer, data.tempmin3);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmin3days_layer));
  //4
  s_tempmin4days_layer = text_layer_create(GRect(108, 68, 36, 16));
  text_layer_set_font(s_tempmin4days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmin4days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_tempmin4days_layer, color_days_fondo);
  text_layer_set_text_color(s_tempmin4days_layer, color_grafico_min);
  text_layer_set_text(s_tempmin4days_layer, data.tempmin4);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmin4days_layer));
  
  s_fondo_graph_layer= text_layer_create(GRect(0,100,144,52));
  text_layer_set_background_color(s_fondo_graph_layer, GColorWhite);
  layer_add_child(s_days_layer, text_layer_get_layer(s_fondo_graph_layer));
  
  
  //grafico
  //max
  s_tempmaxgraph_layer = text_layer_create(GRect(-4, 95, 16, 16));
  text_layer_set_font(s_tempmaxgraph_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmaxgraph_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_tempmaxgraph_layer, GColorWhite);
  text_layer_set_text_color(s_tempmaxgraph_layer, color_days_texto);
  text_layer_set_text(s_tempmaxgraph_layer, data.stempmax);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmaxgraph_layer));
  //min
  s_tempmingraph_layer = text_layer_create(GRect(-4, 126, 16, 16));
  text_layer_set_font(s_tempmingraph_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_tempmingraph_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_tempmingraph_layer, GColorWhite);
  text_layer_set_text_color(s_tempmingraph_layer, color_days_texto);
  text_layer_set_text(s_tempmingraph_layer, data.stempmin);
  layer_add_child(s_days_layer, text_layer_get_layer(s_tempmingraph_layer));
  //etiqueta1
  s_etiqueta1graph_layer = text_layer_create(GRect(11, 138, 16, 16));
  text_layer_set_font(s_etiqueta1graph_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_etiqueta1graph_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_etiqueta1graph_layer, GColorWhite);
  text_layer_set_text_color(s_etiqueta1graph_layer, color_days_texto);
  text_layer_set_text(s_etiqueta1graph_layer, data.etiquetas[0]);
  layer_add_child(s_days_layer, text_layer_get_layer(s_etiqueta1graph_layer));
  //etiqueta2
  s_etiqueta2graph_layer = text_layer_create(GRect(102, 138, 16, 16));
  text_layer_set_font(s_etiqueta2graph_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_etiqueta2graph_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_etiqueta2graph_layer, GColorWhite);
  text_layer_set_text_color(s_etiqueta2graph_layer, color_days_texto);
  text_layer_set_text(s_etiqueta2graph_layer, data.etiquetas[1]);
  layer_add_child(s_days_layer, text_layer_get_layer(s_etiqueta2graph_layer));
  
  
  //Lluvia
  //1
  s_lluvia1days_layer = text_layer_create(GRect(0, 84, 36, 16));
  text_layer_set_font(s_lluvia1days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_lluvia1days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvia1days_layer, color_days_fondo);
  text_layer_set_text_color(s_lluvia1days_layer, color_days_texto);
  text_layer_set_text(s_lluvia1days_layer, data.lluvia1);
  layer_add_child(s_days_layer, text_layer_get_layer(s_lluvia1days_layer));
  //2
  s_lluvia2days_layer = text_layer_create(GRect(36, 84, 36, 16));
  text_layer_set_font(s_lluvia2days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_lluvia2days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvia2days_layer, color_days_fondo);
  text_layer_set_text_color(s_lluvia2days_layer, color_days_texto);
  text_layer_set_text(s_lluvia2days_layer, data.lluvia2);
  layer_add_child(s_days_layer, text_layer_get_layer(s_lluvia2days_layer));
  //3
  s_lluvia3days_layer = text_layer_create(GRect(72, 84, 36, 16));
  text_layer_set_font(s_lluvia3days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_lluvia3days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvia3days_layer, color_days_fondo);
  text_layer_set_text_color(s_lluvia3days_layer, color_days_texto);
  text_layer_set_text(s_lluvia3days_layer, data.lluvia3);
  layer_add_child(s_days_layer, text_layer_get_layer(s_lluvia3days_layer));
  //4
  s_lluvia4days_layer = text_layer_create(GRect(108, 84, 36, 16));
  text_layer_set_font(s_lluvia4days_layer, s_smalldays_font);
  text_layer_set_text_alignment(s_lluvia4days_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvia4days_layer, color_days_fondo);
  text_layer_set_text_color(s_lluvia4days_layer, color_days_texto);
  text_layer_set_text(s_lluvia4days_layer, data.lluvia4);
  layer_add_child(s_days_layer, text_layer_get_layer(s_lluvia4days_layer));
  
  
  
  
  
  
  
  
  //grafico
  GRect bounds = GRect(0,100,144,52);
  s_path_layer = layer_create(bounds);
  
  layer_set_update_proc(s_path_layer, path_layer_update_callback);
  layer_add_child(s_days_layer, s_path_layer);
  
  layer_mark_dirty(s_path_layer);  
  
  
  
  
}

void unload_days_layer(void){
  text_layer_destroy(s_fondo_graph_layer);
  
  //grafico
  layer_destroy(s_path_layer);
  text_layer_destroy(s_tempmaxgraph_layer);
  text_layer_destroy(s_tempmingraph_layer);
  text_layer_destroy(s_etiqueta1graph_layer);
  text_layer_destroy(s_etiqueta2graph_layer);
  //lluvia
  text_layer_destroy(s_lluvia1days_layer);
  text_layer_destroy(s_lluvia2days_layer);
  text_layer_destroy(s_lluvia3days_layer);
  text_layer_destroy(s_lluvia4days_layer);
  //tempmin
  text_layer_destroy(s_tempmin1days_layer);
  text_layer_destroy(s_tempmin2days_layer);
  text_layer_destroy(s_tempmin3days_layer);
  text_layer_destroy(s_tempmin4days_layer);
  //tempmax
  text_layer_destroy(s_tempmax1days_layer);
  text_layer_destroy(s_tempmax2days_layer);
  text_layer_destroy(s_tempmax3days_layer);
  text_layer_destroy(s_tempmax4days_layer);
  //iconos
  gbitmap_destroy(s_icon1days_bitmap);
  bitmap_layer_destroy(s_icon1days_layer);
  gbitmap_destroy(s_icon2days_bitmap);
  bitmap_layer_destroy(s_icon2days_layer);
  gbitmap_destroy(s_icon3days_bitmap);
  bitmap_layer_destroy(s_icon3days_layer);
  gbitmap_destroy(s_icon4days_bitmap);
  bitmap_layer_destroy(s_icon4days_layer);
  //cabecera
  text_layer_destroy(s_cabecera1days_layer);
  text_layer_destroy(s_cabecera2days_layer);
  text_layer_destroy(s_cabecera3days_layer);
  text_layer_destroy(s_cabecera4days_layer);
  //capa general
  layer_destroy(s_days_layer);
}