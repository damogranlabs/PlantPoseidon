#include "button.h"
#include "menu.h"
#include "display.h"

///
/// Classes and methods
///
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

bool Menu::quit(void)
{
    i_active = -1;
    lcd.clear();

    // save to EEPROM
    for (int i = 0; i < n_screens; i++)
    {
        screens[i]->save();
    }

    return false;
}

bool Menu::check(void)
{
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
    if (!(b_next || b_prev || b_inc || b_dec))
    {
        if (i_active == -1)
            return false; // there's nothing going on anyway
        else if (millis() - t_touched > M_TIMEOUT)
            return quit(); // timeout! quit
        else
            return true;
    }
    else
    {
        // a button has been pressed, don't quit the menu
        t_touched = millis(); // reset the timeout

        if (i_active == -1)
        {
            // the menu is currently not shown, show the first (or last) item
            if (b_prev)
            {
                i_active = n_screens - 1;
                screens[i_active]->show(false); // start from the end
            }
            else if (b_next)
            {
                i_active = 0;
                screens[i_active]->show(true); // start from the first section of this item
            }
        }
        else
        {
            // the menu is shown already, send a next/previous to current item
            if (b_next)
            {
                // navigate() returns false if next/previous screen should be displayed
                if (!screens[i_active]->navigate(1))
                {
                    if (++i_active == n_screens)
                        return quit();

                    screens[i_active]->hide();
                    screens[i_active]->show(true);
                }
            }
            else if (b_prev)
            {
                if (!screens[i_active]->navigate(-1))
                {
                    if (--i_active < 0)
                        return quit();

                    screens[i_active]->hide();
                    screens[i_active]->show(false);
                }
            }
            else if (b_inc)
                screens[i_active]->change(1);
            else if (b_dec)
                screens[i_active]->change(-1);
        }

        return true;
    }
}

///
/// Globals
///
Screen *screens[N_SCREENS];
Menu menu(&up, &down, &left, &right, screens, N_SCREENS);
