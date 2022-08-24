#include <Arduino.h>
#include <EEPROM.h>

#include "pinout.h"
#include "outlet.h"
#include "fervo.h"
#include "util.h"
#include "globals.h"

///
/// Methods and all
///
Outlet::Outlet(int outlet_id){
    id = outlet_id;

    // address: schedule + CRC
    address = OUTLET_SIZE*id;
    load();
}

void Outlet::load(void){
    // TODO: DRY
    EEPROM.get(address, schedule);

    // CRC check if everything is OK;
    // this is written in EEPROM
    unsigned long saved_crc;
    EEPROM.get(address + sizeof(schedule), saved_crc);
    // this is what has just been loaded
    unsigned long loaded_crc = crc((uint8_t *)&schedule, sizeof(schedule));

    if (saved_crc != loaded_crc){
        // OMG RESET THE VALUES
        memset(&schedule, 0, sizeof(schedule));
        schedule.enabled = false;
        schedule.interval = O_INTERVAL_DEFAULT;
        schedule.time = O_TIME_DEFAULT;
        schedule.duration = O_DURATION_DEFAULT;

        // last opened? no idea
        schedule.year = 0;
        schedule.month = 1;
        schedule.day = 1;
        schedule.hour = 0;
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
    if(!compareHours(rtc_time.hour, schedule.time, schedule.interval)){
        return false;
    }

    // 3. last time it was opened is greater/equal to specified interval
    long delta = hourDelta(
        rtc_time.year + 2000, rtc_time.month, rtc_time.day, rtc_time.hour,
        schedule.year + 2000, schedule.month, schedule.day, schedule.hour);

    if(delta < 0){
        // something wrong with data
        return true;
    }
    return delta >= schedule.interval;
}

void Outlet::open(unsigned long duration, bool log){
    // remember being opened only when run on schedule
    // but not from the flood menu
    if(log){
        schedule.year = rtc_time.year;
        schedule.month = rtc_time.month;
        schedule.day = rtc_time.day;
        schedule.hour = rtc_time.hour;
        save();
    }

    // LCD:
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print(F("Zalivam #"));
    lcd.print(id+1);
    lcd.print(F("..."));
    
    // turn the plate
    servo.moveToOutlet(id);

    // turn on the pump
    if(!pump.start()) return;

    // open the falve
    digitalWrite(VALVE_PIN, HIGH);

    unsigned long t_start = millis();
    unsigned long t_now = t_start;
    unsigned long t_update = 0;
    unsigned long t_end = t_now + duration*1000;
    unsigned long t_delta;

    while((t_now <= t_end) && (digitalRead(BTN_FLOOD_PIN) == HIGH)){
        t_delta = t_now - t_start;
        lcd.progressbar(1000 + t_delta, duration*1000, 2, 1);

        if(t_now - t_update > 1000){
            lcd.setCursor(2, 2);
            lcd.print(1 + t_delta/1000);
            lcd.print('/');
            lcd.print(duration);
            t_update = t_now;
        }

        t_now = millis();
    }
}

void Outlet::close(void){
    // close the falve
    digitalWrite(VALVE_PIN, LOW);

    // turn off the pump
    pump.stop();
    
    // display
    lcd.clear();
}

void Outlet::flood(unsigned long duration){
    open(duration, false);
    close();
}

bool Outlet::check(void){
    if(pastDue()){
        open(schedule.duration, true);
        close();
        return true;
    }

    return false;
}
