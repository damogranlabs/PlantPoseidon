#include <inttypes.h>
#include <math.h>

///
/// Date/time
///
bool isLeapYear(uint16_t year){
    if(year % 400 == 0) return true;
    if(year % 100 == 0) return false;
    return (year % 4 == 0);
}

uint8_t daysInMonth(uint16_t year, uint8_t month){
    switch(month){
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            if(isLeapYear(year)) return 29;
            return 28;
        default:
            break;
    }

    return 31;
}

uint8_t validateDay(uint16_t year, uint8_t month, uint8_t day){
    // clip the date for given month; returns a 'valid' 'day'
    uint8_t dmax = daysInMonth(year, month);
    
    return (day < dmax) ? day : dmax;
}