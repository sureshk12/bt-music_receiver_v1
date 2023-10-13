#include "keyInput.h"
#include "global.h"

KeyInput::KeyInput() {
  //Default constructor
}

uint8_t KeyInput::start() {

  return 0;
}

uint8_t KeyInput::getKeyValue() {
    int adcVol = analogReadMilliVolts(KEYPORT);
    //Serial.println("Volatge : "); Serial.println(adcVol);
    /* Added on 20231013*/
    if(adcVol > 3000) {
        debounce --;
        if(debounce < 1) {
            debounce = 0;
        }
        return 0;
    }
    if (adcVol > LVL1LO && adcVol < LVL1HI) {
        if (butNum == 1) {
            debounce++;
        } else {
            butNum = 1;
            debounce = 1;
        }
    } else if (adcVol > LVL2LO && adcVol < LVL2HI) {
        if (butNum == 2) {
            debounce++;
        } else {
            butNum = 2;
            debounce = 1;
        }
    } else if (adcVol > LVL3LO && adcVol < LVL3HI) {
        if (butNum == 3) {
            debounce++;
        } else {
            butNum = 3;
            debounce = 1;
        }
    } else if (adcVol > LVL4LO && adcVol < LVL4HI) {
        if (butNum == 4) {
            debounce++;
        } else {
            butNum = 4;
            debounce = 1;
        }
    } else if (adcVol > LVL5LO && adcVol < LVL5HI) {
        if (butNum == 5) {
            debounce++;
        } else {
            butNum = 5;
            debounce = 1;
        }
    } else {
        debounce --;
    }

    if (debounce > 50) {
        debounce = 0;
        uint8_t retBut = butNum;
        butNum = 0;
        debounce = debounce + 2;
        return retBut;      
    } else {
        if(debounce < 1) {
            debounce = 0;
            butNum = 0;
        }
        return 0;
    }
    //return butNum;
}