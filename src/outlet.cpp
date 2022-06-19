#include <Arduino.h>
#include <EEPROM.h>

#include "pinout.h"
#include "outlet.h"
#include "util.h"
#include "fervo.h"

// TODO: remove
#include "display.h"

///
/// Methods and all
///
Outlet::Outlet(int outlet_id)
{
    id = outlet_id;

    // schedule + CRC
    address = (sizeof(schedule) + sizeof(unsigned long)) * id;

    load();
}

bool Outlet::updateSchedule(bool enabled, int interval, int time, int duration)
{
    schedule.enabled = enabled;
    schedule.interval = interval;
    schedule.time = time;
    schedule.duration = duration;
}

void Outlet::load(void)
{
    EEPROM.get(address, schedule);

    // CRC check if everything is OK;
    // this is written in EEPROM
    unsigned long saved_crc;
    EEPROM.get(address + sizeof(struct schedule_data), saved_crc);
    // this is what has just been loaded
    unsigned long loaded_crc = crc((uint8_t *)&schedule, sizeof(schedule));

    if (saved_crc != loaded_crc)
    {
        // OMG RESET THE VALUES
        schedule.enabled = false;
        schedule.interval = O_INTERVAL_DEFAULT;
        schedule.time = O_TIME_DEFAULT;
        schedule.duration = O_DURATION_DEFAULT;
    }
}

void Outlet::save(void)
{
    EEPROM.put(address, schedule);

    // write a crc after schedule_data
    unsigned long check = crc((uint8_t *)&schedule, sizeof(schedule));
    EEPROM.put(address + sizeof(schedule), check);
}

void Outlet::open(unsigned long duration){
    // turn the plate
    servo.easeMove(outlet_to_angle(id));

    // open the falve
    lcd.setCursor(19, 0);
    lcd.print("O");

    // if the stop button is pressed during opening time, ...
    unsigned long t_end = millis() + duration;
    while(millis() < t_end){
        // ... stop
        if(digitalRead(BTN_FLOOD_PIN) == LOW) break;
    }

    lcd.setCursor(19, 0);
    lcd.print(" ");
}

///
/// Globals
///
Outlet *outlets[N_OUTLETS];
