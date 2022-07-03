#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "outlet.h"
#include "ui/menu.h"

///
/// Menu
///
// class SettingsMenu : public Menu
// {
// public:
//     SettingsMenu();
//     void begin(void);
// };

// ///
// /// Screens
// ///
// class OutletScreen : public Screen
// {
// public:
//     OutletScreen(Outlet *o);
    
//     void show(bool forward);
//     void save(void);
// private:
//     Outlet *outlet;
// };

// class ClockScreen : public Screen
// {
// public:
//     ClockScreen();

//     void show(bool end_first);
//     void save(void);
// };

// class ServoScreen : public Screen
// {
// public:
//     ServoScreen();

//     void change(int direction);

//     void show(bool end_first);
//     void save(void);
// };

// ///
// /// Items
// ///
// class IntervalItem : public ChoiceItem
// {
// public:
//     using ChoiceItem::ChoiceItem;
//     void renderValue(void);
//     void change(int direction)
//     {
//         ChoiceItem::change(direction);
//         renderValue();
//         activate();
//     };
// };

// class DurationItem : public ChoiceItem
// {
// public:
//     using ChoiceItem::ChoiceItem;
//     void renderValue(void);
//     void change(int direction)
//     {
//         ChoiceItem::change(direction);
//         renderValue();
//         activate();
//     };
// };

// ///
// /// Globals
// ///
// extern SettingsMenu settings_menu;

#endif