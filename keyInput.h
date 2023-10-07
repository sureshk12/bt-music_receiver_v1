
#include <stdint.h>
#include <Arduino.h>

#ifndef KEYINPUT_H
#define KEYINPUT_H

#define LVL5HI 2888
#define LVL5LO 2720
#define LVL4HI 2410
#define LVL4LO 2123
#define LVL3HI 1815
#define LVL3LO 1485
#define LVL2HI 1078
#define LVL2LO 809
#define LVL1HI 503
#define LVL1LO 354

class KeyInput {
  private:
    uint8_t debounce = 0;
    

  public:
    uint8_t butNum = 0;
    KeyInput();
    uint8_t start();
    uint8_t getKeyValue();
};



#endif