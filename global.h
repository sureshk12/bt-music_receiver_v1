
#ifndef GLOBAL_H
#define GLOBAL_H

#define ESP32_TYPE WROOM

#if ESP32_TYPE == WROOM
    #define KEYPORT 34
    #define IRPORT 35
    #define I2S_BCK 4
    #define I2S_LRCLK 5
    #define I2S_DATAOUT 18
    #define I2C_SDA 21
    #define I2C_SCL 22
#endif




#endif