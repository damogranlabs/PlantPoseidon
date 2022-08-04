#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <Arduino.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>


#define CC_LEFT 0
#define CC_RIGHT 1
#define CC_ON 2
#define CC_OFF 3
#define CC_DEGREE 4

#define LCD_ADDR 0x27
#define LCD_X_SIZE 20
#define LCD_Y_SIZE 4
#define LCD_BACKLIGHT_TIMEOUT 60000

#define LCD_BUF_SIZE (LCD_X_SIZE+1)

// Menu texts
extern unsigned char arrow_left[8];
extern unsigned char arrow_right[8];
extern unsigned char bool_on[8];
extern unsigned char bool_off[8];

extern const char outlet_label[] PROGMEM;
extern const char active_label[] PROGMEM;
extern const char interval_label[] PROGMEM;
extern const int intervals[] PROGMEM;

extern const char duration_label[] PROGMEM;
extern const int durations[] PROGMEM;

extern const char time_label[] PROGMEM;
extern const char clock_point[] PROGMEM;
extern const char date_point[] PROGMEM;

extern const char servo_min_label[] PROGMEM;
extern const char servo_max_label[] PROGMEM;
extern const char servo_zero_label[] PROGMEM;
extern const char servo_mid_label[] PROGMEM;

///
/// extend LCD with backlight tracking
///
class I2CLCD : public hd44780_I2Cexp
{
public:
    using hd44780_I2Cexp::hd44780_I2Cexp;
    void begin(void);

    // reset BL timer
    void touch(void);
    // check for timeout and reset
    void check(void);

    int printPgm(int line, int column, const char *text);
    int printPgmTable(int line, int column, const char * const *table, int i_entry);
    void printSubstr(char *str, int start, int end);

    void showStatus(void);
private:
    char pgm_buffer[LCD_BUF_SIZE];
    unsigned long t_backlight{};
};

#endif