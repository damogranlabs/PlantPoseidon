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
    int min;
    int max;
    int zero;
};

class Fervo : public Servo
{
public:
    Fervo(void);

    // same as write() but with a finite acceleration
    void easeMove(int new_angle);

    // add a few details for easier handling of settings;
    int getMin(void) { return data.min; };
    int getMax(void) { return data.max; };
    int getZero(void) { return data.zero; };

    void setMin(int v) { data.min = v; };
    void setMax(int v) { data.max = v; };
    void setZero(int v) { data.zero = v; };

    void load(void);
    void save(void);

    int outletToAngle(int i_outlet);

private:
    servo_data data;
};

void setup_servo(void);
int outletToAngle(int i_outlet);

#endif