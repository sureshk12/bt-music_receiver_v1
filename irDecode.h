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
        int prevTime = micros();
        int durationTime = 0;
        uint8_t prevPinData = HIGH;
        int timeArray[32] = {};
        uint8_t bitCount = 0;
        uint32_t irData = 0;
        uint8_t butNum = 0;
        //bool startIrLocal = false;

    public:
        IrDecode();
        uint8_t start();
        uint8_t getIrData();

};


#endif