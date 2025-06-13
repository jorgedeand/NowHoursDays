#include <pebble.h>
#include "statusbarclock.h"
#include "now.h"
#include "hours.h"
#include "days.h"
  
static Window *s_main_window;
static u_short s_current_screen = 0;

static TextLayer *s_logo_layer;
GColor color_logo_fondo;
GColor color_logo_texto;

GColor color_fondo;

/************************************************************************/
void ocultar_logo(void* logo){
  BitmapLayer* logo_layer = (BitmapLayer*) logo;
  layer_set_hidden(bitmap_layer_get_layer(logo_layer), true);
}
/************************************************************************/
//AppMessage

//Send message from pebble to JS
void send_message(int comando){
  DictionaryIterator *iter;
	app_message_outbox_begin(&iter);
	dict_write_uint8(iter, 0, comando);//0 recepcion de comando
	dict_write_end(iter);
  app_message_outbox_send();  
}

// Called when a message is received from PebbleKitJS
static void in_received_handler(DictionaryIterator *received, void *context) {
  Tuple *tuple = dict_read_first(received);
  while(tuple){
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "%d:datos int: %d ",(int)tuple->key, (int)tuple->value->int32);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "%d:datos string: %s \n",(int)tuple->key, tuple->value->cstring);
    if(((tuple->key > 60)&&(tuple->key < 106))||(tuple->key == 12)){
      persist_write_int(tuple->key, (int)tuple->value->int32);
    }else{
      persist_write_string(tuple->key, tuple->value->cstring);
    }
    tuple = dict_read_next(received);
  }
  //recarga la pagina en la que se este
  if(s_current_screen == 0){
    unload_now_layer();
    load_now_layer(s_main_window);
  }else if(s_current_screen == 1){
    unload_hours_layer();
    load_hours_layer(s_main_window);
  }else{
    unload_days_layer();
    load_days_layer(s_main_window);
  }
  //oculta icono de actualizacion
  set_updatests(0);
}

// Called when an incoming message from PebbleKitJS is dropped
static void in_dropped_handler(AppMessageResult reason, void *context) {	
  APP_LOG(APP_LOG_LEVEL_DEBUG, "dropped:%d:",reason);
  set_updatests(2);
  /*
  static char reasonStr[20];
  switch(reason){
    case APP_MSG_OK:
      snprintf(reasonStr,20,"%s","APP_MSG_OK");
    break;
    case APP_MSG_SEND_TIMEOUT:
      snprintf(reasonStr,20,"%s","SEND TIMEOUT");
    break;
    case APP_MSG_SEND_REJECTED:
      snprintf(reasonStr,20,"%s","SEND REJECTED");
    break;
    case APP_MSG_NOT_CONNECTED:
      snprintf(reasonStr,20,"%s","NOT CONNECTED");
    break;
    case APP_MSG_APP_NOT_RUNNING:
      snprintf(reasonStr,20,"%s","NOT RUNNING");
    break;
    case APP_MSG_INVALID_ARGS:
      snprintf(reasonStr,20,"%s","INVALID ARGS");
    break;
    case APP_MSG_BUSY:
      snprintf(reasonStr,20,"%s","BUSY");
    break;
    case APP_MSG_BUFFER_OVERFLOW:
      snprintf(reasonStr,20,"%s","BUFFER OVERFLOW");
    break;
    case APP_MSG_ALREADY_RELEASED:
      snprintf(reasonStr,20,"%s","ALRDY RELEASED");
    break;
    case APP_MSG_CALLBACK_ALREADY_REGISTERED:
      snprintf(reasonStr,20,"%s","CLB ALR REG");
    break;
    case APP_MSG_CALLBACK_NOT_REGISTERED:
      snprintf(reasonStr,20,"%s","CLB NOT REG");
    break;
    case APP_MSG_OUT_OF_MEMORY:
      snprintf(reasonStr,20,"%s","OUT OF MEM");
    break;
    default:
    snprintf(reasonStr,20,"%s","OTRO YA");
    break;
  }
  APP_LOG(APP_LOG_LEVEL_DEBUG, "droppedStr:%s:",reasonStr);
  */
}

// Called when PebbleKitJS does not acknowledge receipt of a message
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "failed %d",reason);
  set_updatests(2);
}

/************************************************************************/
//Handlers
//Time
static void tick_handler(struct tm *tick_time,TimeUnits units_changed){
  //time change
  if(units_changed&MINUTE_UNIT){
    update_statusbar_time();
  }
  if(units_changed&HOUR_UNIT){
    send_message(0);
  }
}

