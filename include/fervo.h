#ifndef _FERVO_H
#define _FERVO_H

#include <Arduino.h>
#include <Servo.h>

#include "pinout.h"

///
/// Settings
///
// default values; these should be standard but no one cares
// so they can be modified by the user
#define SERVO_MAX 2300 // maximum pulse width that still turns the shaft
#define SERVO_MIN 700  // and minimum; 

// time to travel full-range; reduced proportionally for shorter moves
#define T_EASING 3000

///
/// Class definitions
///
struct servo_data
{
    // reachable angles
    int min;
    int max;
    // position of the first outlet, the next from
    // minimum servo position
    int zero;
    // position of the last (N_OUTLETS/2)th outlet,
    // reachable using the same hole on rotating plate
    // (should be closest to maximum servo position)
    int mid;
};

class Fervo : public Servo
{
public:
    Fervo(void);

    // add a few details for easier handling of settings;
    int getMin(void) { return data.min; };
    int getMax(void) { return data.max; };
    int getZero(void) { return data.zero; };
    int getMid(void) { return data.mid; };

    void setMin(int v) { data.min = v; };
    void setMax(int v) { data.max = v; };
    void setZero(int v) { data.zero = v; };
    void setMid(int v) { data.mid = v; };

    void load(void);
    void save(void);
    
    // same as write() but with a finite acceleration
    void easeMove(int new_angle);
    void moveToOutlet(int id){ easeMove(outletToAngle(id)); };
private:
    servo_data data;
    
    int outletToAngle(int i_outlet);
};

int outletToAngle(int i_outlet);

#define FERVO_SIZE (sizeof(struct servo_data) + sizeof(unsigned long))

#endif