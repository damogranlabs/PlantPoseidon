#include <Arduino.h>
#include <LiquidCrystal.h>

#include "display.h"
#include "pinout.h"

///
/// Custom characters
///
unsigned char arrow_left[8] = {
    0b00001,
    0b00010,
    0b00101,
    0b01010,
    0b00101,
    0b00010,
    0b00001,

    0b00000,
};

unsigned char arrow_right[8] = {
    0b10000,
    0b01000,
    0b10100,
    0b01010,
    0b10100,
    0b01000,
    0b10000,

    0b00000,
};

unsigned char bool_on[8] = {
    0b00000,
    0b00000,
    0b00001,
    0b00010,
    0b10100,
    0b01000,
    0b00000,
    0b00000
};

unsigned char bool_off[8] = {
    0b00000,
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000
};

///
/// Menu texts
///
const char active_label[] PROGMEM = "Vklop";

// interval in hours
const char interval_label[] PROGMEM = "Zalij na";
const int intervals[] PROGMEM = {
    12, 24, 2*24, 3*24, 4*24, 5*24, 6*24, // 0.5, 1, 2, 3, 4, 5, 6 days
    7*24, 2*7*24, 3*7*24, 4*7*24, // 1, 2, 3, 4 weeks
    -1 // end
};

// valve open duration in seconds
const char duration_label[] PROGMEM = "za";
const int durations[] PROGMEM = {
    1, 2, 3, 4, 5, 10, 15, 20, 30, 40, 50, 60, 90, 120, 180, 240, 300,
    -1
};

// clock
const char time_label[] PROGMEM = "ob";
const char clock_point[] PROGMEM = ":";
const char date_point[] PROGMEM = ".";

// servo
const char servo_min_label[] PROGMEM = "Min. kot";
const char servo_max_label[] PROGMEM = "Max. kot";
const char servo_zero_label[] PROGMEM = "Pozicija #1";


///
/// LCD object
///
LiquidCrystal lcd(P_LCD_RS, P_LCD_EN, P_LCD_D4, P_LCD_D5, P_LCD_D6, P_LCD_D7);
