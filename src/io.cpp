#include <Arduino.h>

#include <Wire.h>
#include <hd44780.h>

#include "pinout.h"
#include "io.h"
#include "display.h"

Encoder enc(ENC_B_PIN, ENC_A_PIN);

/*
OneButton btn_flood_stop(BTN_FLOOD_PIN);
OneButton btn_next(BTN_NEXT_PIN);
OneButton btn_setup(BTN_SETUP_PIN);
OneButton btn_prev(BTN_PREV_PIN);
*/

void setup_i2c(void)
{
  Wire.begin();
}

void setup_gpio(void)
{
  pinMode(LED_BUILTIN, OUTPUT);

  // buttons -> use OneButton library
  // pinMode(BTN_FLOOD_PIN, INPUT);
  // pinMode(BTN_NEXT_PIN, INPUT);
  // pinMode(BTN_SETUP_PIN, INPUT);
  // pinMode(BTN_PREV_PIN, INPUT);
  /*
  btn_flood_stop.attachClick(on_btn_flood_stop_click);
  btn_next.attachClick(on_btn_next_click);
  btn_setup.attachClick(on_btn_setup_click);
  btn_prev.attachClick(on_btn_prev_click);
  */
}

void setup_enc(void)
{
  pinMode(ENC_A_PIN, INPUT_PULLUP);
  pinMode(ENC_B_PIN, INPUT_PULLUP);
}

/*
void on_btn_flood_stop_click(void)
{
  lcd.setCursor(0, 1);
  lcd.print("F");
}

void on_btn_next_click(void)
{
  lcd.setCursor(0, 1);
  lcd.print("N");
}

void on_btn_setup_click(void)
{
  lcd.setCursor(0, 1);
  lcd.print("S");
}

void on_btn_prev_click(void)
{
  lcd.setCursor(0, 1);
  lcd.print("P");
}
*/