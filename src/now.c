#include <pebble.h>
#include "now.h"

static Layer *s_now_layer;

static GFont s_smallnow_font;

GColor color_now_fondo;
GColor color_now_texto;
GColor color_now_max;
GColor color_now_min;


static TextLayer *s_tempnow_layer;
static TextLayer *s_tempmaxnow_layer;
static TextLayer *s_tempminnow_layer;
static TextLayer *s_lluvianow_layer;
static TextLayer *s_stermnow_layer;
static TextLayer *s_vientonow_layer;
static TextLayer *s_presionnow_layer;
static TextLayer *s_sunrisenow_layer;
static TextLayer *s_sunsetnow_layer;
static TextLayer *s_moonrisenow_layer;
static TextLayer *s_moonsetnow_layer;

static BitmapLayer *s_tempiconnow_layer;
static GBitmap *s_tempiconnow_bitmap;
static BitmapLayer *s_lluviaiconnow_layer;
static GBitmap *s_lluviaiconnow_bitmap;
static BitmapLayer *s_stermiconnow_layer;
static GBitmap *s_stermiconnow_bitmap;
static BitmapLayer *s_vientoiconnow_layer;
static GBitmap *s_vientoiconnow_bitmap;
static BitmapLayer *s_presioniconnow_layer;
static GBitmap *s_presioniconnow_bitmap;
static BitmapLayer *s_sunrisesetnow_layer;
static GBitmap *s_sunriseseticonnow_bitmap;
static BitmapLayer *s_moonphasenow_layer;
static GBitmap *s_moonphaseiconnow_bitmap;

struct data_now{
  char temp_now[6];
  char tempicon[4];
  char tempmax[6];
  char tempmin[6];
  char lluvia[8];
  char sterm[7];
  char viento[10];
  char vientoicon[4];
  char presion[8];
  char sunrise[6];
  char sunset[6];
  char moonrise[6];
  char moonset[6];
  int moonphase;
};

struct data_now data;
/************************************************************************/

void get_data_now(){
  if(persist_exists(1)){
    persist_read_string(1, data.temp_now, sizeof(data.temp_now));
    persist_read_string(2, data.tempicon, sizeof(data.tempicon));
    persist_read_string(3, data.tempmax, sizeof(data.tempmax));
    persist_read_string(4, data.tempmin, sizeof(data.tempmin));
    persist_read_string(5, data.lluvia, sizeof(data.lluvia));
    persist_read_string(6, data.sterm, sizeof(data.sterm));
    persist_read_string(7, data.viento, sizeof(data.viento));
    persist_read_string(8, data.vientoicon, sizeof(data.vientoicon));
    persist_read_string(9, data.presion, sizeof(data.presion));
    persist_read_string(10, data.sunrise, sizeof(data.sunrise));
    persist_read_string(11, data.sunset, sizeof(data.sunset));
    data.moonphase = persist_read_int(12);
    persist_read_string(13, data.moonrise, sizeof(data.moonrise));
    persist_read_string(14, data.moonset, sizeof(data.moonset));
  }
}
/************************************************************************/

