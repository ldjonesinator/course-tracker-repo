#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <stdint.h>

// Button pins
#define LEFT_BUTTON_PIN 2
#define RIGHT_BUTTON_PIN 3

// Button struct
typedef struct {
    String label;
    uint8_t pin;
    bool pressed;
    bool longPress;
    uint64_t startTime;
} Button;

void initialiseButton(Button* button, String label, uint8_t pin);
// void updateButton(String label, bool isPressed);
bool isButClicked(Button* button);
void updateLongPresses();

#endif // BUTTON_H
