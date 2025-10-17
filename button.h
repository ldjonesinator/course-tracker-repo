#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <stdint.h>


#define LONG_PRESS_TIME 2000
#define BOUNCE_DELAY 100
#define MAX_BUTTONS 10


// Button struct
typedef struct {
    char label;
    uint8_t pin;
    bool pressed;
    bool longPress;
    uint64_t startTime;
} Button;

void initialiseButton(Button* button, char label, uint8_t pin);
void updateLongPress(char label);
bool isButClicked(Button* button);
bool isLongPressed(Button* button);


#endif // BUTTON_H
