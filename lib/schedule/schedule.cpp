#include <Arduino.h>

#include "DS1338.h"

void setup_rtc(void){
    ds1338_clean_osf();
    ds1338_disable_sqw();
}

struct rtctime_t *getTime(void){
    static struct rtctime_t rtc_time;
    static unsigned long t_obtained = 0;

    // don't bother the RTC too often because it takes time [literally]
    if(millis() - t_obtained > 1000){
        ds1338_read_time(&rtc_time);
        t_obtained = millis();
    }

    return &rtc_time;
}
