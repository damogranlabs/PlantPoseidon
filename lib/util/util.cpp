#include <inttypes.h>

#include "util.h"

int getDigitCount(uint16_t value){
    int digits = 0, remainder = value;

    while(remainder > 0){
        digits += 1;
        remainder = remainder / 10;
    }

    if(digits < 1) return 1;
    return digits;
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

int wrap(int value, int min, int max){
    if(value > max) return min;
    if(value < min) return max;
    return value;
}


bool isLeapYear(int year){
    if(year % 400 == 0) return true;
    if(year % 100 == 0) return false;
    return (year % 4 == 0);
}

uint8_t daysInMonth(int year, int month){
    switch(month){
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            if(isLeapYear(year)) return 29;
            return 28;
        default:
            break;
    }

    return 31;
}

uint8_t validateDay(int year, int month, int day){
    // clip the date for given month; returns a 'valid' 'day'
    uint8_t max_days = daysInMonth(year, month);
    if(day > max_days) return max_days;
    
    return day;
}