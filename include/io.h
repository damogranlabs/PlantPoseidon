#ifndef __IO_HPP__
#define __IO_HPP__

#include <Arduino.h>
#include <Print.h>

#include <OneButton.h>

#include <Encoder.h>

void setup_serial(void);
void setup_i2c(void);
void setup_gpio(void);
void setup_enc(void);

void update_btn_states(void);

void on_btn_flood_stop_click(void);
void on_btn_next_click(void);
void on_btn_setup_click(void);
void on_btn_prev_click(void);

extern OneButton btn_flood_stop;
extern OneButton btn_flood_stop;
extern OneButton btn_flood_stop;
extern OneButton btn_flood_stop;

extern Encoder enc;

#endif
