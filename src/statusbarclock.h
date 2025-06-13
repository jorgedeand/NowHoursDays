#pragma once

void update_bt_status(bool connected, bool start);
void set_updatests(int sts);
void update_statusbar_time();
void update_battery_status(BatteryChargeState charge);

void load_statusbar_layer(Window *window);
void unload_statusbar_layer(void);