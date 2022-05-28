#include "button.h"
#include "menu.h"
#include "globals.h"


// Text
const char active_label[] PROGMEM = "Vklop";

// interval in hours
const char interval_label[] PROGMEM = "Zalij na";
const int intervals[] PROGMEM = {
    12, 24, 2*24, 3*24, 4*24, 5*24, 6*24, // 0.5, 1, 2, 3, 4, 5, 6 days
    7*24, 2*7*24, 3*7*24, 4*7*24, // 1, 2, 3, 4 weeks
    -1 // end
};

// valve open duration in seconds
const char duration_label[] PROGMEM = "za";
const int durations[] PROGMEM = {
    1, 2, 3, 4, 5, 10, 15, 20, 30, 40, 50, 60, 90, 120, 180, 240, 300,
    -1
};

// clock
const char time_label[] PROGMEM = "ob";
const char clock_point[] PROGMEM = ":";
const char date_point[] PROGMEM = ".";

// servo
const char servo_min_label[] PROGMEM = "Min. kot";
const char servo_max_label[] PROGMEM = "Max. kot";
const char servo_zero_label[] PROGMEM = "Pozicija #1";

Menu::Menu(
    Button *b_prev, Button *b_next, Button *b_dec, Button *b_inc,
    Screen **s, int n)
{
    button_prev = b_prev;
    button_next = b_next;
    button_dec = b_dec;
    button_inc = b_inc;

    screens = s;
    n_screens = n;
    i_active = -1;
    
    t_touched = millis();
};

bool Menu::quit(void){
    i_active = -1;
    lcd.clear();

    // save to EEPROM
    for(int i = 0; i < n_screens; i++){
        screens[i]->save();
    }

    return false;
}

bool Menu::check(void){
    // if no buttons were pressed, return false if the menu has timed out.
    // if a button was pressed, check if the menu is already shown:
    //   - if not shown, show the first (or the last) item
    //   - if shown, send a next() (od previous()) command to the current item:
    //      - if current item returns true, return true and don't change anything
    //      - if current item returns false, go to the next (previous) item and return true;

    // see which buttons were pressed;
    bool b_next, b_prev, b_inc, b_dec;
    b_prev = button_prev->uniquePress();
    b_next = button_next->uniquePress();
    b_dec = button_dec->uniquePress();
    b_inc = button_inc->uniquePress();

    // if none of the buttons has been pressed, check if the menu has timed out
    if(!(b_next || b_prev || b_inc || b_dec)){
        if(i_active == -1)
            return false; // there's nothing going on anyway
        else if(millis() - t_touched > M_TIMEOUT)
            return quit(); // timeout! quit
        else
            return true;
    }
    else{
        // a button has been pressed, don't quit the menu
        t_touched = millis(); // reset the timeout

        if(i_active == -1){
            // the menu is currently not shown, show the first (or last) item
            if(b_prev){
                i_active = n_screens - 1;
                screens[i_active]->show(false); // start from the end
            }
            else if(b_next){
                i_active = 0;
                screens[i_active]->show(true); // start from the first section of this item
            }
        }
        else{
            // the menu is shown already, send a next/previous to current item
            if(b_next){
                // navigate() returns false if next/previous screen should be displayed
                if (!screens[i_active]->navigate(1)){
                    if (++i_active == n_screens) return quit();

                    screens[i_active]->hide();
                    screens[i_active]->show(true);
                }
            }
            else if(b_prev){
                if(!screens[i_active]->navigate(-1)){
                    if(--i_active < 0) return quit();
                
                    screens[i_active]->hide();
                    screens[i_active]->show(false);
                }
            }
            else if(b_inc) screens[i_active]->change(1);
            else if(b_dec) screens[i_active]->change(-1);
        }

        return true;
    }
}
