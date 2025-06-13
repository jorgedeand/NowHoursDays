#include <pebble.h>
#include "hours.h"

static Layer *s_hours_layer;

static GFont s_smallhours_font;

GColor color_hours_fondo;
GColor color_hours_texto;
GColor color_hours_viento;
GColor color_hours_grafico;
GColor color_hours_marco_grafico;

static TextLayer *s_cabecera1hours_layer;
static TextLayer *s_cabecera2hours_layer;
static TextLayer *s_cabecera3hours_layer;
static TextLayer *s_cabecera4hours_layer;
static TextLayer *s_temp1hours_layer;
static TextLayer *s_temp2hours_layer;
static TextLayer *s_temp3hours_layer;
static TextLayer *s_temp4hours_layer;
static TextLayer *s_lluvia1hours_layer;
static TextLayer *s_lluvia2hours_layer;
static TextLayer *s_lluvia3hours_layer;
static TextLayer *s_lluvia4hours_layer;
static TextLayer *s_viento1hours_layer;
static TextLayer *s_viento2hours_layer;
static TextLayer *s_viento3hours_layer;
static TextLayer *s_viento4hours_layer;

static BitmapLayer *s_icon1hours_layer;
static GBitmap *s_icon1hours_bitmap;
static BitmapLayer *s_icon2hours_layer;
static GBitmap *s_icon2hours_bitmap;
static BitmapLayer *s_icon3hours_layer;
static GBitmap *s_icon3hours_bitmap;
static BitmapLayer *s_icon4hours_layer;
static GBitmap *s_icon4hours_bitmap;


//grafico
static TextLayer *s_tempmaxgraph_layer;
static TextLayer *s_tempmingraph_layer;
static Layer *s_path_layer;
static TextLayer *s_etiqueta1graph_layer;
static TextLayer *s_etiqueta2graph_layer;
static TextLayer *s_etiqueta3graph_layer;



struct data_hours{
  char cabecera1[6];
  char cabecera2[6];
  char cabecera3[6];
  char cabecera4[6];
  char icon1[4];
  char icon2[4];
  char icon3[4];
  char icon4[4];
  char temp1[6];
  char temp2[6];
  char temp3[6];
  char temp4[6];
  char lluvia1[5];
  char lluvia2[5];
  char lluvia3[5];
  char lluvia4[5];
  char viento1[4];
  char viento2[4];
  char viento3[4];
  char viento4[4];
  char tempsmax[4];
  char tempsmin[4];
  int tempmax;
  int tempmin;
  int temps[24];
  char etiquetas[3][3];
};

struct data_hours data;
/************************************************************************/

void get_data_hours(){
  if(persist_exists(1)){
    persist_read_string(15, data.cabecera1, sizeof(data.cabecera1));
    persist_read_string(16, data.cabecera2, sizeof(data.cabecera2));
    persist_read_string(17, data.cabecera3, sizeof(data.cabecera3));
    persist_read_string(18, data.cabecera4, sizeof(data.cabecera4));
    persist_read_string(19, data.temp1, sizeof(data.temp1));
    persist_read_string(20, data.temp2, sizeof(data.temp2));
    persist_read_string(21, data.temp3, sizeof(data.temp3));
    persist_read_string(22, data.temp4, sizeof(data.temp4));
    persist_read_string(23, data.lluvia1, sizeof(data.lluvia1));
    persist_read_string(24, data.lluvia2, sizeof(data.lluvia2));
    persist_read_string(25, data.lluvia3, sizeof(data.lluvia3));
    persist_read_string(26, data.lluvia4, sizeof(data.lluvia4));
    persist_read_string(27, data.viento1, sizeof(data.viento1));
    persist_read_string(28, data.viento2, sizeof(data.viento2));
    persist_read_string(29, data.viento3, sizeof(data.viento3));
    persist_read_string(30, data.viento4, sizeof(data.viento4));
    persist_read_string(51, data.icon1, sizeof(data.icon1));
    persist_read_string(52, data.icon2, sizeof(data.icon2));
    persist_read_string(53, data.icon3, sizeof(data.icon3));
    persist_read_string(54, data.icon4, sizeof(data.icon4));
    persist_read_string(59, data.tempsmax, sizeof(data.tempsmax));
    persist_read_string(60, data.tempsmin, sizeof(data.tempsmin));
    data.tempmax = persist_read_int(61);
    data.tempmin = persist_read_int(62);
    for(int i = 0;i<21;i++){
      data.temps[i] = persist_read_int(i+63);
    }
    persist_read_string(108, data.etiquetas[0], sizeof(data.etiquetas[0]));
    persist_read_string(109, data.etiquetas[1], sizeof(data.etiquetas[1]));
    persist_read_string(110, data.etiquetas[2], sizeof(data.etiquetas[2]));
  }
}

