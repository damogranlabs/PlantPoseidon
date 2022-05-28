#include <Arduino.h>
#include <Servo.h>

#include "globals.h"

class Fervo : public Servo
{
public:
    using Servo::Servo;

    // add a few details for easier handling of settings;
    // must be 
    int servo_min{700}; // minimum value/physical angle that the servo can move to
    int servo_max{2300}; // maximum angle
    int servo_zero{700}; // position of the first outlet
    unsigned int address{SERVO_ADDRESS}; // EEPROM address

    void load(void);
    void save(void);
};