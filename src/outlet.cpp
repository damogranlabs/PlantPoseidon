#include <Arduino.h>
#include <EEPROM.h>

#include "outlet.h"
#include "util.h"

///
/// Methods and all
///
Outlet::Outlet(int outlet_id)
{
    id = outlet_id;
    angle = id * 360 / N_OUTLETS;
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

void Outlet::open(void)
{
    // turn the plate and start the pump/open the valve
    digitalWrite(13, HIGH);
}

void Outlet::close(void)
{
    // turn off the pump/close the valve
    digitalWrite(13, LOW);
}

///
/// Globals
///
Outlet *outlets[N_OUTLETS];
