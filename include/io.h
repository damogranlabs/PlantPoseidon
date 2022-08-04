#ifndef __IO_HPP__
#define __IO_HPP__

#include <Arduino.h>
#include <OneButton.h>

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

void setup_serial(void);
void setup_i2c(void);
void setup_gpio(void);
void setup_enc(void);

void update_inputs(void);

void on_btn_flood_stop_click(void);
void on_btn_next_click(void);
void on_btn_setup_click(void);
void on_btn_prev_click(void);

extern OneButton btn_flood_stop;
extern OneButton btn_next;
extern OneButton btn_setup;
extern OneButton btn_prev;

extern Encoder enc;

#endif
