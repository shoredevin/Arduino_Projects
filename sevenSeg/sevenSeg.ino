#include "SevSeg.h"
SevSeg sevseg; 
//int nums = {0,1,2,3,4,5,6,7,8,9}

void setup(){
    Serial.begin(9600);
    byte numDigits = 1;
    byte digitPins[] = {};
    byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
    bool resistorsOnSegments = true;

    byte hardwareConfig = COMMON_CATHODE; 
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
}

void loop(){
        for (int i = 0; i < 10; i++) {
          sevseg.setNumber(i);  
          sevseg.refreshDisplay(); 
          Serial.println(i);
          delay(1000);
        }
}
