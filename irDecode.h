#ifndef IR_DECODE_H
#define IR_DECODE_H
/*
int prevTime = micros();
int durationTime = 0;
uint8_t prevPinData = HIGH;
int timeArray[32] = {};
uint8_t bitCount = 0;
uint32_t irData = 0;
*/


class IrDecode {
    private:

    public:
        IrDecode();
        uint8_t start();
        //uint8_t getIrKeyCode(uint32_t irDataInput, uint8_t mode);

};


#endif