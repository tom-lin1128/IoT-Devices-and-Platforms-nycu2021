#include <Servo.h>
Servo myservo;

int servopoint = 0;
int sensorMin = 0;
int sensorMax = 1023;  

// Sensor pins
#define sensorPower 7
#define sensorPin A0

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
// Value for storing water level
int val = 0;
void setup() { // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);

  pinMode( sensorPin, INPUT);
  Calibration(sensorPin);
  myservo.attach(9); 
  myservo.write( servopoint );
}

int flag = 0;
void loop() { //get the reading from the function below and print it
  int level = readSensor();
  
  val = level;  
  val = constrain(val, sensorMin, sensorMax); 
  val = map(val, sensorMin, sensorMax, 0, 100);   
  Serial.println(sensorMax);
  if ( val < 40 && val > 5)
  {
    if(servopoint < 180 && flag == 0) servopoint++;
    if(servopoint == 180) flag = 1;
    if(servopoint > 0 && flag == 1) servopoint--;
    if(servopoint == 0) flag = 0;
  }
  myservo.write( servopoint ); 
  delay(30);
  
  Serial.print("Water level: ");
  Serial.println(val);
  //delay(1000);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH); // Turn the sensor ON
  delay(10); // wait 10 milliseconds
  val = analogRead(sensorPin); // Read the analog value form sensor
  digitalWrite(sensorPower, LOW); // Turn the sensor OFF
  return val; // send current reading
}
