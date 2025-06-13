#include <pebble.h>
#include "statusbarclock.h"

static Layer *s_statusbar_layer;
static GFont s_statusbar_font;

//bt
static BitmapLayer *s_btdis_layer;
static GBitmap *s_btdis_bitmap;
//update status
static BitmapLayer *s_updatests_layer;
static GBitmap *s_updatests_bitmap;
//hora
static TextLayer *s_time_layer;
static char time_text[6] = "00:00";
//bateria
static TextLayer *s_battery_layer;
static char battery_text[5] = "000%";

GColor color_sts_texto;
GColor color_sts_fondo;


/***********************************************************************************/
/*
Layer * get_statusbar_layer(){
  return s_statusbar_layer;
}
*/

void update_bt_status(bool connected, bool start){
  if(connected){
    //when bt connected, vibe and change bt status bitmap
    if(!start){
      vibes_double_pulse();
    }
    layer_set_hidden(bitmap_layer_get_layer(s_btdis_layer), true);
  }else{
    //when bt disconnected, vibe and change bt status bitmap
    if(!start){
      vibes_long_pulse();
    }
    layer_set_hidden(bitmap_layer_get_layer(s_btdis_layer), false);
  }
}

void set_updatests(int sts){
  if(sts == 0){
    //updated
    //gbitmap_destroy(s_updatests_bitmap);
    //s_updatests_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_UPDATED12);
    layer_set_hidden(bitmap_layer_get_layer(s_updatests_layer), S_TRUE);
  }else if(sts == 1){
    //updating
    gbitmap_destroy(s_updatests_bitmap);
    s_updatests_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_UPDATING12);
    layer_set_hidden(bitmap_layer_get_layer(s_updatests_layer), S_FALSE);
  }else{
    //needs update
    gbitmap_destroy(s_updatests_bitmap);
    s_updatests_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NOTUPDATED12);
    layer_set_hidden(bitmap_layer_get_layer(s_updatests_layer), S_FALSE);
  }
}

void update_statusbar_time(){
  //Get a tm struct
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  //Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true){
    //use 24h format
    strftime(time_text,sizeof(time_text), "%H:%M", tick_time);
  }else{
    //use 12h format
    strftime(time_text,sizeof(time_text), "%I:%M", tick_time);
  }

  //Display this time on the TextLayer
  text_layer_set_text(s_time_layer, time_text);
}

void update_battery_status(BatteryChargeState charge){
  //update battery layer
  snprintf(battery_text,sizeof(battery_text),"%d",charge.charge_percent);
  strncat(battery_text,"%",1);
  if(charge.charge_percent < 50){
    layer_set_hidden((Layer *)s_battery_layer, S_FALSE);
  }else{
    layer_set_hidden((Layer *)s_battery_layer, S_TRUE);
  }
  text_layer_set_text(s_battery_layer, battery_text);
  
}



/***********************************************************************************/
void load_statusbar_layer(Window *window) {
  //statusbar layer
  s_statusbar_layer = layer_create(GRect(0,0,144,16));
  layer_add_child(window_get_root_layer(window),s_statusbar_layer);
  
  //font
  s_statusbar_font = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  
  #ifdef PBL_BW
    color_sts_texto = GColorWhite;
    color_sts_fondo = GColorWhite;
  #else
    color_sts_texto = GColorBlack;
    color_sts_fondo = GColorWhite;
  #endif
  
  //disconnected icon
  s_btdis_layer = bitmap_layer_create(GRect(3,0,8,12));
  bitmap_layer_set_compositing_mode(s_btdis_layer, GCompOpSet);
  s_btdis_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_DIS);
  bitmap_layer_set_bitmap(s_btdis_layer, s_btdis_bitmap);
  layer_add_child(s_statusbar_layer, bitmap_layer_get_layer(s_btdis_layer));
  //show bt status from the start
  update_bt_status(bluetooth_connection_service_peek(),true);
  
  //update status
  s_updatests_layer = bitmap_layer_create(GRect(19,0,12,12));
  bitmap_layer_set_compositing_mode(s_updatests_layer, GCompOpSet);
  s_updatests_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_UPDATING12);
  bitmap_layer_set_bitmap(s_updatests_layer, s_updatests_bitmap);
  layer_add_child(s_statusbar_layer, bitmap_layer_get_layer(s_updatests_layer));
  
  //Time layer
  s_time_layer = text_layer_create(GRect(59, -1, 27, 15));
  text_layer_set_background_color(s_time_layer, color_sts_fondo);
  text_layer_set_text_color(s_time_layer, color_sts_texto);
  text_layer_set_font(s_time_layer, s_statusbar_font);
  layer_add_child(s_statusbar_layer,text_layer_get_layer(s_time_layer));
  //show time
  update_statusbar_time();
  
  //Battery icon
  s_battery_layer = text_layer_create(GRect(108,-3,33,16));
  text_layer_set_background_color(s_battery_layer, color_sts_fondo);
  text_layer_set_text_color(s_battery_layer, color_sts_texto);
  text_layer_set_text_alignment(s_battery_layer, GTextAlignmentRight);
  text_layer_set_font(s_battery_layer, s_statusbar_font);
  layer_add_child(s_statusbar_layer, text_layer_get_layer(s_battery_layer));
  //set battery status from start
  update_battery_status(battery_state_service_peek());
}

void unload_statusbar_layer(void) {
  //destroy bt icon
  gbitmap_destroy(s_btdis_bitmap);
  bitmap_layer_destroy(s_btdis_layer);
  
  //destroy updatests
  gbitmap_destroy(s_updatests_bitmap);
  bitmap_layer_destroy(s_updatests_layer);

  //Destroy text layer
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_battery_layer);
  
  layer_destroy(s_statusbar_layer); 
}