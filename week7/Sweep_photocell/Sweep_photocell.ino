#include <Servo.h>
Servo myservo; 

int servopoint = 90;
int sensorMin = 0;
int sensorMax = 1023;
int potpin = A0;  
int val = 0;  

void Calibration(int sensorPin){
  int flag = millis();
  int sensorValue = 0;
 while (millis() - flag < 5000) {
    int sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode( potpin, INPUT);
  Calibration(potpin);
  myservo.attach(9); 
  myservo.write( servopoint );
}

void loop() {
  val = analogRead(potpin);  
  val = constrain(val, sensorMin, sensorMax); 
  val = map(val, sensorMin, sensorMax, 0, 255);        
  Serial.println(val);
  if ( val < 195 )
  {
    if (servopoint < 180) servopoint++;
  }
  if ( val > 210 )
  {
    if(servopoint > 0 && servopoint < (sensorMax - 3)) servopoint--;

  }
  myservo.write( servopoint ); 
  delay(50);
}
