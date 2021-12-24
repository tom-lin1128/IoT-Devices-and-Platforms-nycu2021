#include <SoftwareSerial.h>

#include <Math.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
unsigned long BAUD_RATE = 9600;
const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;
const int READ_TIME = 500;
unsigned long prevMillis;
int ledPin = 13;

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
SoftwareSerial bluetooth (BLUETOOTH_TX, BLUETOOTH_RX);
void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(){
  Serial.begin(BAUD_RATE);
  pinMode(ledPin, OUTPUT);
  bluetooth.begin(BAUD_RATE);
  Serial.println("Setup Complete");
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  displaySensorDetails();
}

void loop(){
  //sensors_event_t event; 
  //mag.getEvent(&event);
if (Serial.available()){
  String str;
  Serial.print("Input:");
  prevMillis = millis();
  while(millis() - prevMillis < READ_TIME){
  if (Serial.available ()){
    char c =  Serial.read();
    if (c != 10 && c != 13){
      str += c;
  } } }
  bluetooth.print(str);
  Serial.println(str);
}

if (bluetooth.available ()){
  String  str = "";
  Serial.print("HM10: ");
  prevMillis  = millis();
  while(millis() - prevMillis < READ_TIME){
    if(bluetooth.available()){
      str += (char) bluetooth.read();
    }
  }
  if(str == "on"){
    digitalWrite(ledPin,HIGH);
    Serial.println("on");
  }
  if(str == "off"){
    digitalWrite(ledPin,LOW);
    Serial.println("off");
  }
  if(str == "w"){
    //Serial.println(-10);
    sensors_event_t event; 
    //Serial.println(0);
    mag.getEvent(&event);
    //Serial.println(10);
    float heading = atan2(event.magnetic.y, event.magnetic.x);
    //Serial.println(20);
    float declinationAngle = 0.22;
    heading += declinationAngle;
    if(heading < 0)
       heading += 2*PI;
    if(heading > 2*PI)
       heading -= 2*PI;
    float headingDegrees = heading * 180/M_PI;
    Serial.println(headingDegrees);
  } 
  //Serial.println(str);
}}
