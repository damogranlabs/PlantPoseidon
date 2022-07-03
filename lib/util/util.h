#ifndef _UTIL_H
#define _UTIL_H

#include <Arduino.h>

///
/// PROGMEM shortcuts
/// 
#define STR_BUFSIZE 21 // size of buffers for string operations; 1 more than LCD's width

// a static buffer for all PROGMEM operations
extern char pgm_buffer[STR_BUFSIZE];

char *pgmToBuffer(const char *text);
// int pgmToLcd(int line, int column, const char *text);
char *pgmTableToBuffer(const char *const *table, int i_entry);
// int pgmTableToLcd(int line, int column, const char * const *table, int i_entry);

// ///
// /// Misc stuff
// ///
// void showI2CError(void);
int getDigitCount(int value);
unsigned long crc(uint8_t *data, int size);
int contain(int value, int min, int max);
// int outletToAngle(int i_outlet);

#endif