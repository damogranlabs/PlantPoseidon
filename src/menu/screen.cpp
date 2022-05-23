#include <Arduino.h>

#include "globals.h"
#include "menu.h"
#include "progmem.h"

/************** Base **************/
void Screen::show(bool forward){
    // show the items
    if(items == NULL) return;

    for(int i = 0; i < n_items; i++){
        items[i]->show();
    }

    // activate first item if forward and vice versa
    if(forward) i_item = 0;
    else i_item = n_items - 1;

    items[i_item]->activate();
}

void Screen::hide(void){
    lcd.clear();
}

bool Screen::navigate(int direction){
    // deactivate current item and activate the next one;
    items[i_item]->deactivate();

    i_item += direction;

    // return false if we're out of this screen
    if(i_item < 0 || i_item >= n_items) return false;

    items[i_item]->activate();
    return true;    
}

void Screen::change(int direction){
    items[i_item]->change(direction);
}

/************** Outlet screen **************/
OutletScreen::OutletScreen(Outlet *o){
    // currently selected outlet
    outlet = o;
    n_items = 4;
    items = new Item * [n_items]; // https://stackoverflow.com/questions/21391089/variable-size-array-of-pointers-c

    items[0] = new BoolItem(active_label, 0, 12, outlet->getSchedule()->enabled ? 1 : 0);
    items[1] = new IntervalItem(interval_label, 1, 0, outlet->getSchedule()->interval, intervals);
    items[2] = new Item(time_label, 2, 0, outlet->getSchedule()->time, true, 'h', 0, 23);
    items[3] = new DurationItem(duration_label, 2, 7, outlet->getSchedule()->duration, durations);
    // immediate

    // TODO
}

void OutletScreen::show(bool forward){
    lcd.setCursor(0, 0);
    lcd.print(F("Rastlina "));
    lcd.print(outlet->getId() + 1);

    Screen::show(forward);
}

void OutletScreen::save(void){
    outlet->updateSchedule(
        items[0]->getValue() != 0,
        items[1]->getValue(),
        items[2]->getValue(),
        items[3]->getValue()
    );
    outlet->save();
}

/************** Clock screen **************/
ClockScreen::ClockScreen(void){
    n_items = 5;
    items = new Item * [n_items];

    // hour and minute
    items[0] = new Item(NULL, 1, 11, 0, true, (char)0, 0, 23);
    items[1] = new Item(clock_point, 1, 15, 0, true, (char)0, 0, 59);

    // day, month, year
    items[2] = new Item(NULL, 2, 4, 1, true, (char)0, 1, 31);
    items[3] = new Item(date_point, 2, 8, 1, true, (char)0, 1, 12);
    items[4] = new Item(date_point, 2, 13, 2022, false, (char)0, 2022, 2052);
}

void ClockScreen::show(bool forward){
    lcd.setCursor(0, 0);
    lcd.print(F("Ura in datum"));

    Screen::show(forward);
}