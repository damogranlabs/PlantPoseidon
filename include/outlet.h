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

struct schedule_data {
    // schedule - when to open
    uint16_t interval; // always in hours
    uint16_t time; // hour of the day
    uint16_t duration; // always in seconds
    bool enabled;

    // time last opened
    uint8_t year;
    uint8_t month; // these two could be combined into
    uint8_t day;   // a single uint8 to save space; currently there's no need
    uint8_t hour;
};

// pumping schedule data
class Outlet
{
public:
    Outlet(int id);
    int getId(void) { return id; };

    // schedule: stored in eeprom
    struct schedule_data schedule;

    // EEPROM
    void load(void);
    void save(void);

    // valve steering
    bool check(void); // open on schedule
    void flood(unsigned long duration); // or open from the flood menu

private:
    int id;
    uint16_t address;

    bool pastDue(void);
    void open(unsigned long duration, bool log);
    void close(void);
};

// EEPROM address:
#define OUTLET_SIZE (sizeof(struct schedule_data) + sizeof(unsigned long))

#endif