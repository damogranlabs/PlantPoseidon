#include <Arduino.h>

#include "util.h"
#include "display.h"

///
/// PROGMEM stuff
///

char pgm_buffer[STR_BUFSIZE];

char *pgm_to_buffer(const char *text){
    // copies a PROGMEMed string pgm::buffer, returning pointer to it
    memset(pgm_buffer, 0, STR_BUFSIZE);

    char c;
    unsigned int i;

    for(i = 0; i < strlen_P(text) || i < STR_BUFSIZE-1; i++){
        c = pgm_read_byte_near(text + i);
        pgm_buffer[i] = c;
    }

    return pgm_buffer;
}

int pgm_to_lcd(int line, int column, const char *text){
    // reads a string from PROGMEM and outputs it directly to LiquidCrystal,
    // skipping buffering
    char c;
    unsigned int i;

    for(i = 0; i < strlen_P(text); i++){
        c = pgm_read_byte_near(text + i);
        lcd.setCursor(column + i, line);
        lcd.print(c);
    }

    return i;
}

char *pgm_table_to_buffer(const char *const *table, int i_entry){
    // copies an entry from a string table stored in PROGMEM to pgm::buffer, returning pointer to it
    memset(pgm_buffer, 0, STR_BUFSIZE);
    strncpy_P(pgm_buffer, (char*)pgm_read_word(&(table[i_entry])), STR_BUFSIZE-1);

    return pgm_buffer;
}

int pgm_table_to_lcd(int line, int column, const char * const *table, int i_entry){
    // reads an entry from a string table stored in PROGMEM
    // https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
    memset(pgm_buffer, 0, STR_BUFSIZE);

    strncpy_P(pgm_buffer, (char*)pgm_read_word(&(table[i_entry])), STR_BUFSIZE-1);
    lcd.setCursor(column, line);
    lcd.print(pgm_buffer);

    return strlen(pgm_buffer);
}

///
/// Misc
///
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

int contain(int value, int min, int max){
    if(value > max) return min;
    if(value < min) return max;
    return value;
}