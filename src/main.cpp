#include <Arduino.h>
#include <hd44780.h>

#include "pinout.h"

#include "display.h"
#include "io.h"
#include "schedule.h"
#include "fervo.h"
// #include "outlet.h"
// #include "ui/settings.h"
// #include "ui/flood.h"
#include "util.h"

///
/// Globals
///
// Display
I2CLCD lcd(
    LCD_ADD, // addr
    I2Cexp_PCF8574, // chiptype
    P_LCD_RS, P_LCD_RW, P_LCD_EN, P_LCD_D4, P_LCD_D5, P_LCD_D6, P_LCD_D7, P_LCD_BL,
    HIGH //blLevel
);

// I/O a.k.a. buttons and encoder
OneButton btn_flood_stop(BTN_FLOOD_PIN);
OneButton btn_next(BTN_NEXT_PIN);
OneButton btn_setup(BTN_SETUP_PIN);
OneButton btn_prev(BTN_PREV_PIN);

Encoder enc(ENC_B_PIN, ENC_A_PIN);

// Fervo motor/falve
Fervo servo;


// void setup_outlets(void){
//     for (int i = 0; i < N_OUTLETS; i++){
//         outlets[i] = new Outlet(i);
//     }
// }

// void setup_menus(void){
//     settings_menu.begin();
//     flood_menu.begin();
// }

void setup()
{
    setup_serial();
    setup_i2c();
    setup_lcd(&lcd);
    setup_gpio(&btn_setup, &btn_flood_stop, &btn_prev, &btn_next);
    setup_enc();
    setup_rtc();
    setup_servo(&servo, SERV1_PIN);
    //setup_outlets();
    //setup_menus();

    lcd.print(F("Bohdej, Kmet"));
    delay(3000);
    lcd.clear();
}

void loop(){
    //static int i;

    //update_inputs();
    //update_backlight();

    // currently dealing with menus?
    //if(flood_menu.is_active()) return;
    //if(settings_menu.is_active()) return;

    // check if there's anything to water
    //for(i = 0; i < N_OUTLETS; i++){
    //    outlets[i]->check();
    //}

    // nothing else to do: show status
    //show_status();
}