void load_now_layer(Window *window){
  //datos
  get_data_now();
  
  //capa general
  s_now_layer = layer_create(GRect(0,16,144,152));
  layer_add_child(window_get_root_layer(window),s_now_layer);
  //fuente
  s_smallnow_font = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  //colores
  #ifdef PBL_BW
    color_now_fondo = GColorBlack;
    color_now_texto = GColorWhite;
    color_now_max = GColorWhite;
    color_now_min = GColorWhite;
  #else
    color_now_fondo = GColorWhite;
    color_now_texto = GColorBlack;
    color_now_max = GColorRed;
    color_now_min = GColorBlue;
  #endif
  
  //Temperaturas
  //now
  s_tempnow_layer = text_layer_create(GRect(50, -4, 68, 48));
  text_layer_set_font(s_tempnow_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  text_layer_set_text_alignment(s_tempnow_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_tempnow_layer, color_now_fondo);
  text_layer_set_text_color(s_tempnow_layer, color_now_texto);
  text_layer_set_text(s_tempnow_layer, data.temp_now);
  layer_add_child(s_now_layer, text_layer_get_layer(s_tempnow_layer));
  //max
  s_tempmaxnow_layer = text_layer_create(GRect(118, 5, 25, 16));
  text_layer_set_font(s_tempmaxnow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_tempmaxnow_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_tempmaxnow_layer, color_now_fondo);
  text_layer_set_text_color(s_tempmaxnow_layer, color_now_max);
  text_layer_set_text(s_tempmaxnow_layer, data.tempmax);
  layer_add_child(s_now_layer, text_layer_get_layer(s_tempmaxnow_layer));
  //min
  s_tempminnow_layer = text_layer_create(GRect(118, 25, 25, 16));
  text_layer_set_font(s_tempminnow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_tempminnow_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_tempminnow_layer, color_now_fondo);
  text_layer_set_text_color(s_tempminnow_layer, color_now_min);
  text_layer_set_text(s_tempminnow_layer, data.tempmin);
  layer_add_child(s_now_layer, text_layer_get_layer(s_tempminnow_layer));
  //icono
  s_tempiconnow_layer = bitmap_layer_create(GRect(2,0,48,48));
  bitmap_layer_set_compositing_mode(s_tempiconnow_layer, GCompOpSet);
  //s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_CLEAR);
  s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_CLEAR);
  if(strcmp(data.tempicon,"cle")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_CLEAR);
  }else if(strcmp(data.tempicon,"clo")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_CLOUDY);
  }else if(strcmp(data.tempicon,"flu")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_FLURRIES);
  }else if(strcmp(data.tempicon,"fog")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_FOG);
  }else if(strcmp(data.tempicon,"hzy")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_HAZY);
  }else if(strcmp(data.tempicon,"mcl")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_MOSTLYCLOUDY);
  }else if(strcmp(data.tempicon,"msu")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_MOSTLYCLEAR);
  }else if(strcmp(data.tempicon,"rai")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_RAIN);
  }else if(strcmp(data.tempicon,"snw")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_SNOW);
  }else if(strcmp(data.tempicon,"str")==0){
    gbitmap_destroy(s_tempiconnow_bitmap);
    s_tempiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOW_STORM);
  }
  bitmap_layer_set_bitmap(s_tempiconnow_layer, s_tempiconnow_bitmap);
  layer_add_child(s_now_layer, bitmap_layer_get_layer(s_tempiconnow_layer));
  
  //lluvia
  s_lluvianow_layer = text_layer_create(GRect(21, 60, 49, 16));
  text_layer_set_font(s_lluvianow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_lluvianow_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_lluvianow_layer, color_now_fondo);
  text_layer_set_text_color(s_lluvianow_layer, color_now_texto);
  text_layer_set_text(s_lluvianow_layer, data.lluvia);
  layer_add_child(s_now_layer, text_layer_get_layer(s_lluvianow_layer));
  //icono
  s_lluviaiconnow_layer = bitmap_layer_create(GRect(5,60,16,16));
  bitmap_layer_set_compositing_mode(s_lluviaiconnow_layer, GCompOpSet);
  s_lluviaiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LLUVIA16);
  bitmap_layer_set_bitmap(s_lluviaiconnow_layer, s_lluviaiconnow_bitmap);
  layer_add_child(s_now_layer, bitmap_layer_get_layer(s_lluviaiconnow_layer));
  
  //sens termica
  s_stermnow_layer = text_layer_create(GRect(90, 60, 49, 16));
  text_layer_set_font(s_stermnow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_stermnow_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_stermnow_layer, color_now_fondo);
  text_layer_set_text_color(s_stermnow_layer, color_now_texto);
  text_layer_set_text(s_stermnow_layer, data.sterm);
  layer_add_child(s_now_layer, text_layer_get_layer(s_stermnow_layer));
  //icono
  s_stermiconnow_layer = bitmap_layer_create(GRect(74,60,16,16));
  bitmap_layer_set_compositing_mode(s_stermiconnow_layer, GCompOpSet);
  s_stermiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_STERM16);
  bitmap_layer_set_bitmap(s_stermiconnow_layer, s_stermiconnow_bitmap);
  layer_add_child(s_now_layer, bitmap_layer_get_layer(s_stermiconnow_layer));
  
  //viento
  s_vientonow_layer = text_layer_create(GRect(21, 80, 49, 16));
  text_layer_set_font(s_vientonow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_vientonow_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_vientonow_layer, color_now_fondo);
  text_layer_set_text_color(s_vientonow_layer, color_now_texto);
  text_layer_set_text(s_vientonow_layer, data.viento);
  layer_add_child(s_now_layer, text_layer_get_layer(s_vientonow_layer));
  //icono
  s_vientoiconnow_layer = bitmap_layer_create(GRect(5,80,16,16));
  bitmap_layer_set_compositing_mode(s_vientoiconnow_layer, GCompOpSet);
  s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_VAR);
  if(strcmp(data.vientoicon,"N")==0){
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_N);
  }else if(strcmp(data.vientoicon,"NE")==0){
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_NE);
  }else if(strcmp(data.vientoicon,"E")==0){
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_E);
  }else if(strcmp(data.vientoicon,"SE")==0){
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_SE);
  }else if(strcmp(data.vientoicon,"S")==0){
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_S);
  }else if(strcmp(data.vientoicon,"SW")==0){
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_SW);
  }else if(strcmp(data.vientoicon,"W")==0){
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_W);
  }else if(strcmp(data.vientoicon,"NW")==0){
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_NW);
  }else{
    gbitmap_destroy(s_vientoiconnow_bitmap);
    s_vientoiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIENTO_VAR);
  }
  bitmap_layer_set_bitmap(s_vientoiconnow_layer, s_vientoiconnow_bitmap);
  layer_add_child(s_now_layer, bitmap_layer_get_layer(s_vientoiconnow_layer));
  
  //presion
  s_presionnow_layer = text_layer_create(GRect(90, 80, 49, 16));
  text_layer_set_font(s_presionnow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_presionnow_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_presionnow_layer, color_now_fondo);
  text_layer_set_text_color(s_presionnow_layer, color_now_texto);
  text_layer_set_text(s_presionnow_layer, data.presion);
  layer_add_child(s_now_layer, text_layer_get_layer(s_presionnow_layer));
  //icono
  s_presioniconnow_layer = bitmap_layer_create(GRect(74,80,16,16));
  bitmap_layer_set_compositing_mode(s_presioniconnow_layer, GCompOpSet);
  s_presioniconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PRESION16);
  bitmap_layer_set_bitmap(s_presioniconnow_layer, s_presioniconnow_bitmap);
  layer_add_child(s_now_layer, bitmap_layer_get_layer(s_presioniconnow_layer));
  
  //sunrise
  s_sunrisenow_layer = text_layer_create(GRect(41, 108, 27, 16));
  text_layer_set_font(s_sunrisenow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_sunrisenow_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_sunrisenow_layer, color_now_fondo);
  text_layer_set_text_color(s_sunrisenow_layer, color_now_texto);
  text_layer_set_text(s_sunrisenow_layer, data.sunrise);
  layer_add_child(s_now_layer, text_layer_get_layer(s_sunrisenow_layer));
  //sunset
  s_sunsetnow_layer = text_layer_create(GRect(41, 124, 27, 16));
  text_layer_set_font(s_sunsetnow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_sunsetnow_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_sunsetnow_layer, color_now_fondo);
  text_layer_set_text_color(s_sunsetnow_layer, color_now_texto);
  text_layer_set_text(s_sunsetnow_layer, data.sunset);
  layer_add_child(s_now_layer, text_layer_get_layer(s_sunsetnow_layer));
  //icono
  s_sunrisesetnow_layer = bitmap_layer_create(GRect(9,108,32,32));
  bitmap_layer_set_compositing_mode(s_sunrisesetnow_layer, GCompOpSet);
  s_sunriseseticonnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SUNRISESET);
  bitmap_layer_set_bitmap(s_sunrisesetnow_layer, s_sunriseseticonnow_bitmap);
  layer_add_child(s_now_layer, bitmap_layer_get_layer(s_sunrisesetnow_layer));
  
  //moonrise
  s_moonrisenow_layer = text_layer_create(GRect(108, 108, 27, 16));
  text_layer_set_font(s_moonrisenow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_moonrisenow_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_moonrisenow_layer, color_now_fondo);
  text_layer_set_text_color(s_moonrisenow_layer, color_now_texto);
  text_layer_set_text(s_moonrisenow_layer, data.moonrise);
  layer_add_child(s_now_layer, text_layer_get_layer(s_moonrisenow_layer));
  //moonset
  s_moonsetnow_layer = text_layer_create(GRect(108, 124, 27, 16));
  text_layer_set_font(s_moonsetnow_layer, s_smallnow_font);
  text_layer_set_text_alignment(s_moonsetnow_layer, GTextAlignmentRight);
  text_layer_set_background_color(s_moonsetnow_layer, color_now_fondo);
  text_layer_set_text_color(s_moonsetnow_layer, color_now_texto);
  text_layer_set_text(s_moonsetnow_layer, data.moonset);
  layer_add_child(s_now_layer, text_layer_get_layer(s_moonsetnow_layer));
  //icono
  s_moonphasenow_layer = bitmap_layer_create(GRect(76,108,32,32));
  bitmap_layer_set_compositing_mode(s_moonphasenow_layer, GCompOpSet);
  s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_NUEVA);
  switch(data.moonphase){
    case 0:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_NUEVA);
    break;
    case 1:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C1);
    break;
    case 2:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C2);
    break;
    case 3:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C3);
    break;
    case 4:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C4);
    break;
    case 5:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C5);
    break;
    case 6:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C6);
    break;
    case 7:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C7);
    break;
    case 8:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_LLENA);
    break;
    case 9:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D1);
    break;
    case 10:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D2);
    break;
    case 11:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D3);
    break;
    case 12:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D4);
    break;
    case 13:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D5);
    break;
    case 14:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D6);
    break;
    case 15:
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D7);
    break;
  }
  /*
  if(strcmp(data.moonphase,"NU")==0){
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_NUEVA);
  }else if(strcmp(data.moonphase,"C1")==0){
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C1);
  }else if(strcmp(data.moonphase,"C2")==0){
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C2);
  }else if(strcmp(data.moonphase,"C3")==0){
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_C3);
  }else if(strcmp(data.moonphase,"LL")==0){
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_LLENA);
  }else if(strcmp(data.moonphase,"D1")==0){
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D1);
  }else if(strcmp(data.moonphase,"D2")==0){
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D2);
  }else if(strcmp(data.moonphase,"D3")==0){
    gbitmap_destroy(s_moonphaseiconnow_bitmap);
    s_moonphaseiconnow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUNA_D3);
  }
  */
  bitmap_layer_set_bitmap(s_moonphasenow_layer, s_moonphaseiconnow_bitmap);
  layer_add_child(s_now_layer, bitmap_layer_get_layer(s_moonphasenow_layer));
 
}

