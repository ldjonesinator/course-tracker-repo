#include <Wire.h>

// using namespace std;
#include "button.h"
#include "lcd.h"

#define BUTTON_PIN 2

hd44780_I2Cexp lcd;
Button button;


int CATAGORY_SIZE = 5;
const String CATAGORIES[] = {"ENEL200", "ENEL220", "ENEL270", "ENEL280", "EMTH210"};
int selected_cat_i = 0;

int cat_times[5] = {0, 0, 0, 0, 0}; // time in seconds


// timer variables
unsigned long timer = 0; // timer for seconds
unsigned long startTime;
unsigned long pauseStart;
unsigned long pauseDuration = 0;

bool isTimerRunning = false;


// returns the same number with zeros in front to reach the required amount of characters
String getFixedNumberLength(int num, int requiredCharAmnt) {
    if (String(num).length() >= requiredCharAmnt) { // error prevention with unsigned numbers
        return String(num);
    }

    String zeros = "";
    for (int i = 0; i < requiredCharAmnt - String(num).length(); i++) {
        zeros += "0";
    }

    return zeros + String(num);
}

String getTimerDisplayFormat(long timer) { // takes timer value in seconds and outputs time in hours:minutes
    int hours = timer / 3600;
    int minutes = (timer % 3600) / 60;
    int seconds = (timer % 3600) % 60;

    return getFixedNumberLength(hours, 2) + ":" + getFixedNumberLength(minutes, 2) + ":" + getFixedNumberLength(seconds, 2);
}


void setup() {
    lcdSetup(&lcd, true);
    initialiseButton(&button, 'B', BUTTON_PIN);

// TESTING
    Serial.begin(9600);
    Serial.println("Starting up");
}

void loop() {

    if (millis() > (timer + 1) * 1000 && isTimerRunning) { // happens every second
        timer = (millis() - (startTime + pauseDuration)) / 1000; // only have the timer working when isTimerRunning is TRUE
    }

    lcdWrite(&lcd, CATAGORIES[selected_cat_i], 0);
    lcdWrite(&lcd, getTimerDisplayFormat(timer), 1);

    if (isLongPressed(&button)) {
        startTime = millis();
        isTimerRunning = true;
        pauseDuration = 0;
    }

    if (isButClicked(&button)) {
        if (startTime == 0) { // remove this later when there's transitions
            startTime = millis();
        }
        isTimerRunning = !isTimerRunning;
        if (!isTimerRunning) {
            pauseStart = millis();
        } else if (pauseStart != 0) { // don't want the duration going up at the start
            pauseDuration += millis() - pauseStart;
            Serial.println(pauseDuration);
        }
    }

}
