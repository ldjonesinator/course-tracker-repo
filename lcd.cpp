#include <stdint.h>

#include "lcd.h"


static uint8_t stringIndexes[LCD_ROWS];


// sets up an LCD with the options to start with the backlight on
void lcdSetup(const hd44780_I2Cexp* lcd, bool backlight) {
    Wire.begin();
    int status = lcd->begin(LCD_COLS, LCD_ROWS);
    if (status != 0) {
        Serial.println("There was an error with the LCD");
        hd44780::fatalError(status);
    }
    lcd->clear();
    if (backlight) {
        lcd->backlight();
    } else {
        lcd->noBacklight();
    }
}

// puts up to the first 16 characters of a string on an LCD and returns if the line is too long
bool lcdWrite(const hd44780_I2Cexp* lcd, String text, uint8_t line) {
    bool islong;
    lcd->setCursor(0, line);
    lcd->print("                ");
    if (text.length() > LCD_COLS) {
        lcd->setCursor(0, line);
        lcd->print(text.substring(0, 16));
        islong = true;
    } else {
        lcd->setCursor((LCD_COLS - text.length()) / 2, line); // Spacing to center the text
        lcd->print(text);
        islong = false;
    }
    return islong;
}

// Shifts text on a line in the LCD
bool shiftText(const hd44780_I2Cexp* lcd, String text, uint8_t line) {
    bool isDoneShift = false;
    if (stringIndexes[line] == text.length() - 17) {
        isDoneShift = true;
    }

    if (stringIndexes[line] >= text.length() - 16) {
        lcdWrite(lcd, text, line);
        stringIndexes[line] = 0;
    } else {
        lcdWrite(lcd, text.substring(stringIndexes[line] + 1, text.length()), line);
    }

    stringIndexes[line] ++;
    return isDoneShift;
}
