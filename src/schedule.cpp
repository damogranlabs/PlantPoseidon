#include <Arduino.h>

#include "DS1338.h"

struct rtctime_t rtc_time;

void setup_rtc(void){
    ds1338_clean_osf();
    ds1338_disable_sqw();
}

///
/// Date/time
///
bool isLeapYear(int year){
    if(year % 400 == 0) return true;
    if(year % 100 == 0) return false;
    return (year % 4 == 0);
}

int daysInMonth(int year, int month){
    switch(month){
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            if(isLeapYear(year)) return 29;
            return 28;
        default:
            break;
    }

    return 31;
}

int validateDay(int year, int month, int day){
    // clip the date for given month; returns a 'valid' 'day'
    return min(day, daysInMonth(year, month));
}