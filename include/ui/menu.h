#ifndef _MENU_H
#define _MENU_H

#include <Arduino.h>
#include <hd44780.h>
#include <EEPROM.h>
#include <math.h>

#include "outlet.h"

#define MENU_TIMEOUT 15000

// class Menu; // a container/handler for Screens
//     class Screen; // a container for Items
//         class Item; // generic numeric value
//         class BoolItem; // yes/no
//         class ChoiceItem; // named numeric value

// ///
// /// Menu
// ///
// class Menu
// {
// public:
//     // init: Menu*() constructor is not the right place for initialization;
//     // like other libraries, use begin() method or whatever
//     virtual void begin(void) = 0;

//     // button press events
//     void enter(void);
//     void quit(void);
//     bool is_active(void); // check/timeout
//     void toggle(void); // enter/quit the menu
//     void navigate(int direction);
//     void change(int direction);
// protected:
//     int n_screens{};
//     Screen **screens;
    
//     int i_active{-1}; // index of currently active screen; if -1, the menu is not shown
//     unsigned long t_touched{}; // time the last button was pressed
// };

// ///
// /// Screen
// ///
// class Screen
// {
// public:
//     virtual void show(bool forward);
//     bool navigate(int direction);
//     virtual void change(int direction);
//     virtual void save(void) = 0;
// protected:
//     Item **items;
//     int n_items, i_item{0}; // number of items and index of active one
// };

// ///
// /// Item base and generic types
// ///
// class Item // a generic integer item with label, unit and optional padding
// {
// public:
//     // used by 'custom' items with overridden renderValue/change
//     Item(const char *label, int line, int column, int value);
//     // generic items
//     Item(const char *label, int line, int column, int value,
//          bool pad, char unit, int low_limit, int high_limit);

//     virtual void show(void);

//     virtual void renderValue(void); // (re)draw the value (depends on item type)
//     void clear(void);
//     void activate(void);                // add increase/decrease markers
//     virtual void change(int direction); // value +/-
//     void deactivate(void);              // remove the markers

//     int getValue(void) { return value; };
//     void setValue(int v) { value = v; };

// protected:
//     // lcd stuff
//     const char *label;
//     int line, column;

//     int value{0};
//     int l_label{0}, l_value{0}; // current length of displayed label/value

//     bool pad{false};
//     char unit{(char)0};
//     int low_limit{0}, high_limit{0};
// };

// class BoolItem : public Item
// {
// public:
//     BoolItem(const char *label, int line, int column, int value) : Item(label, line, column, value, false, (char)0, 0, 1) { l_value = 1; };

//     void renderValue(void);
// };

// class ChoiceItem : public Item
// {
// public:
//     ChoiceItem(const char *label, int line, int column, int value, const int *choices);
//     virtual void change(int direction);
//     virtual void renderValue(void) = 0;

// private:
//     const int *choices;
//     int n_choices{0}, i_choice{0};
// };

#endif // _MENU_H
