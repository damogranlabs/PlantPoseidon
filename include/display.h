#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <Arduino.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#define CC_LEFT 0
#define CC_RIGHT 1
#define CC_ON 2
#define CC_OFF 3

#define LCD_ADD 0x27
#define LCD_X_SIZE 20
#define LCD_Y_SIZE 4
#define LCD_BACKLIGHT_TIMEOUT 5000

// Menu texts
extern unsigned char arrow_left[8];
extern unsigned char arrow_right[8];
extern unsigned char bool_on[8];
extern unsigned char bool_off[8];

extern const char outlet_label[] PROGMEM;
extern const char active_label[] PROGMEM;
extern const char interval_label[] PROGMEM;
extern const int intervals[] PROGMEM;

extern const char duration_label[] PROGMEM;
extern const int durations[] PROGMEM;

extern const char time_label[] PROGMEM;
extern const char clock_point[] PROGMEM;
extern const char date_point[] PROGMEM;

extern const char servo_min_label[] PROGMEM;
extern const char servo_max_label[] PROGMEM;
extern const char servo_zero_label[] PROGMEM;

extern hd44780_I2Cexp lcd;
void setup_lcd(void);

// backlight
extern unsigned long t_backlight;
void touch(void);
void update_backlight(void);

// status
void show_status(void);

#endif