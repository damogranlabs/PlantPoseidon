#include <Arduino.h>

#include "DS1338.h"

struct rtctime_t rtc_time;

void setup_rtc(void){
    ds1338_clean_osf();
    ds1338_disable_sqw();
}
