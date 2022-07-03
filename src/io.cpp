#include <Arduino.h>

#include <Wire.h>
#include <hd44780.h>

#include "pinout.h"
#include "io.h"
#include "display.h"

#include "ui/settings.h"
#include "ui/flood.h"

void setup_serial(void){
    Serial.begin(9600);
    while (!Serial)
        ;
}

void setup_i2c(void){
    Wire.begin();
}

void setup_gpio(
    OneButton *btn_setup,
    OneButton *btn_flood_stop,
    OneButton *btn_prev,
    OneButton *btn_next){
    pinMode(LED_BUILTIN, OUTPUT);

    // btn_setup->attachClick(on_btn_setup_click);
    // btn_flood_stop->attachClick(on_btn_flood_stop_click);
    // btn_prev->attachClick(on_btn_prev_click);
    // btn_next->attachClick(on_btn_next_click);
}

void setup_enc(void){
    pinMode(ENC_A_PIN, INPUT_PULLUP);
    pinMode(ENC_B_PIN, INPUT_PULLUP);
}

// void update_inputs(void){
//     // buttons
//     btn_flood_stop.tick();
//     btn_next.tick();
//     btn_setup.tick();
//     btn_prev.tick();

//     // encoder
//     static int e_this, e_prev = 0, direction;
//     e_this = enc.read() / 4;
//     if(e_this != e_prev){
//         touch();

//         direction = (e_this - e_prev)/abs(e_this - e_prev);
//         e_prev = e_this;
        
//         // TODO: do something with all that if()ing
//         if(settings_menu.is_active()) settings_menu.change(direction);
//         else if(flood_menu.is_active()) flood_menu.change(direction);
//     }
// }

// void on_btn_flood_stop_click(void){
//     touch();

//     if(!settings_menu.is_active()) flood_menu.toggle();
// }

// void on_btn_next_click(void){
//     touch();

//     if(settings_menu.is_active()) settings_menu.navigate(1);
//     else if(flood_menu.is_active()) flood_menu.navigate(1);
// }

// void on_btn_setup_click(void){
//     touch();

//     if(!flood_menu.is_active()) settings_menu.toggle();
// }

// void on_btn_prev_click(void){
//     touch();
    
//     if(settings_menu.is_active()) settings_menu.navigate(-1);
//     else if(flood_menu.is_active()) flood_menu.navigate(-1);
// }