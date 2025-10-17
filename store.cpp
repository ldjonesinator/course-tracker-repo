#include <stdint.h>
#include <EEPROM.h>

#include "store.h"

static int eeAddress = 0;

void clearEEPROM() {
    for (size_t i = 0 ; i < EEPROM.length() ; i++) {
        EEPROM.write(i, 0);
    }
    eeAddress = 0;
}

void storeVariable() {
    EEPROM.put();
}
