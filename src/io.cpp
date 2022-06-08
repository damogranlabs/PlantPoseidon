#include <Arduino.h>

#include <Wire.h>
#include <hd44780.h>

#include "pinout.h"
#include "io.h"
#include "display.h"

#include "ui/settings.h"
#include "ui/flood.h"

OneButton btn_flood_stop(BTN_FLOOD_PIN);
OneButton btn_next(BTN_NEXT_PIN);
OneButton btn_setup(BTN_SETUP_PIN);
OneButton btn_prev(BTN_PREV_PIN);

Encoder enc(ENC_B_PIN, ENC_A_PIN);

void setup_serial(void)
{
    Serial.begin(9600);
    while (!Serial)
        ;
}

void setup_i2c(void)
{
    Wire.begin();
}

void setup_gpio(void)
{
    pinMode(LED_BUILTIN, OUTPUT);

    btn_flood_stop.attachClick(on_btn_flood_stop_click);
    btn_next.attachClick(on_btn_next_click);
    btn_setup.attachClick(on_btn_setup_click);
    btn_prev.attachClick(on_btn_prev_click);
}

void setup_enc(void)
{
    pinMode(ENC_A_PIN, INPUT_PULLUP);
    pinMode(ENC_B_PIN, INPUT_PULLUP);
}

void update_inputs(void)
{
    // buttons
    btn_flood_stop.tick();
    btn_next.tick();
    btn_setup.tick();
    btn_prev.tick();

    // encoder
    static int e_this, e_prev = 0;
    e_this = enc.read() / 4;
    if(e_this != e_prev){
        settings.change((e_this - e_prev)/abs(e_this - e_prev));
        e_prev = e_this;
    }
}

void on_btn_flood_stop_click(void)
{
    lcd.setCursor(19, 3);
    lcd.print("F");
}

void on_btn_next_click(void)
{
    settings.navigate(1);
}

void on_btn_setup_click(void)
{
    settings.go();
}

void on_btn_prev_click(void)
{
    settings.navigate(-1);
}