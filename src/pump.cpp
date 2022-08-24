#include <Arduino.h>
#include <EEPROM.h>

#include "pinout.h"
#include "globals.h"
#include "pump.h"
#include "util.h"

Pump::Pump(void){
    load();
}

void Pump::load(void){
    // TODO: DRY
    EEPROM.get(ADDR_PUMP_OFFSET, data);

    unsigned long saved_crc;
    EEPROM.get(ADDR_PUMP_OFFSET + sizeof(data), saved_crc);
    unsigned long loaded_crc = crc((uint8_t *)&data, sizeof(data));

    if (saved_crc != loaded_crc){
        memset(&data, 0, sizeof(data));
        data.enabled = false;
        data.delay = 0;
    }
}

void Pump::save(void){
    EEPROM.put(ADDR_PUMP_OFFSET, data);

    unsigned long check = crc((uint8_t *)&data, sizeof(data));
    EEPROM.put(ADDR_PUMP_OFFSET + sizeof(data), check);
}

bool Pump::start(void){
    unsigned long t_end = millis() + data.delay * 1000;

    if(data.enabled){
        digitalWrite(PUMP_PIN, HIGH);
        while((millis() < t_end) && (digitalRead(BTN_FLOOD_PIN) == HIGH)){ };
    }

    return millis() >= t_end;
}

void Pump::stop(void){
    if(data.enabled){
        digitalWrite(PUMP_PIN, LOW);
    }
}