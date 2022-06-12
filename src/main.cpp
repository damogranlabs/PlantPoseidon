#include <Arduino.h>
#include <hd44780.h>

#include "pinout.h"
#include "io.h"
#include "display.h"
#include "outlet.h"
#include "fervo.h"
#include "ui/settings.h"
#include "ui/flood.h"
#include "util.h"

void setup_outlets(void){
    for (int i = 0; i < N_OUTLETS; i++)
    {
        outlets[i] = new Outlet(i);
    }
}

void setup_menus(void){
    settings_menu.begin();
    flood_menu.begin();
}

void setup()
{
    setup_serial();
    setup_i2c();
    setup_lcd();
    setup_gpio();
    setup_enc();
    setup_servo();
    setup_outlets();
    setup_menus();

    lcd.print("System initialized.");
    delay(1000);
    lcd.clear();
}

void loop()
{
    update_inputs();

    // currently dealing with menus?
    if(flood_menu.is_active()) return;
    if(settings_menu.is_active()) return;

    // show status
    lcd.setCursor(0, 0);
    lcd.print(millis() / 1000);

    // check if there's anything to water
    
    /*


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