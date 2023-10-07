#include "Arduino.h"
#include "irDecode.h"
#include "global.h"

IrDecode::IrDecode() {
  //Default constructor
}

uint8_t IrDecode::start() {

  return 0;
}

uint8_t IrDecode::getIrData() {
    irData = 0;
    uint8_t pinData = digitalRead(IRPORT);
    if(pinData == LOW && prevPinData == HIGH) {
        durationTime = micros() - prevTime;
        prevTime = micros();
        prevPinData = LOW;
        timeArray[bitCount] = durationTime;
        bitCount++;    
    }

    if(pinData == HIGH && prevPinData == LOW) {
        prevPinData = HIGH;
    }

    if(durationTime > 12150 && durationTime < 14850) {
        bitCount = 0;
        //startIrLocal = true;
    }

    if(bitCount > 31) {
        irData = 0;
        for(int x = 0; x < 32; x++) {
            irData = irData << 1;
            if(timeArray[x] > 1634) {
                irData = irData ^ 1; 
            }
        //Serial.printf("%d, ",timeArray[x]);
        timeArray[x] = 0;
        }
        //Serial.println();
        // Serial.print("IR DATA is = "); Serial.println(irData);
        switch(irData) {
            case 3245148407:
                butNum = 1;
                break;
            case 3245181047:
                butNum = 2;
                break;
            case 3245191247:
                butNum = 3;
                break;
            case 3245174927:
                butNum = 4;
                break;
            case 3245199407:
                butNum = 5;
                break;
            default:
                butNum = 0;
                break;
        }
    }
    bitCount = 0;
    prevPinData = HIGH;
    return butNum;
}
