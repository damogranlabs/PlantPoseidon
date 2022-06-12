#ifndef _OUTLET_H
#define _OUTLET_H

#include <Arduino.h>

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
struct schedule_data
{
    bool enabled;
    int interval;
    int time;
    int duration;
};

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
    void open(unsigned long duration);

private:
    int id;
    int address; // EEPROM

    // schedule and task managing
    schedule_data schedule;
};

///
/// Globals
///
extern Outlet *outlets[N_OUTLETS];

#endif