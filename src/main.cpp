#include <Arduino.h>
#include <hd44780.h>

#include "pinout.h"
#include "io.h"
#include "display.h"
#include "schedule.h"
#include "outlet.h"
#include "fervo.h"
#include "ui/settings.h"
#include "ui/flood.h"
#include "util.h"

void setup_outlets(void){
    for (int i = 0; i < N_OUTLETS; i++){
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
    setup_rtc();
    setup_enc();
    setup_servo();
    setup_outlets();
    setup_menus();

    lcd.print(F("Bohdej, Kmet"));
    delay(3000);
    lcd.clear();
}

void loop(){
    static int i;

    update_inputs();
    update_backlight();

    // currently dealing with menus?
    if(flood_menu.is_active()) return;
    if(settings_menu.is_active()) return;

    // check if there's anything to water
    for(i = 0; i < N_OUTLETS; i++){
        outlets[i]->check();
    }

    // nothing else to do: show status
    show_status();
}