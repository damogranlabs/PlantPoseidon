#ifndef _FLOOD_H
#define _FLOOD_H

#include "ui/menu.h"

///
/// Menu
///
class FloodMenu : public Menu
{
public:
    void begin(void);
};

class FloodScreen : public Screen
{
public:
    FloodScreen();
    
    void show(bool forward);
    virtual void change(int direction);
    void save(void){ /* nothing to save */ };
};

///
/// Globals
///
extern FloodMenu flood_menu;

#endif