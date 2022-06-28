#include <Arduino.h>

#include "pinout.h"
#include "display.h"
#include "schedule.h"
#include "util.h"

// hd44780_I2Cexp lcd(addr, chiptype,       rs,[rw],en,d4,d5,d6,d7,bl,blLevel);
hd44780_I2Cexp lcd(LCD_ADD,
                   I2Cexp_PCF8574,
                   P_LCD_RS,
                   P_LCD_RW,
                   P_LCD_EN,
                   P_LCD_D4,
                   P_LCD_D5,
                   P_LCD_D6,
                   P_LCD_D7,
                   P_LCD_BL,
                   HIGH);

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
    0b00000};

unsigned char bool_off[8] = {
    0b00000,
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000};

///
/// Menu texts
///
const char outlet_label[] PROGMEM = "Teglc";
const char active_label[] PROGMEM = "Vklop";

// interval in hours
const char interval_label[] PROGMEM = "Zalij na";
const int intervals[] PROGMEM = {
    12, 24, 2*24, 3*24, 4*24, 5*24, 6*24, // 0.5, 1, 2, 3, 4, 5, 6 days
    7*24, 2*7*24, 3*7*24, 4*7*24,         // 1, 2, 3, 4 weeks
    -1                                    // end
};

// valve open duration in seconds
const char duration_label[] PROGMEM = "za";
const int durations[] PROGMEM = {
    1, 2, 3, 4, 5, 10, 15, 20, 30, 40, 50, 60, 90, 120, 180, 240, 300,
    -1};

// clock
const char time_label[] PROGMEM = "ob";
const char clock_point[] PROGMEM = ":";
const char date_point[] PROGMEM = ".";

// servo
const char servo_min_label[] PROGMEM = "Min. kot";
const char servo_max_label[] PROGMEM = "Max. kot";
const char servo_zero_label[] PROGMEM = "Pozicija #1";

void setup_lcd(void){
    lcd.begin(LCD_X_SIZE, LCD_Y_SIZE);
    lcd.setCursor(0, 0);
    
    lcd.clear();
    lcd.createChar(CC_LEFT, arrow_left);
    lcd.createChar(CC_RIGHT, arrow_right);
    lcd.createChar(CC_ON, bool_on);
    lcd.createChar(CC_OFF, bool_off);

    lcd.backlight(); // handle separately
    t_backlight = millis();
}

unsigned long t_backlight;

void touch(void){
    t_backlight = millis();
    lcd.backlight();
}

void update_backlight(void){
    // TODO TODO: check power consumption/7805 temperature
    if(millis() - t_backlight > LCD_BACKLIGHT_TIMEOUT){
        lcd.noBacklight();
    }
}

void substr_to_lcd(char *str, int start, int end){
    for(int i = start; i < end; i++){
        lcd.print(str[i]);
    }
}

void show_status(void){
    static unsigned long t_updated = millis();
    static char buf[20];
    
    if(millis() - t_updated > 1000){
        t_updated = millis();

        if(ds1338_read_time(&rtc_time) != 0){
            showI2CError();
            return;
        }

        // format_time_str prints:
        // 0123456789012345678
        // 2022-06-19T13:58:11
        format_time_str(&rtc_time, buf);
        lcd.setCursor(0, 1);
        lcd.print(buf);

        // print:
        // 13:59
        lcd.setCursor(15, 0);
        substr_to_lcd(buf, 11, 13);
        
        //every other second has no ':' mark
        lcd.setCursor(15+2, 0);
        if(rtc_time.second % 2 != 0) lcd.print(' ');
        else lcd.print(':');

        lcd.setCursor(15+3, 0);
        substr_to_lcd(buf, 14, 16);

        // print:
        // 21.09.2022
        lcd.setCursor(0, 0);
        substr_to_lcd(buf, 8, 10);
        lcd.print('.');
        substr_to_lcd(buf, 5, 7);
        lcd.print('.');
        substr_to_lcd(buf, 0, 4);
    }
}
