/*####################################################################
 FILE: ds1307.cpp
 VERSION: 1.0
 PURPOSE: Real Time Clock module with DS1307 library for Arduino

 HISTORY:
 Mirko Prosseda - Original version (23/06/2013)
#######################################################################*/


#include "ds1307.h"
#include "Wire.h"


// Set a value into the register
void ds1307::setRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(address);                 // address the ds1307
    Wire.write(reg);                                 // point to the selected register
    Wire.write(value);                               // write value to the selected register
    Wire.endTransmission();                          // execute comand
}


// Set a BCD value into the register
void ds1307::setBCDtoRegister(uint8_t reg, uint8_t value)
{
    uint8_t tens = 0;
    tens = value / 10;
    setRegister(reg, ((tens * 16) + (value - (tens * 10))));
}


// Return the value of an internal register
uint8_t ds1307::getRegister(uint8_t reg)
{
    Wire.beginTransmission(address); // address the ds1307
    Wire.write(reg);                 // point to the selected register
    Wire.endTransmission();          // execute comand

    Wire.requestFrom(address, 1);    // requires 1 byte from the DS1307
    uint8_t c = Wire.read();         // receive the byte
    return c;                        // return register value
}


// Turn on the internal clock
void ds1307::resume()
{
    setRegister(0x00, (getRegister(0x00) & 0x7F)); // reset CH bit of register 0
}


// Turn off the internal clock
void ds1307::standby()
{
    setRegister(0x00, (getRegister(0x00) | 0x80));   // set CH bit of register 0
}


// Set seconds
void ds1307::setSeconds(uint8_t seconds)
{
    setBCDtoRegister(0, seconds);
}


// Set minutes
void ds1307::setMinutes(uint8_t minutes)
{
    setBCDtoRegister(1, minutes);
}


// Set hours
void ds1307::setHours(uint8_t hours)
{
    setBCDtoRegister(2, hours);
}


// Set the day of the week
void ds1307::setDow(uint8_t dow)
{
    setBCDtoRegister(3, dow);
}


// Set the data
void ds1307::setData(uint8_t data)
{
    setBCDtoRegister(4, data);
}


// Set the month
void ds1307::setMonth(uint8_t month)
{
    setBCDtoRegister(5, month);
}


// Set the year
void ds1307::setYear(uint8_t year)
{
    setBCDtoRegister(6, year);
}


// Read DS1307 data
void ds1307::getDate(uint8_t *values)
{
    uint8_t i = 0;

    Wire.beginTransmission(address); // address the ds1307
    Wire.write(0x00);                // point to the register 0
    Wire.endTransmission();          // execute comand

    Wire.requestFrom(address, 7);    // requires 6 bytes from the DS1307
    while(Wire.available())          // slave can send less bytes then requested
    {
        uint8_t c = Wire.read();     // receive next byte
        values[i++] = (((c >> 4) * 10) + (c & 0x0F));
    }
}
