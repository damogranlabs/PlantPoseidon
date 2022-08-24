#ifndef _PUMP_H
#define _PUMP_H

#include <Arduino.h>

struct pump_data
{
    bool enabled;
    uint8_t delay;
};

class Pump
{
public:
    Pump(void);

    bool start(void);
    void stop(void);

    bool getEnabled(void){ return data.enabled; };
    void setEnabled(bool enabled){ data.enabled = enabled; };

    uint8_t getDelay(void){ return data.delay; };
    void setDelay(uint8_t delay){ data.delay = delay; };

    void load(void);
    void save(void);
private:
    struct pump_data data;
};

#endif