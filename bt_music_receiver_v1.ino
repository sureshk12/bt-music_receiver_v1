#include "BluetoothA2DPSink.h"
#include "keyInput.h"
#include "irDecode.h"
#include "global.h"

BluetoothA2DPSink a2dp_sink;
KeyInput keyinput;
IrDecode irDecode;

bool playPass = false;    // Playing
uint8_t playerMode = 1;  // 1 = BT, 2 = AUX
uint8_t butNum = 0;
uint8_t selectedSource = 1; // 1 = BT , 2 = USB, 3 AUX, 4 = Optical, 5 = ARC
bool btOnMode = false;

bool foundKey = false;
double foundKeyTime = millis();

int prevTime = micros();
int durationTime = 0;
uint8_t prevPinData = HIGH;
int timeArray [32] = {};
uint8_t bitCount = 0;
uint32_t irData = 0;


void avrc_metadata_callback(uint8_t id, const uint8_t *text) {
  Serial.printf("==> AVRC metadata rsp: attribute id 0x%x, %s\n", id, text);
}

void doKeyIrAction(uint8_t actionNum) {
    //Player routine
    if (a2dp_sink.get_audio_state()==ESP_A2D_AUDIO_STATE_STARTED){
        btOnMode = true;
    }
    //Serial.print("Key ");  Serial.print(actionNum);  Serial.println(" Pressed");
    if (playerMode == 1) {
        // BT
        if (actionNum == 3) {                                           // PLAY / PAUSE

            //Play / Pause
            if (playPass) {
                //Pause
                Serial.println("pause");
                if(btOnMode) {a2dp_sink.pause();}
                playPass = false;
            } else {
                //play
                Serial.println("play");
                if(btOnMode) {a2dp_sink.play();}
                playPass = true;
            }
        } else if (actionNum == 1) {                                    // PREVIOUS
            Serial.println("Previous");
            if(btOnMode) {a2dp_sink.previous();}
        } else if (actionNum == 2) {                                    // NEXT
            Serial.println("Next");
            if(btOnMode) {a2dp_sink.next();}
        } else if (actionNum == 4) {                                    // VOLUME MINUS
            Serial.println("Vol -");
            if(btOnMode) {
                int volValue = a2dp_sink.get_volume();
                volValue = volValue - 4;
                if(volValue < 0 ) {
                    volValue = 0;
                }
                a2dp_sink.set_volume(volValue);
                Serial.printf("Volume level = %d\n", volValue );
            }
    } else if (actionNum == 5) {                                        // VOLUME PLUS
                Serial.println("Vol +");
                if(btOnMode) {
                int volValue = a2dp_sink.get_volume();
                volValue = volValue + 4;
                if(volValue > 127 ) {
                    volValue = 127;
                }
                a2dp_sink.set_volume(volValue);
                Serial.printf("Volume level = %d\n", volValue );
            }            
        } else if (actionNum == 6) {
            Serial.println("Std By");                                   // STAND BY
        } else if (actionNum == 7) {
            Serial.println("Mute");                                     // MUTE
        } else if (actionNum == 8) {
            Serial.println("Source");                                   // SOURCE / INPUT
        } else if (actionNum == 9) {
            Serial.println("Music");                                    // MUSIC
        } else if (actionNum == 10) {
            Serial.println("Movie");                                    // MOVIE
        } else if (actionNum == 11) {
            Serial.println("News");                                     // ATAND BY
        } else if (actionNum == 12) {
            Serial.println("Treble +");                                 // TREBLE PLUS
        } else if (actionNum == 13) {
            Serial.println("Treble -");                                 // TREBLE Minus
        } else if (actionNum == 14) {
            Serial.println("BASS +");                                   // BASS PLUS
        } else if (actionNum == 15) {
            Serial.println("BASS -");                                   // BASS Minus
        }
    }
    //delay(400);
}

void setup() {
    Serial.begin(115200);
    delay(100);

    // //Initilize IR values
    pinMode(IRPORT, INPUT_PULLUP);
    for(int x = 0; x < 32; x++) {
        timeArray[x] = 0;
    }

    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);

    //set the resolution to 12 bits (0-4096)
    analogReadResolution(12);  

    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    //a2dp_sink.start("MyMusic");  

    a2dp_sink.set_auto_reconnect(true, 1000);
    a2dp_sink.start("MyMusic");  



}

void loop() {
  
    butNum = keyinput.getKeyValue();
    if(butNum != 0) {
        // Serial.printf("KEY INPUT %d\n", butNum);
        if(foundKey) {
            if((millis() - foundKeyTime) > 600) {
                foundKey = false;
            } 
        }
        if(!foundKey) {
            doKeyIrAction(butNum);
            butNum = 0;
            foundKey = true;
            foundKeyTime = millis();
        }
    }    
    
    //Remote
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
        //startIr = true;
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
        //Serial.print("IR DATA is = "); Serial.println(irData);
        switch(irData) {
            case 3245148407:    //PREVIOUS
                butNum = 1;
                break;
            case 3245181047:    //Next
                butNum = 2;
                break;
            case 3245191247:    // PLAY / PAUSE
                butNum = 3;
                break;
            case 3245174927:    // Volume -
                butNum = 4;
                break;
            case 3245199407:    // Volume +
                butNum = 5;
                break;
            case 3245191757:    // STANDBY
                butNum = 6;
                break;
            case 3245195837:    // MUTE
                butNum = 7;
                break;
            case 3245193287:    // SOURCE/INPUT
                butNum = 8;
                break;
            case 3245187677:    // MUSIC
                butNum = 9;
                break;
            case 3245203997:    // MOVIE
                butNum = 10;
                break;
            case 3245175437:    // News
                butNum = 11;
                break;
            case 3245168807:    // TREBLE +
                butNum = 12;
                break;
            case 3245163197:    // TREBLE -
                butNum = 13;
                break;
            case 3245205527:    // BASS +
                butNum = 14;
                break;
            case 3245152487:    // BASS -
                butNum = 15;
                break;
        default:
            break;
        }
        doKeyIrAction(butNum);
        bitCount = 0;
        //startIr = false;
        prevPinData = HIGH;
    }

}
