#include "ui/menu.h"
#include "ui/settings.h"

#include "display.h"
#include "outlet.h"
#include "fervo.h"

#include "util.h"

///
/// Menu
///
SettingsMenu::SettingsMenu(void){
    n_screens = N_OUTLETS + 2;
    screens = new Screen *[n_screens];
}

void SettingsMenu::begin(void){
    for(int i = 0; i < N_OUTLETS; i++){
        screens[i] = new OutletScreen(outlets[i]);
    }
    
    screens[n_screens-2] = new ClockScreen();
    screens[n_screens-1] = new ServoScreen();
}

///
/// Screens
///
/************** Outlet screen **************/
OutletScreen::OutletScreen(Outlet *o)
{
    // currently selected outlet
    outlet = o;
    n_items = 4;
    items = new Item *[n_items]; // https://stackoverflow.com/questions/21391089/variable-size-array-of-pointers-c

    items[0] = new BoolItem(active_label, 1, 2, outlet->getSchedule()->enabled ? 1 : 0);
    items[1] = new IntervalItem(interval_label, 2, 2, outlet->getSchedule()->interval, intervals);
    items[2] = new Item(time_label, 3, 2, outlet->getSchedule()->time, true, 'h', 0, 23);
    items[3] = new DurationItem(duration_label, 3, 9, outlet->getSchedule()->duration, durations);
}

void OutletScreen::show(bool forward)
{
    lcd.setCursor(0, 0);
    lcd.print(F("Teglc "));
    lcd.print(outlet->getId() + 1);

    Screen::show(forward);
}

void OutletScreen::save(void)
{
    outlet->updateSchedule(
        items[0]->getValue() != 0,
        items[1]->getValue(),
        items[2]->getValue(),
        items[3]->getValue());
    outlet->save();
}

/************** Clock screen **************/
ClockScreen::ClockScreen(void)
{
    n_items = 5;
    items = new Item *[n_items];

    // hour and minute
    items[0] = new Item(NULL, 1, 1, 0, true, (char)0, 0, 23);
    items[1] = new Item(clock_point, 1, 5, 0, true, (char)0, 0, 59);

    // day, month, year
    items[2] = new Item(NULL, 2, 1, 1, true, (char)0, 1, 31);
    items[3] = new Item(date_point, 2, 5, 1, true, (char)0, 1, 12);
    items[4] = new Item(date_point, 2, 10, 2022, false, (char)0, 2022, 2122);
}

void ClockScreen::show(bool forward)
{
    lcd.setCursor(0, 0);
    lcd.print(F("Ura in datum"));

    Screen::show(forward);
}

/************** Servo screen **************/
ServoScreen::ServoScreen(void)
{
    n_items = 3;
    items = new Item *[n_items];

    items[0] = new Item(servo_min_label, 1, 2, servo.getMin(), true, (char)0, 100, 3000);
    items[1] = new Item(servo_max_label, 2, 2, servo.getMax(), true, (char)0, 100, 3000);
    items[2] = new Item(servo_zero_label, 3, 2, servo.getZero(), true, (char)0, 100, 3000);
};

void ServoScreen::show(bool forward)
{
    lcd.setCursor(0, 0);
    lcd.print(F("Servo"));

    Screen::show(forward);
}

void ServoScreen::change(int direction)
{
    Screen::change(direction * 10);
    servo.easeMove(items[i_item]->getValue());
};

void ServoScreen::save(void)
{
    servo.setMin(items[0]->getValue());
    servo.setMax(items[1]->getValue());
    servo.setZero(items[2]->getValue());
    servo.save();
}

///
/// Items
///
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


///
/// Globals
///
SettingsMenu settings;