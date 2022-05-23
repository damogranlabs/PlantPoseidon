#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#include "pinout.h"
#include "button.h"
#include "menu.h"

// Menu texts
extern unsigned char arrow_left[8];
extern unsigned char arrow_right[8];
extern unsigned char bool_on[8];
extern unsigned char bool_off[8];

extern const char active_label[] PROGMEM;
extern const char interval_label[] PROGMEM;
extern const int intervals[] PROGMEM;

extern const char duration_label[] PROGMEM;
extern const int durations[] PROGMEM;

extern const char time_label[] PROGMEM;
extern const char clock_point[] PROGMEM;
extern const char date_point[] PROGMEM;

// Display
extern LiquidCrystal lcd;
// custom character indexes

#define CC_LEFT 0
#define CC_RIGHT 1
#define CC_ON 2
#define CC_OFF 3

extern Button up;
extern Button down;
extern Button left;
extern Button right;

extern Outlet *outlets[N_OUTLETS];
#define N_SCREENS (N_OUTLETS + 1)
extern Screen *screens[N_SCREENS];
extern Menu menu;

// motor
#define T_MAX 10000 // max easing time (180 degrees, less is scaled)
extern Servo servo;

#endif