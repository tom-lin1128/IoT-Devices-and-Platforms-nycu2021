/***************************************************************************
  This is a library example for the HMC5883 magnentometer/compass

  Designed specifically to work with the Adafruit HMC5883 Breakout
  http://www.adafruit.com/products/1746
 
  *** You will also need to install the Adafruit_Sensor library! ***

  These displays use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries with some heading example from
  Love Electronics (loveelectronics.co.uk)
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the version 3 GNU General Public License as
 published by the Free Software Foundation.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#define echoPin 7
#define trigPin 8

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

long duration, distance1, distance2;

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
const int buttonPin = 3; 

void setup(void) 
{
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buttonPin,INPUT);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
     /*There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

int lastButtonState = LOW;
int buttonState;
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;

int count = 0;
float headingDegrees1 = 0.0;
float headingDegrees2 = 0.0;

void loop(void) 
{
  /* Get a new sensor event */ 
  //Serial.println(reading);

  int reading = digitalRead(buttonPin);
  //Serial.println(reading);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

   if((millis() - lastDebounceTime) > debounceDelay){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState == LOW){
        if(count == 0){
          // heading
          sensors_event_t event; 
          mag.getEvent(&event);
          float heading = atan2(event.magnetic.y, event.magnetic.x);
          float declinationAngle = 0.22;
          heading += declinationAngle;
          if(heading < 0)
            heading += 2*PI;
          if(heading > 2*PI)
            heading -= 2*PI;
          headingDegrees1 = heading * 180/M_PI;
          Serial.print("heading: ");
          Serial.println(headingDegrees1);
          
          count=1;
          // distance
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2);
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          duration = pulseIn(echoPin, HIGH);
          distance1 = duration/58.2;
          Serial.print("distance1: ");
          Serial.println(distance1);
        }
        else{
          //heading
          sensors_event_t event; 
          mag.getEvent(&event);
          float heading = atan2(event.magnetic.y, event.magnetic.x);
          float declinationAngle = 0.22;
          heading += declinationAngle;
          if(heading < 0)
            heading += 2*PI;
          if(heading > 2*PI)
            heading -= 2*PI;
          headingDegrees2 = heading * 180/M_PI;
          Serial.print("heading: ");
          Serial.println(headingDegrees2);
          
          count=0;
          //distance
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2);
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          duration = pulseIn(echoPin, HIGH);
          distance2 = duration/58.2;
          Serial.print("distance2: ");
          Serial.println(distance2);
          float AB = sqrt(pow(distance1, 2) + pow(distance2, 2) - 2*distance1*distance2*cos(abs(headingDegrees1-headingDegrees2)));
          Serial.print("AB: ");
          Serial.println(AB);
        }
      }
    }
  }
  lastButtonState = reading;
  
}
