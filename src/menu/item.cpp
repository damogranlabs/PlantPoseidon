#include <Arduino.h>

#include "display.h"
#include "menu.h"
#include "util.h"

Item::Item(const char *l, int r, int c, int v)
{
    // store attributes
    label = l;
    line = r;
    column = c;

    value = v;
}

Item::Item(const char *l, int r, int c, int v,
        bool p, char u, int ll, int hl) : 
        Item(l, r, c, v) // reuse the above constructor
{
    pad = p;
    unit = u;
    high_limit = hl;
    low_limit = ll;
}

void Item::show(void){
    if(label){
        // display the label on the screen and store its length
        l_label = pgm_to_lcd(line, column, label);

        // a space between a label and current choice
        lcd.setCursor(column + l_label, line);
        lcd.print(' '); // does not increase l_label
    }
    else {
        l_label = 0;
    }

    renderValue();
}

void Item::clear(void){
    // removes value and arrows
    for(int i = 0; i < l_value + 2; i++){
        lcd.setCursor(column + l_label + i, line);
        lcd.print(' ');
    }
}

void Item::activate(void){
    // show the < and > characters around the value
    lcd.setCursor(column + l_label, line);
    lcd.write(byte(CC_LEFT));

    lcd.setCursor(column + l_label + l_value + 1, line);
    lcd.write(byte(CC_RIGHT));
}

void Item::deactivate(void){
    lcd.setCursor(column + l_label, line);
    lcd.print(' ');

    lcd.setCursor(column + l_label + l_value + 1, line);
    lcd.print(' ');
}

void Item::renderValue(void){
    clear();
    int position = column + l_label + 1;
    
    lcd.setCursor(position, line);

    // padding: calculate the maximum number of digits from high limit
    if(pad && high_limit > 0){
        int digits = getDigitCount(value);
        int max_digits = getDigitCount(high_limit);

        for(int i = 0; i < max_digits; i++){
            lcd.print('0');
        }

        l_value = max_digits;
        lcd.setCursor(position + (max_digits-digits), line);
        lcd.print(value);
    }
    else{
        // write from the beginning
        l_value = lcd.print(value);
    }

    // add a unit if defined
    if(unit != 0) l_value += lcd.print(unit);
}

void Item::change(int direction){
    value += direction;

    // when low_limit and high_limit are the same, limiting is disabled
    if(high_limit > low_limit){
        // when over limit, wrap around
        if(value > high_limit) value = low_limit;
        if(value < low_limit) value = high_limit;
    }

    renderValue();
    activate();
};

void BoolItem::renderValue(void){
    clear();
    lcd.setCursor(column + l_label + 1, line);
    lcd.write(byte(value == 0 ? CC_OFF : CC_ON));
};

ChoiceItem::ChoiceItem(const char *label, int line, int column, int value, const int * _choices) :
    Item(label, line, column, value, false, (char)0, 0, 0)
{
    // save the choices array and count the number of items
    choices = _choices;

    int i = 0;
    while((int)pgm_read_word_near(choices + i++) != -1){ n_choices += 1; }

    // find i_choice
    change(0);
};

void ChoiceItem::change(int direction){
    // find the currently selected choice by value
    int this_value, this_diff, max_diff = INT16_MAX;
    i_choice = 0;
    
    for(int i = 0; i < n_choices; i++){
        this_value = pgm_read_word_near(choices + i);
        this_diff = abs(this_value - value);

        if(this_diff <= max_diff){
            max_diff = this_diff;
            i_choice = i;
        }
    }

    // change index
    i_choice += direction;
    // wrap around?
    if(i_choice < 0) i_choice = n_choices - 1;
    else if(i_choice >= n_choices) i_choice = 0;

    // change value
    value = pgm_read_word_near(choices + i_choice);
}

void IntervalItem::renderValue(void){
    clear();
    lcd.setCursor(column + l_label + 1, line);
    l_value = 0;

    int days, weeks;
    int number;
    const char *unit;
    
    // TODO: move to globals
    static const char h[] PROGMEM = "ur";
    static const char d[] PROGMEM = "dni";
    static const char t1[] PROGMEM = "teden";
    static const char t2[] PROGMEM = "tedna";
    static const char t3[] PROGMEM = "tedne";

    days = value / 24;
    weeks = days / 7;

    if(weeks > 0){
        number = weeks;
        if(number > 2) unit = t3;
        else if(number > 1) unit = t2;
        else unit = t1;
    }
    else if(days > 1){
        number = days;
        unit = d;
    }
    else{
        number = value;
        unit = h;
    }

    l_value = lcd.print(number);
    l_value += pgm_to_lcd(line, column + l_label + 1 + l_value, unit);
};

void DurationItem::renderValue(void){
    clear();
    lcd.setCursor(column + l_label + 1, line);
    l_value = 0;

    if(value < 120){
        l_value += lcd.print(value);
        l_value += lcd.print('s');
    }
    else{
        l_value += lcd.print(value/60);
        l_value += lcd.print(F("min"));
    }
}
