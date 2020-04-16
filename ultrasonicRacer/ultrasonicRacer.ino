/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

#include "SevSeg.h"
SevSeg sevseg; 

// defines pins numbers
const int trigPin = 11;
const int echoPin = 10;
// defines variables
long duration;
int distance;

int lap = 0;
uint32_t startingTime;
uint32_t endingTime;
uint32_t lapDuration;


void setup() {
  Serial.begin(9600); // Starts the serial communication
  
  //setting up ultrasonce sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  //setting up seven segment
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034/2;
  if (millis() > 1000) {
    if (distance < 100) {
      //Serial.println("Distance less than 100");
      endTimer();
      delay(1000);
    }
  }
}

void startTimer() {
    startingTime = millis();
}

void endTimer() {
    if (lap == 0) {
      Serial.println("Race starting now...");
       lap++;
       startTimer();
    } else {
      endingTime = millis();
      calculateDuration();
      lap++;
      startTimer();
    }
}

void calculateDuration() {
  lapDuration = endingTime - startingTime; 
  long hr = lapDuration / 3600000;
  lapDuration = lapDuration - 3600000 * hr;
  long min = lapDuration / 60000;
  lapDuration = lapDuration - 60000 * min;
  long sec = lapDuration / 1000;
  Serial.print("Lap: ");
  Serial.println(lap);
  Serial.println("hh:mm:ss");
  if (hr < 10) {
    Serial.print(0);
    Serial.print(hr);
  } else {
    Serial.print(hr);
  }
  Serial.print(":");
  if  (min < 10) {
    Serial.print(0);
    Serial.print(min);
  } else {
    Serial.print(min);
  }
  Serial.print(":");
  if (sec < 10) {
    Serial.print(0);
    Serial.println(sec); 
  } else {
    Serial.println(sec);
  }
  sevseg.setNumber(sec);  
  sevseg.refreshDisplay(); 
  Serial.println("");
}
