#ifndef _OUTLET_H
#define _OUTLET_H

#include <Arduino.h>

#include "schedule.h"

///
/// Settings/defaults
///
// number of outlets
#define N_OUTLETS 8

// defaults for fresh EEPROMs
#define O_TIME_DEFAULT 19     // hour of day
#define O_INTERVAL_DEFAULT 24 // hours
#define O_DURATION_DEFAULT 10 // seconds

///
/// Class definitions and whatnot
///
// pumping schedule data
class Outlet
{
public:
    Outlet(int id);
    int getId(void) { return id; };

    // schedule
    schedule_data *getSchedule(void) { return &schedule; };
    bool updateSchedule(bool enabled, int time, int interval, int duration);

    // EEPROM
    void load(void);
    void save(void);

    // valve steering
    bool check(void); // open on schedule
    void flood(unsigned long duration); // or open from the flood menu
    

private:
    int id;
    unsigned int address; // EEPROM

    // schedule and task managing
    struct schedule_data schedule;
    bool pastDue(void);
    void open(unsigned long duration, bool log);
};

#endif