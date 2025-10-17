#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>


#define LCD_COLS 16
#define LCD_ROWS 2


void lcdSetup(const hd44780_I2Cexp* lcd, bool backlight);
bool lcdWrite(const hd44780_I2Cexp* lcd, String text, uint8_t line);
bool shiftText(const hd44780_I2Cexp* lcd, String text, uint8_t line);

#endif // LCD_H
