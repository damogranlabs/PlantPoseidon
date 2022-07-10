#ifndef _TIME_H
#define _TIME_H

#include "DS1338.h"

extern struct rtctime_t rtc_time;
void setup_rtc(void);

struct schedule_data
{
    // when to open
    bool enabled;
    uint8_t interval; // always in hours
    uint16_t time; // hour of the day
    uint16_t duration; // always in seconds

    // time last opened
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
};

#endif