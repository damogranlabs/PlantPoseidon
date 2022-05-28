#include <Arduino.h>
#include <LiquidCrystal.h>

#include "pinout.h"

#include "button.h"
#include "display.h"
#include "menu.h"
#include "outlet.h"
#include "fervo.h"
#include "util.h"

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
    screens[N_OUTLETS+1] = new ServoScreen();

    // mechanics
    servo.attach(P_SERVO);
    servo.write(90);
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
    
    servo.easeMove(0);
    delay(1000);
    servo.easeMove(22);
    delay(1000);
    servo.easeMove(45);
    delay(1000);
    servo.easeMove(90);
    delay(1000);
    servo.easeMove(180);
    delay(1000);

}