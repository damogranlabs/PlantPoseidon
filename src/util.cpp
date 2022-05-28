#include <Arduino.h>

#include "globals.h"

int getDigitCount(int value){
    int digits = 0, remainder = value;

    while(remainder > 0){
        digits += 1;
        remainder = remainder / 10;
    }

    return max(1, digits);
}

unsigned long crc(uint8_t *data, int size){
    // https://docs.arduino.cc/learn/programming/eeprom-guide
    const unsigned long crc_table[16] = {
        0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
        0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
        0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
        0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
    };

    unsigned long crc = ~0L;

    for(int index = 0; index < size; ++index){
        crc = crc_table[(crc ^ data[index]) & 0x0f] ^ (crc >> 4);
        crc = crc_table[(crc ^ (data[index] >> 4)) & 0x0f] ^ (crc >> 4);
        crc = ~crc;
    }

    return crc;
}

void easeMove(int new_angle){
    // tabulated f(x) = 1000 * (-(cos(pi*x) - 1)/2)
    // https://easings.net/#easeInOutSine
    const int fx[] PROGMEM = {
          0,   1,   2,   5,  10,  15,  22,  29,
         38,  48,  59,  71,  84,  98, 113, 130,
        146, 164, 183, 202, 222, 243, 264, 286,
        309, 332, 355, 379, 402, 427, 451, 475,
        500, 525, 549, 573, 598, 621, 645, 668,
        691, 714, 736, 757, 778, 798, 817, 836,
        854, 870, 887, 902, 916, 929, 941, 952,
        962, 971, 978, 985, 990, 995, 998, 1000, 1000
    };
    #define N_SAMPLES (sizeof(fx)/sizeof(fx[0]))

    if(new_angle < 200){
        // when setting limits through menu, the servo moves to current item value,
        // which is in 'microseconds'; this is also the convention of the Servo library
        new_angle = (int)((long)new_angle*(long)(servo_max - servo_min)/180 + servo_min);
    }

    long old_angle = (long)servo.readMicroseconds();
    long delta_angle = (long)new_angle - old_angle;

    if(delta_angle == 0) return;

    unsigned long t_start = millis();
    unsigned long delta_t = T_MAX*abs(delta_angle) / (servo_max - servo_min);
    unsigned long t_end = t_start + delta_t;
    unsigned long t_now = t_start;
    
    // subdivisions: linear interpolation between tabulated points,
    unsigned int i_left, i_right;
    unsigned long t_left, dt = delta_t/N_SAMPLES;
    int r;
    
    while(t_now < t_end){
        t_now = millis();

        i_left = (t_now - t_start)/dt;
        i_left = i_left >= N_SAMPLES ? N_SAMPLES-2 : i_left;
        i_right = i_left + 1;

        t_left = t_start + i_left*dt;

        r = (fx[i_left] + (fx[i_right] - fx[i_left])*((int)(t_now - t_left)/dt));
        servo.writeMicroseconds(old_angle + (delta_angle * r)/fx[N_SAMPLES-1]);
    }
};