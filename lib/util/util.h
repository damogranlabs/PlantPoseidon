#ifndef _UTIL_H
#define _UTIL_H

#include <inttypes.h>

int getDigitCount(uint16_t value);
unsigned long crc(uint8_t *data, int size);
int wrap(int value, int min, int max);

bool isLeapYear(int year);
uint8_t daysInMonth(int year, int month);
uint8_t validateDay(int year, int month, int day);

#endif