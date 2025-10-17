#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "button.h"

void updateTimer();
void displayTimer(const hd44780_I2Cexp* lcd, String title);
void detectTimerEvents(Button* button);

#endif // TIMER_H