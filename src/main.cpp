#include <Arduino.h>
#include <LiquidCrystal.h>

#include "pinout.h"

#include "button.h"
#include "menu.h"
#include "outlet.h"
#include "util.h"

#include "globals.h"

void setup() {
    // display
    lcd.begin(20, 4);
    lcd.clear();
    lcd.createChar(CC_LEFT, arrow_left);
    lcd.createChar(CC_RIGHT, arrow_right);
    lcd.createChar(CC_ON, bool_on);
    lcd.createChar(CC_OFF, bool_off);

    // menu
    int i;
    for(i = 0; i < N_OUTLETS; i++){
        outlets[i] = new Outlet(i);
        screens[i] = new OutletScreen(outlets[i]);
    }
    screens[N_OUTLETS] = new ClockScreen();

    // mechanics
    servo.attach(P_SERVO);
}

void loop() {
    if(menu.check()){
        // don't do anything while the user is deciding what to do
        delay(50); // do something with debounce
        return;
    }
    
    // check if there's anything to water
    lcd.setCursor(0, 0);
    lcd.print(millis()/1000);
    
    // servo.move(-90);
    // delay(1000);
    // servo.move(0);
    // delay(1000);
    // servo.move(45);
    // delay(1000);
    // servo.move(73);
    // delay(1000);
    easeMove(45);
    delay(1000);
    easeMove(90);
    delay(1000);
    easeMove(0);
    delay(1000);
    easeMove(180);
    delay(1000);
    easeMove(90);
    delay(1000);
    easeMove(80);
    delay(1000);
    easeMove(60);
    delay(1000);
}