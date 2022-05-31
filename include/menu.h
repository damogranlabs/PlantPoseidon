#ifndef _MENU_H
#define _MENU_H

#include <Arduino.h>
#include <hd44780.h>
#include <EEPROM.h>
#include <math.h>

#include "outlet.h"
#include "button.h"

#define M_TIMEOUT 30000 // go to default item in the menu after

// Menu texts
extern unsigned char arrow_left[8];
extern unsigned char arrow_right[8];
extern unsigned char bool_on[8];
extern unsigned char bool_off[8];

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

// Menu classes:
class Menu;   // a collection of Screens
class Screen; // a collection of Items

class Item;
class BoolItem;
class ChoiceItem;
class IntervalItem;
class DurationItem;

class Menu
{
public:
    Menu(Button *b_prev, Button *b_next, Button *b_dec, Button *b_inc,
         Screen **s, int n_screens);

    bool check(void); // checks what happened and 'sends a message' to current screen

private:
    bool quit(void); // stores data to EEPROM

    Button *button_prev, *button_next, *button_dec, *button_inc;

    Screen **screens;
    int i_active, n_screens; // index of current screen, total number of screens

    unsigned long t_touched; // time the last button was pressed
};

class Screen
{
public:
    virtual void show(bool forward);
    virtual void hide(void);

    bool navigate(int direction);
    virtual void change(int direction);
    virtual void save(void) = 0;

protected:
    Item **items;
    int n_items, i_item{0}; // number of items and index of active one
};

class OutletScreen : public Screen
{
public:
    OutletScreen(Outlet *outlet);
    void show(bool forward);
    void save(void); // saves to EEPROM
private:
    const char *title;
    Outlet *outlet; // outlet currently shown in this screen
};

class ClockScreen : public Screen
{
public:
    ClockScreen();

    void show(bool end_first);
    void save(void){};
};

class ServoScreen : public Screen
{
public:
    ServoScreen();

    void change(int direction);

    void show(bool end_first);
    void save(void);
};

class Item // a generic integer item with label, unit and optional padding
{
public:
    // used by 'custom' items with overridden renderValue/change
    Item(const char *label, int line, int column, int value);
    // generic items
    Item(const char *label, int line, int column, int value,
         bool pad, char unit, int low_limit, int high_limit);

    virtual void show(void);

    virtual void renderValue(void); // (re)draw the value (depends on item type)
    void clear(void);
    void activate(void);                // add increase/decrease markers
    virtual void change(int direction); // value +/-
    void deactivate(void);              // remove the markers

    int getValue(void) { return value; };
    void setValue(int v) { value = v; };

protected:
    // lcd stuff
    const char *label;
    int line, column;

    int value{0};
    int l_label{0}, l_value{0}; // current length of displayed label/value

    bool pad{false};
    char unit{(char)0};
    int low_limit{0}, high_limit{0};
};

class BoolItem : public Item
{
public:
    BoolItem(const char *label, int line, int column, int value) : Item(label, line, column, value, false, (char)0, 0, 1) { l_value = 1; };

    void renderValue(void);
};

class ChoiceItem : public Item
{
public:
    ChoiceItem(const char *label, int line, int column, int value, const int *choices);
    virtual void change(int direction);
    virtual void renderValue(void) = 0;

private:
    const int *choices;
    int n_choices{0}, i_choice{0};
};

class IntervalItem : public ChoiceItem
{
public:
    using ChoiceItem::ChoiceItem;
    void renderValue(void);
    void change(int direction)
    {
        ChoiceItem::change(direction);
        renderValue();
        activate();
    };
};

class DurationItem : public ChoiceItem
{
public:
    using ChoiceItem::ChoiceItem;
    void renderValue(void);
    void change(int direction)
    {
        ChoiceItem::change(direction);
        renderValue();
        activate();
    };
};

///
/// Globals
///
// number of menu screens: outlets + clock + servo
#define N_SCREENS (N_OUTLETS + 2)

extern Screen *screens[N_SCREENS];
extern Menu menu;

#endif // _MENU_H