//BT
static void bt_handler(bool connected){
  update_bt_status(connected,false);
}
static void battery_handler(BatteryChargeState charge){
  update_battery_status(charge);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(s_current_screen == 0){ //now
    unload_now_layer();
    load_days_layer(s_main_window);
    s_current_screen = 2;
    text_layer_set_text(s_logo_layer, "\n\ndays");
  }else if(s_current_screen==1){ //hours
    unload_hours_layer();
    load_now_layer(s_main_window);
    s_current_screen = 0;
    text_layer_set_text(s_logo_layer, "now\n\n");
  }else{ //days
    unload_days_layer();
    load_hours_layer(s_main_window);
    s_current_screen = 1;
    text_layer_set_text(s_logo_layer, "\nhours\n");
  }
  layer_set_hidden(text_layer_get_layer(s_logo_layer), S_FALSE);
  layer_add_child(window_get_root_layer(s_main_window),text_layer_get_layer(s_logo_layer));
  app_timer_register(400, &ocultar_logo, (void*)s_logo_layer);
}
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //send_message(0);
}
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(s_current_screen == 0){ //now
    unload_now_layer();
    load_hours_layer(s_main_window);
    s_current_screen = 1;
    text_layer_set_text(s_logo_layer, "\nhours\n");
  }else if(s_current_screen==1){ //hours
    unload_hours_layer();
    load_days_layer(s_main_window);
    s_current_screen = 2;
    text_layer_set_text(s_logo_layer, "\n\ndays");
  }else{ //days
    unload_days_layer();
    load_now_layer(s_main_window);
    s_current_screen = 0;
    text_layer_set_text(s_logo_layer, "now\n\n");
  }
  layer_set_hidden(text_layer_get_layer(s_logo_layer), S_FALSE);
  layer_add_child(window_get_root_layer(s_main_window),text_layer_get_layer(s_logo_layer));
  app_timer_register(400, &ocultar_logo, (void*)s_logo_layer);
}
static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

/************************************************************************/
//Start
static void main_window_load(Window *window){ 
  load_statusbar_layer(s_main_window);
  load_now_layer(s_main_window);
  
  #ifdef PBL_BW
    color_logo_fondo = GColorBlack;
    color_logo_texto = GColorWhite;
  #else
    color_logo_fondo = GColorWhite;
    color_logo_texto = GColorBlack;
  #endif
  
  //pantalla presentacion
  s_logo_layer = text_layer_create(GRect(0, 0 , 144, 168));
  text_layer_set_background_color(s_logo_layer, color_logo_fondo);
  text_layer_set_text_color(s_logo_layer, color_logo_texto);
  text_layer_set_text_alignment(s_logo_layer, GTextAlignmentCenter);
  text_layer_set_font(s_logo_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));//(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text(s_logo_layer, "now\nhours\ndays");
  layer_add_child(window_get_root_layer(window),text_layer_get_layer(s_logo_layer));
  app_timer_register(600, &ocultar_logo, (void*)s_logo_layer);
  
  /*
  //inverter layer
  s_inverter_layer = inverter_layer_create(GRect(0,0,144,168));
  layer_set_hidden(inverter_layer_get_layer(s_inverter_layer), true);
  layer_add_child(window_get_root_layer(window), inverter_layer_get_layer(s_inverter_layer)); 
  */
}

static void main_window_unload(Window *window){
  if(s_current_screen == 0){ //now
    unload_now_layer();
  }else if(s_current_screen==1){ //hours
    unload_hours_layer();
  }else{ //days
    unload_days_layer();
  }
  
  unload_statusbar_layer();
  text_layer_destroy(s_logo_layer);
  
  //destroy inverter layer
  //inverter_layer_destroy(s_inverter_layer); 
}

/************************************************************************/

static void init(){
  //Create main window element and assign to pointer
  s_main_window = window_create();
  
  //Set handlers to manage the elements inside the window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
                                .load = main_window_load,
                                .unload = main_window_unload
                              });
  //fullscreen window
  #ifdef PBL_BW
//    window_set_fullscreen(s_main_window, true);
  #endif
  //background
  #ifdef PBL_BW
    color_fondo = GColorBlack;
  #else
    color_fondo = GColorWhite;
  #endif
  window_set_background_color(s_main_window, color_fondo);
  //click provider
  window_set_click_config_provider(s_main_window, click_config_provider);
  //Show window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  //Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  //Register with BluetoothConnectionService
  bluetooth_connection_service_subscribe(bt_handler);
  //Register with BatteryStateService
  battery_state_service_subscribe(battery_handler);
  // Register callbacks for AppMessage
  app_message_register_inbox_received(in_received_handler); 
	app_message_register_inbox_dropped(in_dropped_handler); 
	app_message_register_outbox_failed(out_failed_handler);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
}


static void deinit(){
  //appmessage
  app_message_deregister_callbacks();
  
  //unsuscribe from services
  tick_timer_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
  battery_state_service_unsubscribe();
  
  //Destroy window
  window_destroy(s_main_window);
}

/************************************************************************/
  
int main(void){
  init();
  app_event_loop();
  deinit();
}