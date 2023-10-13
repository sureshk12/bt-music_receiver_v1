#include "Arduino.h"
#include "irDecode.h"
#include "global.h"

IrDecode::IrDecode() {
  //Default constructor
}

uint8_t IrDecode::start() {

  return 0;
}

/*
uint8_t IrDecode::getIrKeyCode(uint32_t irDataInput, uint8_t mode) {
    
    uint8_t butNumRetVal;
    switch(irDataInput) {
        case 3245148407 :
            butNumRetVal = 1;
            break;
        case 3245181047:
            butNumRetVal = 2;
            break;
        case 3245191247:
            butNumRetVal = 3;
            break;
        case 3245174927:
            butNumRetVal = 4;
            break;
        case 3245199407:
            butNumRetVal = 5;
            break;
        default:
            butNumRetVal = 0;
            break;
    }
    
    return 0;
}
*/