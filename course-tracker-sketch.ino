#include <stdint.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "timer.h"
#include "button.h"
#include "lcd.h"


#define BUTTON_PIN 2


typedef enum {
    CHOOSE,
    TIMER,
    CREATE,
    SEND
} State;

State deviceState = CHOOSE;

hd44780_I2Cexp lcd;
Button button;


int CATAGORY_SIZE = 5;
const String CATAGORIES[] = {"ENEL200", "ENEL220", "ENEL270", "ENEL280", "EMTH210"};
int selected_cat_i = 0;

int cat_times[5] = {0, 0, 0, 0, 0}; // time in seconds

void setup() {
    lcdSetup(&lcd, true);
    initialiseButton(&button, 'B', BUTTON_PIN);

// TESTING
    Serial.begin(9600);
    Serial.println("Starting up");
}

void loop() {

    updateTimer();
    displayTimer(&lcd, CATAGORIES[selected_cat_i]);
    detectTimerEvents(&button);



}
