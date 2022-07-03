#ifndef __IO_HPP__
#define __IO_HPP__

#include <Arduino.h>
#include <Print.h>
#include <OneButton.h>
#include <Encoder.h>

void setup_serial(void);
void setup_i2c(void);
void setup_gpio(
    OneButton *btn_setup,
    OneButton *btn_flood_stop,
    OneButton *btn_prev,
    OneButton *btn_next);
void setup_enc(void);

// void update_inputs(void);

// void on_btn_flood_stop_click(void);
// void on_btn_next_click(void);
// void on_btn_setup_click(void);
// void on_btn_prev_click(void);

#endif
