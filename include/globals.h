#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "display.h"
#include "OneButton.h"
#include "Encoder.h"

#include "outlet.h"
#include "fervo.h"
#include "menus/settings.h"
#include "menus/flood.h"
#include "DS1338.h"

extern I2CLCD lcd;

extern struct rtctime_t rtc_time;

extern OneButton btn_flood_stop;
extern OneButton btn_next;
extern OneButton btn_setup;
extern OneButton btn_prev;

extern Encoder enc;

extern Outlet *outlets[N_OUTLETS];
extern Fervo servo;

extern SettingsMenu settings_menu;
extern FloodMenu flood_menu;


#endif