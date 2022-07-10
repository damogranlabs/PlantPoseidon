#include <Arduino.h>
#include <hd44780.h>

#include "io.h"
#include "pinout.h"
#include "display.h"
#include "schedule.h"
#include "outlet.h"
#include "fervo.h"
#include "menus/settings.h"
#include "menus/flood.h"
#include "util.h"

I2CLCD lcd(LCD_ADDR,
    I2Cexp_PCF8574,
    P_LCD_RS, P_LCD_RW, P_LCD_EN,
    P_LCD_D4, P_LCD_D5, P_LCD_D6, P_LCD_D7,
    P_LCD_BL, HIGH);

OneButton btn_flood_stop(BTN_FLOOD_PIN);
OneButton btn_next(BTN_NEXT_PIN);
OneButton btn_setup(BTN_SETUP_PIN);
OneButton btn_prev(BTN_PREV_PIN);

Encoder enc(ENC_B_PIN, ENC_A_PIN);

Outlet *outlets[N_OUTLETS];
Fervo servo;

SettingsMenu settings_menu;
FloodMenu flood_menu;

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
    lcd.begin();
    setup_gpio();
    setup_rtc();
    setup_servo();
    setup_outlets();
    setup_menus();

    lcd.print(F("Bohdej, Kmet"));
    delay(3000);
    lcd.clear();
}

void loop(){
    static int i;

    lcd.check();
    update_inputs();

    // currently dealing with menus?
    if(flood_menu.is_active()) return;
    if(settings_menu.is_active()) return;

    // check if there's anything to water
    for(i = 0; i < N_OUTLETS; i++){
        outlets[i]->check();
    }

    // nothing else to do: show status
    lcd.showStatus();
}