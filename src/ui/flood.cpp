#include <Arduino.h>

#include "outlet.h"
#include "display.h"
#include "ui/menu.h"
#include "ui/flood.h"
#include "ui/settings.h"

void FloodMenu::begin(void){
    n_screens = 1;
    screens = new Screen *[n_screens];
    screens[0] = new FloodScreen();
}

FloodScreen::FloodScreen(void){
    n_items = 3;
    items = new Item *[n_items];
    // Zalij takoj
    // Teglc: <1>
    // Limit: <duration>
    // Vklop: <x>

    items[0] = new Item(outlet_label, 1, 2, 1, false, (char)0, 1, N_OUTLETS);
    items[1] = new DurationItem(duration_label, 2, 2, 5, durations);
    items[2] = new BoolItem(active_label, 3, 2, false);
}

void FloodScreen::show(bool forward){
    lcd.setCursor(0, 0);
    lcd.print(F("Poplavi"));

    Screen::show(forward);
}

void FloodScreen::change(int direction){
    Screen::change(direction);

    // open the outlet at once
    if(i_item == 2){
        if(items[2]->getValue() > 0){
            // the value in in ms
            outlets[items[0]->getValue() - 1]->flood((unsigned long)items[1]->getValue());
        }

        // make the item inactive again
        items[2]->setValue(0);
        items[2]->renderValue();
        items[2]->activate();
    }
}

///
/// Globals
///
FloodMenu flood_menu;