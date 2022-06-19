#include <Arduino.h>

#include "display.h"
#include "DS1338.h"

struct rtctime_t time;

void setup_rtc(void){
    ds1338_clean_osf();
    ds1338_disable_sqw();
}

void substr_to_lcd(char *str, int start, int end){
    for(int i = start; i < end; i++){
        lcd.print(str[i]);
    }
}

void print_time(int row, int col){
    char buf[20];
    int i;

    if(!ds1338_read_time(&time)){
        // returns:
        // 0123456789012345678
        // 2022-06-19T13:58:11
        format_time_str(&time, buf);

        // prints:
        // 13:59
        lcd.setCursor(col, row);
        substr_to_lcd(buf, 11, 16);
        
        if(time.second % 2 != 0){
            lcd.setCursor(col+2, row);
            lcd.print(' ');
        }
    }
}

void print_date(int row, int col){
    char buf[20];
    int i;

    if(!ds1338_read_time(&time)){
        format_time_str(&time, buf);

        // prints:
        // 21.09.2022
        lcd.setCursor(col, row);
        substr_to_lcd(buf, 8, 10);
        lcd.print('.');
        substr_to_lcd(buf, 5, 7);
        lcd.print('.');
        substr_to_lcd(buf, 0, 4);
    }
}