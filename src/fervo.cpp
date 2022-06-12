#include <Arduino.h>
#include <EEPROM.h>
#include <Servo.h>

#include "pinout.h"
#include "fervo.h"
#include "util.h"

// TODO: un-include
#include "display.h"

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

void Fervo::easeMove(int new_angle)
{
    // tabulated f(x) = 1000 * (-(cos(pi*x) - 1)/2)
    // https://easings.net/#easeInOutSine
    const int fx[] PROGMEM = {
        0, 1, 2, 5, 10, 15, 22, 29,
        38, 48, 59, 71, 84, 98, 113, 130,
        146, 164, 183, 202, 222, 243, 264, 286,
        309, 332, 355, 379, 402, 427, 451, 475,
        500, 525, 549, 573, 598, 621, 645, 668,
        691, 714, 736, 757, 778, 798, 817, 836,
        854, 870, 887, 902, 916, 929, 941, 952,
        962, 971, 978, 985, 990, 995, 998, 1000, 1000};
#define N_SAMPLES (sizeof(fx) / sizeof(fx[0]))

    if (new_angle < 200)
    {
        // when setting limits through menu, the servo moves to current item value,
        // which is in 'microseconds'; this is also the convention of the Servo library
        new_angle = (int)((long)new_angle * (long)(data.max - data.min) / 180 + data.min);
    }

    long old_angle = (long)readMicroseconds();
    long delta_angle = (long)new_angle - old_angle;

    if (delta_angle == 0)
        return;

    unsigned long t_start = millis();
    // the abs(x) macro is written in Arduino.h for Uno but Nano Every uses
    // __builtin_abs() from stdlib, which has been improved to not work properly.
    //unsigned long delta_t = SERVO_T_MOVE * abs(delta_angle) / (data.max - data.min);
    // it seems that for long integers, the function of choice is 'labs', which is like totally intuitive.
    // alas, there is no 'dabs' for doubles and 'fabs' for floats.
#define arduino_abs(x) ((x)>0?(x):-(x))
    unsigned long delta_t = SERVO_T_MOVE * labs(delta_angle) / (data.max - data.min);    
    unsigned long t_end = t_start + delta_t;
    unsigned long t_now = t_start;

    // subdivisions: linear interpolation between tabulated points
    unsigned int i_left, i_right;
    unsigned long t_left, dt = delta_t / N_SAMPLES;
    int r;

    while (t_now < t_end){
        t_now = millis();

        i_left = (t_now - t_start) / dt;
        i_left = i_left >= N_SAMPLES ? N_SAMPLES - 2 : i_left;
        i_right = i_left + 1;

        t_left = t_start + i_left * dt;

        r = (fx[i_left] + (fx[i_right] - fx[i_left]) * ((int)(t_now - t_left) / dt));
        writeMicroseconds(old_angle + (delta_angle * r) / fx[N_SAMPLES - 1]);
    }
};

///
/// Globals
///
Fervo servo;

void setup_servo(void)
{
    servo.attach(SERV1_PIN);
    servo.write(90);
}