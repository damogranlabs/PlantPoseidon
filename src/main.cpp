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

extern hd44780_I2Cexp lcd;
extern Outlet *outlets[N_OUTLETS];

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
}

void setup_menu_outlets(void)
{
    int i;
    for (i = 0; i < N_OUTLETS; i++)
    {
        screens[i] = new OutletScreen(outlets[i]);
    }
    screens[N_OUTLETS] = new ClockScreen();
    screens[N_OUTLETS + 1] = new ServoScreen();
}

void loop()
{
    if (menu.check())
    {
        // don't do anything while the user is deciding what to do
        delay(50); // do something with debounce
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