void changeicon_hours(GBitmap* bitmap, char dataicon[]){
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "data:%s", dataicon);
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
  graphics_context_set_stroke_color(ctx, color_hours_marco_grafico);
  
  graphics_draw_line(ctx, GPoint(12, 0), GPoint(12, 51));
  graphics_draw_line(ctx, GPoint(0, 41), GPoint(143, 41));
  //puntos de las horas
  for(int i = 0;i< 21;i++){
    if((i!=0)&&(i!=10)&&(i!=20)){
      graphics_draw_pixel(ctx, GPoint(18+i*6,42));
    }
  }
  int rango = data.tempmax -data.tempmin;
  for(int i=0;i<20;i++){
    graphics_context_set_stroke_color(ctx, color_hours_grafico);
    graphics_draw_line(ctx, GPoint(18+i*6, (int)(40-40*(data.temps[(i)]-data.tempmin)/rango)), GPoint(18+(i+1)*6, (int)(40-40*(data.temps[i+1]-data.tempmin)/rango))); 
  }
  
}

/************************************************************************/


void load_hours_layer(Window *window){
  //datos
  get_data_hours();
  //capa general
  s_hours_layer = layer_create(GRect(0,16,144,152));
  layer_add_child(window_get_root_layer(window),s_hours_layer);
  //fuentes
  s_smallhours_font = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  //colores
  #ifdef PBL_BW
    color_hours_fondo = GColorBlack;
    color_hours_texto = GColorWhite;
    color_hours_viento = GColorWhite;
    color_hours_grafico = GColorWhite;
    color_hours_marco_grafico = GColorWhite;
  #else
    color_hours_fondo = GColorWhite;
    color_hours_texto = GColorBlack;
    color_hours_viento = GColorDarkGreen;
    color_hours_grafico = GColorRed;
    color_hours_marco_grafico = GColorBlack;
  #endif
  
  //Cabecera
  //1
  s_cabecera1hours_layer = text_layer_create(GRect(0, 0, 36, 16));
  text_layer_set_font(s_cabecera1hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_cabecera1hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_cabecera1hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_cabecera1hours_layer, color_hours_texto);
  text_layer_set_text(s_cabecera1hours_layer, data.cabecera1);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_cabecera1hours_layer));
  //2
  s_cabecera2hours_layer = text_layer_create(GRect(36, 0, 36, 16));
  text_layer_set_font(s_cabecera2hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_cabecera2hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_cabecera2hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_cabecera2hours_layer, color_hours_texto);
  text_layer_set_text(s_cabecera2hours_layer, data.cabecera2);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_cabecera2hours_layer));
  //3
  s_cabecera3hours_layer = text_layer_create(GRect(72, 0, 36, 16));
  text_layer_set_font(s_cabecera3hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_cabecera3hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_cabecera3hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_cabecera3hours_layer, color_hours_texto);
  text_layer_set_text(s_cabecera3hours_layer, data.cabecera3);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_cabecera3hours_layer));
  //4
  s_cabecera4hours_layer = text_layer_create(GRect(108, 0, 36, 16));
  text_layer_set_font(s_cabecera4hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_cabecera4hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_cabecera4hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_cabecera4hours_layer, color_hours_texto);
  text_layer_set_text(s_cabecera4hours_layer, data.cabecera4);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_cabecera4hours_layer));
  
  //Iconos
  //1
  s_icon1hours_layer = bitmap_layer_create(GRect(0,16,36,36));
  bitmap_layer_set_compositing_mode(s_icon1hours_layer, GCompOpSet);
  s_icon1hours_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  changeicon_hours(s_icon1hours_bitmap,data.icon1);
  bitmap_layer_set_bitmap(s_icon1hours_layer, s_icon1hours_bitmap);
  layer_add_child(s_hours_layer, bitmap_layer_get_layer(s_icon1hours_layer));  
  //2
  s_icon2hours_layer = bitmap_layer_create(GRect(36,16,36,36));
  bitmap_layer_set_compositing_mode(s_icon2hours_layer, GCompOpSet);
  s_icon2hours_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  changeicon_hours(s_icon2hours_bitmap,data.icon2);
  bitmap_layer_set_bitmap(s_icon2hours_layer, s_icon2hours_bitmap);
  layer_add_child(s_hours_layer, bitmap_layer_get_layer(s_icon2hours_layer));  
  //3
  s_icon3hours_layer = bitmap_layer_create(GRect(72,16,36,36));
  bitmap_layer_set_compositing_mode(s_icon3hours_layer, GCompOpSet);
  s_icon3hours_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  changeicon_hours(s_icon3hours_bitmap,data.icon3);
  bitmap_layer_set_bitmap(s_icon3hours_layer, s_icon3hours_bitmap);
  layer_add_child(s_hours_layer, bitmap_layer_get_layer(s_icon3hours_layer));  
  //4
  s_icon4hours_layer = bitmap_layer_create(GRect(108,16,36,36));
  bitmap_layer_set_compositing_mode(s_icon4hours_layer, GCompOpSet);
  s_icon4hours_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLEAR36);
  changeicon_hours(s_icon4hours_bitmap,data.icon4);
  bitmap_layer_set_bitmap(s_icon4hours_layer, s_icon4hours_bitmap);
  layer_add_child(s_hours_layer, bitmap_layer_get_layer(s_icon4hours_layer));  
  
  //Temperatura
  //1
  s_temp1hours_layer = text_layer_create(GRect(0, 52, 36, 16));
  text_layer_set_font(s_temp1hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_temp1hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_temp1hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_temp1hours_layer, color_hours_grafico);
  text_layer_set_text(s_temp1hours_layer, data.temp1);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_temp1hours_layer));
  //2
  s_temp2hours_layer = text_layer_create(GRect(36, 52, 36, 16));
  text_layer_set_font(s_temp2hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_temp2hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_temp2hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_temp2hours_layer, color_hours_grafico);
  text_layer_set_text(s_temp2hours_layer, data.temp2);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_temp2hours_layer));
  //3
  s_temp3hours_layer = text_layer_create(GRect(72, 52, 36, 16));
  text_layer_set_font(s_temp3hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_temp3hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_temp3hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_temp3hours_layer, color_hours_grafico);
  text_layer_set_text(s_temp3hours_layer, data.temp3);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_temp3hours_layer));
  //4
  s_temp4hours_layer = text_layer_create(GRect(108, 52, 36, 16));
  text_layer_set_font(s_temp4hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_temp4hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_temp4hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_temp4hours_layer, color_hours_grafico);
  text_layer_set_text(s_temp4hours_layer, data.temp4);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_temp4hours_layer));
  
  
  //grafico
  //max
  s_tempmaxgraph_layer = text_layer_create(GRect(-4, 95, 16, 16));
  text_layer_set_font(s_tempmaxgraph_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_tempmaxgraph_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_tempmaxgraph_layer, color_hours_fondo);
  text_layer_set_text_color(s_tempmaxgraph_layer, color_hours_texto);
  text_layer_set_text(s_tempmaxgraph_layer, data.tempsmax);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_tempmaxgraph_layer));
  //min
  s_tempmingraph_layer = text_layer_create(GRect(-4, 126, 16, 16));
  text_layer_set_font(s_tempmingraph_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_tempmingraph_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_tempmingraph_layer, color_hours_fondo);
  text_layer_set_text_color(s_tempmingraph_layer, color_hours_texto);
  text_layer_set_text(s_tempmingraph_layer, data.tempsmin);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_tempmingraph_layer));
  //etiqueta1
  s_etiqueta1graph_layer = text_layer_create(GRect(11, 138, 16, 16));
  text_layer_set_font(s_etiqueta1graph_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_etiqueta1graph_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_etiqueta1graph_layer, color_hours_fondo);
  text_layer_set_text_color(s_etiqueta1graph_layer, color_hours_texto);
  text_layer_set_text(s_etiqueta1graph_layer, data.etiquetas[0]);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_etiqueta1graph_layer));
  //etiqueta2
  s_etiqueta2graph_layer = text_layer_create(GRect(70, 138, 16, 16));
  text_layer_set_font(s_etiqueta2graph_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_etiqueta2graph_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_etiqueta2graph_layer, color_hours_fondo);
  text_layer_set_text_color(s_etiqueta2graph_layer, color_hours_texto);
  text_layer_set_text(s_etiqueta2graph_layer, data.etiquetas[1]);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_etiqueta2graph_layer));
  //etiqueta3
  s_etiqueta3graph_layer = text_layer_create(GRect(130, 138, 16, 16));
  text_layer_set_font(s_etiqueta3graph_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_etiqueta3graph_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_etiqueta3graph_layer, color_hours_fondo);
  text_layer_set_text_color(s_etiqueta3graph_layer, color_hours_texto);
  text_layer_set_text(s_etiqueta3graph_layer, data.etiquetas[2]);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_etiqueta3graph_layer));
  
  
  //Viento
  //1
  s_viento1hours_layer = text_layer_create(GRect(0, 68, 36, 16));
  text_layer_set_font(s_viento1hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_viento1hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_viento1hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_viento1hours_layer, color_hours_viento);
  text_layer_set_text(s_viento1hours_layer, data.viento1);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_viento1hours_layer));
  //2
  s_viento2hours_layer = text_layer_create(GRect(36, 68, 36, 16));
  text_layer_set_font(s_viento2hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_viento2hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_viento2hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_viento2hours_layer, color_hours_viento);
  text_layer_set_text(s_viento2hours_layer, data.viento2);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_viento2hours_layer));
  //3
  s_viento3hours_layer = text_layer_create(GRect(72, 68, 36, 16));
  text_layer_set_font(s_viento3hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_viento3hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_viento3hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_viento3hours_layer, color_hours_viento);
  text_layer_set_text(s_viento3hours_layer, data.viento3);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_viento3hours_layer));
  //4
  s_viento4hours_layer = text_layer_create(GRect(108, 68, 36, 16));
  text_layer_set_font(s_viento4hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_viento4hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_viento4hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_viento4hours_layer, color_hours_viento);
  text_layer_set_text(s_viento4hours_layer, data.viento4);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_viento4hours_layer));
  
  //Lluvia
  //1
  s_lluvia1hours_layer = text_layer_create(GRect(0, 84, 36, 16));
  text_layer_set_font(s_lluvia1hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_lluvia1hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvia1hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_lluvia1hours_layer, color_hours_texto);
  text_layer_set_text(s_lluvia1hours_layer, data.lluvia1);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_lluvia1hours_layer));
  //2
  s_lluvia2hours_layer = text_layer_create(GRect(36, 84, 36, 16));
  text_layer_set_font(s_lluvia2hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_lluvia2hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvia2hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_lluvia2hours_layer, color_hours_texto);
  text_layer_set_text(s_lluvia2hours_layer, data.lluvia2);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_lluvia2hours_layer));
  //3
  s_lluvia3hours_layer = text_layer_create(GRect(72, 84, 36, 16));
  text_layer_set_font(s_lluvia3hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_lluvia3hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvia3hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_lluvia3hours_layer, color_hours_texto);
  text_layer_set_text(s_lluvia3hours_layer, data.lluvia3);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_lluvia3hours_layer));
  //4
  s_lluvia4hours_layer = text_layer_create(GRect(108, 84, 36, 16));
  text_layer_set_font(s_lluvia4hours_layer, s_smallhours_font);
  text_layer_set_text_alignment(s_lluvia4hours_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvia4hours_layer, color_hours_fondo);
  text_layer_set_text_color(s_lluvia4hours_layer, color_hours_texto);
  text_layer_set_text(s_lluvia4hours_layer, data.lluvia4);
  layer_add_child(s_hours_layer, text_layer_get_layer(s_lluvia4hours_layer));
  
  //grafico
  GRect bounds = GRect(0,100,144,52);
  s_path_layer = layer_create(bounds);
  layer_set_update_proc(s_path_layer, path_layer_update_callback);
  layer_add_child(s_hours_layer, s_path_layer);
  
  layer_mark_dirty(s_path_layer);  
}

