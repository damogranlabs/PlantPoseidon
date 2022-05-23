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

    // servos are quick but the plate is heavy;
    // to reduce strain/wear on gears, ease the transition
    // with a sinusoidal-ish function
    // also, keep this function blocking as
    // nothing is more important or satisfying than a turning motor
    double old_angle = (double)servo.read();

    // TODO: integer math + tabulated equation
    double delta_angle = (double)new_angle - old_angle;

    // the move starts now
    // and lasts at most T_MAX ms; smaller deltas need less time
    double t_start = (double)millis();
    double delta_t = abs(delta_angle)*T_MAX/180;
    double t_end = t_start + delta_t;
    double t_now = t_start;

    // scale t_start...t_end => t => to 0...1,
    // then map t =  -(cos(pi*t) - 1)/2
    double t, p; 
    
    while(t_now < t_end){
        t = (t_now - t_start) / delta_t;
        p = (double)old_angle + delta_angle*(-(cos(PI*t) - 1)/2);

        servo.write((int)p);
        
        t_now = (double)millis();
    }
};