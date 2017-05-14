/*####################################################################
 FILE: ds1307.h
 VERSION: 1.0
 PURPOSE: Real Time Clock module with DS1307 library for Arduino

 HISTORY:
 Mirko Prosseda - Original version (23/06/2013)
#######################################################################*/


#ifndef ds1307_h
#define ds1307_h

#include "Arduino.h"

#define address B01101000


class ds1307
{
private:
    void setRegister(uint8_t reg, uint8_t value);      // Set a value into the register
    void setBCDtoRegister(uint8_t reg, uint8_t value); // Set a BCD value into the register
public:
    uint8_t getRegister(uint8_t reg);                  // Return the value of an internal register
    void resume();                                     // Turn on the internal clock
    void standby();                                    // Turn off the internal clock
    void getDate(uint8_t *values);                     // Read DS1307 data
    void setSeconds(uint8_t seconds);                  // Set seconds
    void setMinutes(uint8_t minutes);                  // Set minutes
    void setHours(uint8_t hours);                      // Set hours
    void setDow(uint8_t dow);                          // Set the day of the week
    void setData(uint8_t data);                        // Set the data
    void setMonth(uint8_t month);                      // Set the month
    void setYear(uint8_t year);                        // Set the year
};
#endif
