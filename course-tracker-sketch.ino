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
unsigned long start_time;

bool is_timer_running = false;


// returns the same number with zeros in front to reach the required amount of characters
String getFixedNumberLength(int num, int required_char_amnt) {
    if (String(num).length() >= required_char_amnt) { // error prevention with unsigned numbers
        return String(num);
    }

    String zeros = "";
    for (int i = 0; i < required_char_amnt - String(num).length(); i++) {
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

    if (millis() > (timer + 1) * 1000 && is_timer_running) { // happens every second
        timer = (millis() - start_time) / 1000; // only have the timer working when is_timer_running is TRUE
    }

    lcdWrite(&lcd, CATAGORIES[selected_cat_i], 0);
    lcdWrite(&lcd, getTimerDisplayFormat(timer), 1);

    if (isLongPressed(&button)) {
        start_time = millis();
        is_timer_running = true;
    }

    if (isButClicked(&button)) {
        is_timer_running = !is_timer_running;
    }
}
