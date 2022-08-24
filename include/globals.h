#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <DHT.h>
#include <OneButton.h>
#include <Encoder.h>
#include <DS1338.h>

#include "display.h"
#include "outlet.h"
#include "fervo.h"
#include "pump.h"
#include "menus/settings.h"
#include "menus/flood.h"

// EEPROM addresses
#define ADDR_OUTLET_OFFSET 0
#define ADDR_FERVO_OFFSET (OUTLET_SIZE*N_OUTLETS)
#define ADDR_PUMP_OFFSET (ADDR_FERVO_OFFSET + FERVO_SIZE)

extern I2CLCD lcd;

extern struct rtctime_t rtc_time;

extern OneButton btn_flood_stop;
extern OneButton btn_next;
extern OneButton btn_setup;
extern OneButton btn_prev;

extern Encoder enc;

extern DHT dht;

extern Outlet *outlets[N_OUTLETS];
extern Fervo servo;
extern Pump pump;

extern SettingsMenu settings_menu;
extern FloodMenu flood_menu;

#endif