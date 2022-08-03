#ifndef _FERVO_H
#define _FERVO_H

#include <Arduino.h>
#include <Servo.h>

///
/// Settings
///
#define SERVO_ADDRESS 128 // EEPROM

// default values; these should be standard but no one cares
// so they can be modified by the user
#define SERVO_MAX 2300 // maximum pulse width that still turns the shaft
#define SERVO_MIN 700  // and minimum; 

///
/// Class definitions
///
struct servo_data
{
    // reachable angles
    int min;
    int max;
    // position of the first outlet
    int zero;
    // position of the second outlet
    int one;
};

class Fervo : public Servo
{
public:
    Fervo(void);

    // add a few details for easier handling of settings;
    int getMin(void) { return data.min; };
    int getMax(void) { return data.max; };
    int getZero(void) { return data.zero; };
    int getOne(void) { return data.one; };

    void setMin(int v) { data.min = v; };
    void setMax(int v) { data.max = v; };
    void setZero(int v) { data.zero = v; };
    void setOne(int v) { data.one = v; };

    void load(void);
    void save(void);

    // same as write() but with a finite acceleration
    void easeMove(int new_angle);
    void moveToOutlet(int id){ easeMove(outletToAngle(id)); };
private:
    servo_data data;

    int outletToAngle(int i_outlet);
};

void setup_servo(void);
int outletToAngle(int i_outlet);

#endif