/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

bool lapInProgress = false;
int lap = 0;
uint32_t startingTime;
uint32_t endingTime;
uint32_t duration;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Race started...");
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  if (sensorValue == 0) { 
    startTimer();
  } if (sensorValue == 1023) {
    endTimer();
  }
  delay(1);        // delay in between reads for stability
}

void startTimer() {
  if (lapInProgress == false) {
    startingTime = millis();
    lapInProgress = true; 
  }
}

void endTimer() {
  if (lapInProgress == true) {
    endingTime = millis();
    calculateDuration();
    lapInProgress = false;
  }

}

void calculateDuration() {
  lap++;
  duration = endingTime - startingTime; 

  long hr = duration / 3600000;
  duration = duration - 3600000 * hr;
  long min = duration / 60000;
  duration = duration - 60000 * min;
  long sec = duration / 1000;
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
  Serial.println("");
}