void unload_hours_layer(void){
  //grafico
  layer_destroy(s_path_layer);
  text_layer_destroy(s_tempmaxgraph_layer);
  text_layer_destroy(s_tempmingraph_layer);
  text_layer_destroy(s_etiqueta1graph_layer);
  text_layer_destroy(s_etiqueta2graph_layer);
  text_layer_destroy(s_etiqueta3graph_layer);
//  gpath_destroy(s_bordes_path);
  //viento
  text_layer_destroy(s_viento1hours_layer);
  text_layer_destroy(s_viento2hours_layer);
  text_layer_destroy(s_viento3hours_layer);
  text_layer_destroy(s_viento4hours_layer);
  //lluvia
  text_layer_destroy(s_lluvia1hours_layer);
  text_layer_destroy(s_lluvia2hours_layer);
  text_layer_destroy(s_lluvia3hours_layer);
  text_layer_destroy(s_lluvia4hours_layer);
  //temp
  text_layer_destroy(s_temp1hours_layer);
  text_layer_destroy(s_temp2hours_layer);
  text_layer_destroy(s_temp3hours_layer);
  text_layer_destroy(s_temp4hours_layer);
  //iconos
  gbitmap_destroy(s_icon1hours_bitmap);
  bitmap_layer_destroy(s_icon1hours_layer);
  gbitmap_destroy(s_icon2hours_bitmap);
  bitmap_layer_destroy(s_icon2hours_layer);
  gbitmap_destroy(s_icon3hours_bitmap);
  bitmap_layer_destroy(s_icon3hours_layer);
  gbitmap_destroy(s_icon4hours_bitmap);
  bitmap_layer_destroy(s_icon4hours_layer);
  //cabecera
  text_layer_destroy(s_cabecera1hours_layer);
  text_layer_destroy(s_cabecera2hours_layer);
  text_layer_destroy(s_cabecera3hours_layer);
  text_layer_destroy(s_cabecera4hours_layer);
  //capa general
  layer_destroy(s_hours_layer);
}