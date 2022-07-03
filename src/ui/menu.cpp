#include "outlet.h"
#include "ui/menu.h"
#include "display.h"
#include "util.h"
#include "io.h"

///
/// Menu
///
// bool Menu::is_active(void){
//     if(i_active >= 0){
//         if(millis() - t_touched > MENU_TIMEOUT){
//             quit();
//         }
//     }

//     return i_active >= 0;
// }

// void Menu::enter(void){
//     // show the first screen
//     i_active = 0;
//     t_touched = millis();

//     lcd.clear();
//     screens[i_active]->show(true);
// }

// void Menu::quit(void){
//     // save and clear
//     for(int i = 0; i < n_screens; i++){
//         screens[i]->save();
//     }
        
//     i_active = -1;
//     lcd.clear();
// }

// void Menu::toggle(void){
//     if(!is_active()) enter();
//     else quit();
// }

// void Menu::navigate(int direction){
//     if(!is_active()) return;

//     // screen->navigate() will activate the next/previous item and return true,
//     // unless the last/first item was already active;
//     // in that case, go to next/previous screen
//     if(!screens[i_active]->navigate(direction)){
//         // show the new screen
//         lcd.clear();
//         i_active = contain(i_active + direction, 0, n_screens-1);
//         screens[i_active]->show(direction >= 0);
//     }

//     t_touched = millis();
// }

// void Menu::change(int direction){
//     if(!is_active()) return;
    
//     screens[i_active]->change(direction);
//     t_touched = millis();
// }

// ///
// /// Screens
// ///
// /************** Base **************/
// void Screen::show(bool forward){
//     // show the items
//     if (items == NULL)
//         return;

//     for (int i = 0; i < n_items; i++){
//         items[i]->show();
//     }

//     // activate first item if forward and vice versa
//     if (forward) i_item = 0;
//     else i_item = n_items - 1;

//     items[i_item]->activate();
// }

// bool Screen::navigate(int direction){
//     // deactivate current item and activate the next one;
//     items[i_item]->deactivate();

//     i_item += direction;

//     // return false if we're out of this screen
//     if (i_item < 0 || i_item >= n_items)
//         return false;

//     items[i_item]->activate();
//     return true;
// }

// void Screen::change(int direction){
//     items[i_item]->change(direction);
// }