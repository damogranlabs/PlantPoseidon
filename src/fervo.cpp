#include <Arduino.h>
#include <EEPROM.h>
#include <Servo.h>

#include "pinout.h"
#include "fervo.h"
#include "outlet.h"
#include "util.h"

#include "globals.h"

///
/// Methods and all
///
Fervo::Fervo(void) : Servo()
{
    load();
}

void Fervo::load(void)
{
    // same as Outlet::load but different
    EEPROM.get(SERVO_ADDRESS, data);

    unsigned long saved_crc;
    EEPROM.get(SERVO_ADDRESS + sizeof(struct servo_data), saved_crc);
    unsigned long loaded_crc = crc((uint8_t *)&data, sizeof(data));

    if (saved_crc != loaded_crc)
    {
        data.min = SERVO_MIN;
        data.max = SERVO_MAX;
        data.zero = SERVO_MIN;
    }
}

void Fervo::save(void)
{
    EEPROM.put(SERVO_ADDRESS, data);

    unsigned long check = crc((uint8_t *)&data, sizeof(data));
    EEPROM.put(SERVO_ADDRESS + sizeof(data), check);
}

void Fervo::easeMove(int new_angle){
    if (new_angle < 200){
        // when setting limits through menu, the servo moves to current item value,
        // which is in 'microseconds'; this is also the convention of the Servo library
        new_angle = (int)((long)new_angle * (long)(data.max - data.min) / 180 + data.min);
    }

    long old_angle = (long)readMicroseconds();

    if(old_angle == new_angle) return;

    // long map(long x, long in_min, long in_max, long out_min, long out_max)
    #define T_EASING 3000
    long a, d = T_EASING*uabs(old_angle - new_angle)/(SERVO_MAX - SERVO_MIN);

    for(long i = 0; i < d; i++){
        a = map(i, 0, d, old_angle, new_angle);
        writeMicroseconds(a);
        delay(1);
    }
};

int Fervo::outletToAngle(int i_outlet){
    // this should represent approximately 180 degrees
    int servo_range = getMax() - getMin();
    int delta_outlet = 2*servo_range/N_OUTLETS;

    int pos_outlet = getZero() + i_outlet*delta_outlet;
    if(pos_outlet > getMax()) pos_outlet -= servo_range + delta_outlet/2;

    return pos_outlet;
}

void setup_servo(void)
{
    servo.attach(SERV1_PIN);
    servo.write(90);
}