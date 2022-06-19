#ifndef _TIME_H
#define _TIME_H

#include "DS1338.h"

extern struct rtctime_t time;
void setup_rtc(void);

void print_time(int row, int col);
void print_date(int row, int col);

#endif