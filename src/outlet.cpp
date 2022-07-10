#include <Arduino.h>
#include <EEPROM.h>
#include <time.h>

#include "pinout.h"
#include "outlet.h"
#include "fervo.h"
#include "schedule.h"
#include "util.h"

#include "globals.h"


///
/// Methods and all
///
Outlet::Outlet(int outlet_id){
    id = outlet_id;

    // address: schedule + CRC
    address = (sizeof(schedule) + sizeof(unsigned long)) * id;
    load();
}

bool Outlet::updateSchedule(bool enabled, int interval, int time, int duration){
    schedule.enabled = enabled;
    schedule.interval = interval;
    schedule.time = time;
    schedule.duration = duration;
}

void Outlet::load(void){
    EEPROM.get(address, schedule);

    // CRC check if everything is OK;
    // this is written in EEPROM
    unsigned long saved_crc;
    EEPROM.get(address + sizeof(struct schedule_data), saved_crc);
    // this is what has just been loaded
    unsigned long loaded_crc = crc((uint8_t *)&schedule, sizeof(schedule));

    if (saved_crc != loaded_crc){
        // OMG RESET THE VALUES
        memset(&schedule, 0, sizeof(schedule));
        schedule.enabled = false;
        schedule.interval = O_INTERVAL_DEFAULT;
        schedule.time = O_TIME_DEFAULT;
        schedule.duration = O_DURATION_DEFAULT;
    }
}

void Outlet::save(void){
    EEPROM.put(address, schedule);

    // write a crc after schedule_data
    unsigned long check = crc((uint8_t *)&schedule, sizeof(schedule));
    EEPROM.put(address + sizeof(schedule), check);
}

bool Outlet::pastDue(void){
    // return true if the outlet should be opened;
    // on three conditions:
    // 1. the outlet is enabled
    if(!schedule.enabled){
        return false;
    }

    // 2. the time is as requested
    // (Achtung: also take into account less than 24h intervals)
    if(rtc_time.hour != schedule.time % schedule.interval){ // tested with python
        return false;
    }

    // 3. last time it was opened is greater/equal to specified interval
    struct tm tnow;
    struct tm targ;

    // "Datetime operations are notoriously tricky"
    //                            - Stackoverflow
    // copy the 'rtc' data to the standard <time.h> tm and run difftime;
    tnow.tm_year = rtc_time.year + 2000;
    tnow.tm_mon = rtc_time.month + 1;
    tnow.tm_mday = rtc_time.day;
    tnow.tm_hour = rtc_time.hour;
    tnow.tm_min = 0;
    tnow.tm_sec = 0;

    targ.tm_year = schedule.year + 2000;
    targ.tm_mon = schedule.month + 1;
    targ.tm_mday = schedule.day;
    targ.tm_hour = schedule.hour;
    targ.tm_min = 0;
    targ.tm_sec = 0;

    return (int)(difftime(mktime(&targ), mktime(&tnow))/3600) >= schedule.interval;
}

void Outlet::open(unsigned long duration, bool log){
    // remember being opened only when run on schedule
    // but not from the flood menu
    if(log){
        schedule.year = rtc_time.year;
        schedule.month = rtc_time.month;
        schedule.day = rtc_time.day;
        schedule.hour = rtc_time.hour;
    }
    
    // turn the plate
    servo.easeMove(servo.outletToAngle(id));

    // open the falve
    lcd.setCursor(19, 0);
    lcd.print("O");

    // if the stop button is pressed during opening time, ...
    unsigned long t_end = millis() + duration*1000;
    while(millis() < t_end){
        // ... stop
        if(digitalRead(BTN_FLOOD_PIN) == LOW){
            // debounce or the flood menu will also be closed
            delay(50);
            // wait for the button to be released
            while(digitalRead(BTN_FLOOD_PIN) == LOW) {};
            // cancel the flooding enterprise
            break;
        }
    }

    // close the falve
    lcd.setCursor(19, 0);
    lcd.print(" ");
}

void Outlet::flood(unsigned long duration){
    open(duration, false);
}

bool Outlet::check(void){
    if(pastDue()){
        open(schedule.duration, true);
        return true;
    }

    return false;
}
