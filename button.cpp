#include <stdint.h>

#include "button.h"

const uint32_t LONG_PRESS_TIME = 3000; // 3 seconds
const uint8_t BOUNCE_DELAY = 100;
const uint8_t MAX_BUTTONS = 10;
static Button* allButtons[MAX_BUTTONS];
static uint8_t numButtons = 0;


// registers a button in to a list of memory
static void registerButton(Button* button) {
    if (numButtons < MAX_BUTTONS) { // don't have to worry about going over this amount
        allButtons[numButtons] = button;
        numButtons ++;
    }
}

// sets the start time for a button
static void setTimerStart(String label) {
    // updates the start time if the button is pressed
    size_t i = 0;
    bool isFound = false;
    while (i < numButtons && !isFound) { // assumes this label is unique and picks the first one found
        if (allButtons[i]->label == label) {
            allButtons[i]->startTime = millis();
            isFound = true;
        }
        i ++;
    }
}

// updates the button state and start time
static void updateButton(String label, bool isPressed) {
    size_t i = 0;
    bool isFound = false;
    while (i < numButtons && !isFound) { // assumes this label is unique and picks the first one found
        if (allButtons[i]->label == label) {
            setTimerStart(label);
            allButtons[i]->pressed = isPressed;
            isFound = true;
        }
        i ++;
    }
}

// Initialises a button in the default state
void initialiseButton(Button* button, String label, uint8_t pin) {
    // sets the button label, puts button in default state and registers it
    button->label = label;
    button->pin = pin;
    button->pressed = false;
    button->longPress = false;
    pinMode(pin, INPUT);
    registerButton(button);
}

// checks if a button is clicked and updates its state and returns true if it was clicked
bool isButClicked(Button* button) {
    if (millis() - button->startTime > BOUNCE_DELAY) { // 50 ms to account for bouncing
        if (digitalRead(button->pin) == HIGH && !button->pressed) {
            updateButton(button->label, HIGH);
        } else if (digitalRead(button->pin) == LOW && button->pressed) {
            updateButton(button->label, LOW);
            return true;
        }
    }
    return false;
}

// checks every button to see if its been long pressed
void updateLongPresses() {
    for (size_t i = 0; i < numButtons; i ++) {
        if (allButtons[i]->pressed && millis() - allButtons[i]->startTime >= LONG_PRESS_TIME) {
            allButtons[i]->longPress = true;
        } else {
            allButtons[i]->longPress = false;
        }
    }
}
