#include <Arduino.h>

#include "pinout.h"
#include "display.h"
#include "util.h"
#include "globals.h"
///
/// Custom characters
///
unsigned char arrow_left[8] = {
    0b00001,
    0b00010,
    0b00101,
    0b01010,
    0b00101,
    0b00010,
    0b00001,

    0b00000,
};

unsigned char arrow_right[8] = {
    0b10000,
    0b01000,
    0b10100,
    0b01010,
    0b10100,
    0b01000,
    0b10000,

    0b00000,
};

unsigned char bool_on[8] = {
    0b00000,
    0b00000,
    0b00001,
    0b00010,
    0b10100,
    0b01000,
    0b00000,
    0b00000
};

unsigned char bool_off[8] = {
    0b00000,
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000
};

unsigned char degree[8] = {
    0b00111,
    0b00101,
    0b00111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};

///
/// Menu texts
///
const char outlet_label[] PROGMEM = "Teglc";
const char active_label[] PROGMEM = "Vklop";

// interval in hours
const char interval_label[] PROGMEM = "Zalij na";
const int intervals[] PROGMEM = {
    12, 24, 2*24, 3*24, 4*24, 5*24, 6*24, // 0.5, 1, 2, 3, 4, 5, 6 days
    7*24, 2*7*24, 3*7*24, 4*7*24,         // 1, 2, 3, 4 weeks
    -1                                    // end
};

// valve open duration in seconds
const char duration_label[] PROGMEM = "za";
const int durations[] PROGMEM = {
    1, 2, 3, 4, 5, 10, 15, 20, 30, 40, 50, 60, 90, 120, 180, 240, 300,
    -1};

// clock
const char time_label[] PROGMEM = "ob";
const char clock_point[] PROGMEM = ":";
const char date_point[] PROGMEM = ".";

// servo
const char servo_min_label[] PROGMEM = "Min";
const char servo_max_label[] PROGMEM = "Max";
const char servo_zero_label[] PROGMEM = "Pozicija #1";
const char servo_mid_label[] PROGMEM = "Pozicija #2";

// pump
const char pump_active_label[] PROGMEM = "Vklopi";
const char pump_warmup_label[] PROGMEM = "Zakasnitev";

void I2CLCD::begin(void){
    hd44780_I2Cexp::begin(LCD_X_SIZE, LCD_Y_SIZE);

    setCursor(0, 0);
    
    clear();
    createChar(CC_LEFT, arrow_left);
    createChar(CC_RIGHT, arrow_right);
    createChar(CC_ON, bool_on);
    createChar(CC_OFF, bool_off);
    createChar(CC_DEGREE, degree);

    backlight(); // handle separately
    t_backlight = millis();
}

void I2CLCD::touch(void){
    backlight();
    t_backlight = millis();
}

void I2CLCD::check(void){
    if(millis() - t_backlight > LCD_BACKLIGHT_TIMEOUT){
        noBacklight();
    }
}

int I2CLCD::printPgm(int line, int column, const char *text){
    // reads a string from PROGMEM and outputs it directly to LiquidCrystal,
    // skipping buffering
    char c;
    unsigned int i;

    for(i = 0; i < strlen_P(text); i++){
        c = pgm_read_byte_near(text + i);
        setCursor(column + i, line);
        print(c);
    }

    return i;
}

int I2CLCD::printPgmTable(int line, int column, const char * const *table, int i_entry){
    // reads an entry from a string table stored in PROGMEM
    // https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
    memset(pgm_buffer, 0, LCD_BUF_SIZE);

    strncpy_P(pgm_buffer, (char*)pgm_read_word(&(table[i_entry])), LCD_BUF_SIZE-1);
    setCursor(column, line);
    print(pgm_buffer);

    return strlen(pgm_buffer);
}

void I2CLCD::printSubstr(char *str, int start, int end){
    for(int i = start; i < end; i++){
        print(str[i]);
    }
}

void I2CLCD::showStatus(void){
    static char buf[20];
    // format_time_str prints:
    // 0123456789012345678
    // 2022-06-19T13:58:11
    format_time_str(&rtc_time, buf);
    
    // extract relevant data from ready-formatted buffer
    // 13:59
    setCursor(15, 0);
    printSubstr(buf, 11, 16);

    // print:
    // 21.09.2022
    setCursor(0, 0);
    printSubstr(buf, 8, 10);
    print('.');
    printSubstr(buf, 5, 7);
    print('.');
    printSubstr(buf, 0, 4);

    // clear the second line
    memset(buf, ' ', sizeof(buf) - 1);
    setCursor(0, 1);
    print(buf);
    // write down temperature and humidity
    setCursor(0, 1);
    print((int)dht.readTemperature());
    write(byte(CC_DEGREE));
    print("C ");
    print((int)dht.readHumidity());
    print('%');    
}

void I2CLCD::progressbar(unsigned long value, unsigned long max, int row, int col){
    #define REFRESH_RATE 250 // [ms]

    static uint8_t pattern = 0b10110101;
    static uint8_t height, i;
    static unsigned char stack[8];

    static unsigned long t_refreshed = 0;
    if(millis() - t_refreshed < REFRESH_RATE) return;

    height = 8*value/max;

    // full brick
    memset(stack, 0xff, 8);

    // empty to 8-height
    for(i = 0; i < 8-height; i++){
        stack[i] = 0;
    }

    // the line in between
    if(height <= 8){
        // https://stackoverflow.com/questions/13289397/circular-shift-in-c
        pattern = (pattern << 1) | (pattern >> 7);
        stack[8-height] = pattern;
    }

    createChar(CC_PROGRESS, stack);
    setCursor(col, row);
    write(byte(CC_PROGRESS));

    t_refreshed = millis();
}

