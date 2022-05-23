#include <Arduino.h>
#include <LiquidCrystal.h>

#include "globals.h"
#include "progmem.h"

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