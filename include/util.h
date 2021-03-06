#ifndef _UTIL_H
#define _UTIL_H

///
/// PROGMEM shortcuts
/// 
#define STR_BUFSIZE 21 // size of buffers for string operations; 1 more than LCD's width

// a static buffer for all PROGMEM operations
extern char pgm_buffer[STR_BUFSIZE];

char *pgm_to_buffer(const char *text);
int pgm_to_lcd(int line, int column, const char *text);
char *pgm_table_to_buffer(const char *const *table, int i_entry);
int pgm_table_to_lcd(int line, int column, const char * const *table, int i_entry);

///
/// Misc stuff
///
int getDigitCount(int value);
unsigned long crc(uint8_t *data, int size);

#endif