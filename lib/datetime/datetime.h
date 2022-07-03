#ifndef _DATETIME_H
#define _DATETIME_H

#include <inttypes.h>

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

///
/// Date and time
///
bool isLeapYear(uint16_t year);
uint8_t daysInMonth(uint16_t year, uint8_t month);
uint8_t validateDay(uint16_t year, uint8_t month, uint8_t day);



#endif