#ifndef _TIME_H
#define _TIME_H

#include "DS1338.h"

void setup_rtc(void);
struct rtctime_t *getTime(void);

#endif