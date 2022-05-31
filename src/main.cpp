#include <Arduino.h>

#include <hd44780.h>

#include "pinout.h"
#include "io.h"
#include "button.h"
#include "display.h"
#include "menu.h"
#include "outlet.h"
#include "fervo.h"
#include "util.h"

static void setup_menu_outlets(void);

extern OneButton btn_flood_stop, btn_next, btn_setup, btn_prev;
extern hd44780_I2Cexp lcd;
extern Encoder enc;
extern Outlet *outlets[N_OUTLETS];
extern Screen *screens[N_SCREENS];
extern Menu menu;

void setup()
{
    setup_i2c();
    setup_lcd();
    setup_gpio();
    setup_enc();
    setup_servo();
    setup_menu_outlets();

    lcd.print("System initialized.");
    delay(1000);
    lcd.clear();
}

void setup_menu_outlets(void)
{
    int i;
    for (i = 0; i < N_OUTLETS; i++)
    {
        outlets[i] = new Outlet(i);
        screens[i] = new OutletScreen(outlets[i]);
    }
    screens[N_OUTLETS] = new ClockScreen();
    screens[N_OUTLETS + 1] = new ServoScreen();
}

void loop()
{
    update_btn_states();

    /* Example
    lcd.setCursor(0, 0);
    lcd.print(millis() / 1000);
    lcd.setCursor(0, 1);
    lcd.print(enc.read() / 4); // this library will count 4 changes on pin A and B of rotary encoder for each shaft ident.
    */

    if (menu.check())
    {
        // don't do anything while the user is deciding what to do
        // TODO don't debounce manually, use OneButton
        // delay(50); // do something with debounce
        return;
    }

    /*
    // check if there's anything to water
    lcd.setCursor(0, 0);
    lcd.print(millis() / 1000);

    servo.easeMove(0);
    delay(1000);
    servo.easeMove(22);
    delay(1000);
    servo.easeMove(45);
    delay(1000);
    servo.easeMove(90);
    delay(1000);
    servo.easeMove(180);
    delay(1000);
    */
}