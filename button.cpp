#include <stdint.h>

#include "button.h"

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
static void setTimerStart(char label) {
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
static void updateButton(char label, bool isPressed) {
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
void initialiseButton(Button* button, char label, uint8_t pin) {
    // sets the button label, puts button in default state and registers it
    button->label = label;
    button->pin = pin;
    button->pressed = false;
    button->longPress = false;
    pinMode(pin, INPUT);
    registerButton(button);
}

// checks a button to see if its been long pressed
void updateLongPress(char label) {
    size_t i = 0;
    bool isFound = false;
    while (i < numButtons && !isFound) { // assumes this label is unique and picks the first one found
        if (allButtons[i]->label == label) {
            if (allButtons[i]->pressed && millis() - allButtons[i]->startTime >= LONG_PRESS_TIME) {
                allButtons[i]->longPress = true;
            } else {
                allButtons[i]->longPress = false;
            }
            isFound = true;
        }
        i ++;
    }
}

// checks if a button is clicked and updates its state and returns true if it was clicked
bool isButClicked(Button* button) {
    if (millis() - button->startTime > BOUNCE_DELAY) { // 50 ms to account for bouncing
        if (digitalRead(button->pin) == HIGH && !button->pressed) {
            updateButton(button->label, true);
        } else if (digitalRead(button->pin) == LOW && button->pressed) {
            updateButton(button->label, false);
            if (!button->longPress) {
                return true;
            }
        }
    }
    return false;
}

bool isLongPressed(Button* button) {
    if (button->pressed && !button->longPress) {
        updateLongPress(button->label);
    } else if (!button->pressed && button->longPress) {
        updateLongPress(button->label);
        return true;
    }
    return false;
}
