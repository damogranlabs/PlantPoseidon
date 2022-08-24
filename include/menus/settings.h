#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "outlet.h"
#include "menus/menu.h"

///
/// Menu
///
class SettingsMenu : public Menu
{
public:
    SettingsMenu();
    void begin(void);
};

///
/// Screens
///
class OutletScreen : public Screen
{
public:
    OutletScreen(Outlet *o);
    
    void show(bool forward);
    void save(void);
private:
    Outlet *outlet;
};

class ClockScreen : public Screen
{
public:
    ClockScreen();

    void change(int direction);
    void show(bool end_first);
    void save(void);
private:
    // don't re-save the clock if it wasn't adjusted
    bool changed{false};
};

class ServoScreen : public Screen
{
public:
    ServoScreen();

    void change(int direction);
    void show(bool end_first);
    void save(void);
};

class PumpScreen : public Screen
{
public:
    PumpScreen();

    void show(bool end_first);
    void save(void);
};

///
/// Items
///
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

#endif