void unload_now_layer(void){
  //sunmoon
  gbitmap_destroy(s_moonphaseiconnow_bitmap);
  bitmap_layer_destroy(s_moonphasenow_layer);
  text_layer_destroy(s_moonsetnow_layer);
  text_layer_destroy(s_moonrisenow_layer);
  gbitmap_destroy(s_sunriseseticonnow_bitmap);
  bitmap_layer_destroy(s_sunrisesetnow_layer);
  text_layer_destroy(s_sunrisenow_layer);
  text_layer_destroy(s_sunsetnow_layer);
  //presion
  gbitmap_destroy(s_presioniconnow_bitmap);
  bitmap_layer_destroy(s_presioniconnow_layer);
  text_layer_destroy(s_presionnow_layer);
  //viento
  gbitmap_destroy(s_vientoiconnow_bitmap);
  bitmap_layer_destroy(s_vientoiconnow_layer);
  text_layer_destroy(s_vientonow_layer);
  //sensaciontermica
  gbitmap_destroy(s_stermiconnow_bitmap);
  bitmap_layer_destroy(s_stermiconnow_layer);
  text_layer_destroy(s_stermnow_layer);
  //lluvia
  gbitmap_destroy(s_lluviaiconnow_bitmap);
  bitmap_layer_destroy(s_lluviaiconnow_layer);
  text_layer_destroy(s_lluvianow_layer);
  //temps
  gbitmap_destroy(s_tempiconnow_bitmap);
  bitmap_layer_destroy(s_tempiconnow_layer);
  text_layer_destroy(s_tempminnow_layer);
  text_layer_destroy(s_tempmaxnow_layer);
  text_layer_destroy(s_tempnow_layer);
  
  layer_destroy(s_now_layer);
}