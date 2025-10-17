#include <stdint.h>

#include "timer.h"
#include "lcd.h"
#include "button.h"


// timer variables
static unsigned long timer = 0; // timer for seconds
static unsigned long startTime;
static unsigned long pauseStart;
static unsigned long pauseDuration = 0;

static bool isTimerRunning = false;


// returns the same number with zeros in front to reach the required amount of characters
static String getFixedNumberLength(int num, int requiredCharAmnt) {
    if (String(num).length() >= requiredCharAmnt) { // error prevention with unsigned numbers
        return String(num);
    }

    String zeros = "";
    for (int i = 0; i < requiredCharAmnt - String(num).length(); i++) {
        zeros += "0";
    }
    return zeros + String(num);
}

static String getTimerDisplayFormat(long timer) { // takes timer value in seconds and outputs time in hours:minutes
    int hours = timer / 3600;
    int minutes = (timer % 3600) / 60;
    int seconds = (timer % 3600) % 60;

    return getFixedNumberLength(hours, 2) + ":" + getFixedNumberLength(minutes, 2) + ":" + getFixedNumberLength(seconds, 2);
}

// updates the timer
void updateTimer() {
    if (millis() > (timer + 1) * 1000 && isTimerRunning) { // happens every second
        timer = (millis() - (startTime + pauseDuration)) / 1000; // only have the timer working when isTimerRunning is TRUE
    }
}

void displayTimer(const hd44780_I2Cexp* lcd, String title) {
    lcdWrite(lcd, title, 0);
    lcdWrite(lcd, getTimerDisplayFormat(timer), 1);
}

void detectTimerEvents(Button* button) {
    if (isLongPressed(button)) {
        startTime = millis();
        isTimerRunning = true;
        pauseDuration = 0;
    }

    if (isButClicked(button)) {
        if (startTime == 0) { // remove this later when there's transitions
            startTime = millis();
        }
        isTimerRunning = !isTimerRunning;
        if (!isTimerRunning) {
            pauseStart = millis();
        } else if (pauseStart != 0) { // don't want the duration going up at the start
            pauseDuration += millis() - pauseStart;
        }
    }
}
