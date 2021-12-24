#include <Adafruit_BMP085.h>

/*************************************************** 
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These pressure and temperature sensors use I2C to communicate, 2 pins
  are required to interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

const int buttonPin = 2;
const int led1Pin = 11;
const int led2Pin = 12;
const int led3Pin = 13;

int led1State = LOW;
int led2State = LOW;
int led3State = LOW;

int buttonState;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

Adafruit_BMP085 bmp;
  
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  digitalWrite(led1Pin, led1State);
  digitalWrite(led2Pin, led2State);
  digitalWrite(led3Pin, led3State);
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}

int count = 0;
float first_floor = 0.0;
float second_floor = 0.0;
int fl = 0;
int flag = 0;

void loop() {
    int reading = digitalRead(buttonPin);
    if(reading != lastButtonState){
      lastDebounceTime = millis();
    }

    if((millis()-lastDebounceTime) > debounceDelay){
      if(reading != buttonState){
        buttonState = reading;
        if( buttonState == HIGH){
         Serial.println(buttonState);
         if(count==0){
          first_floor = bmp.readAltitude();
          count ++;
          Serial.print("1 ");
          Serial.println(first_floor);
        }
        else if(count==1){
          second_floor = bmp.readAltitude();
          count ++;
          Serial.print("2 ");
          Serial.println(second_floor);
        }
        else if(count == 2){
          count ++;
          fl = ((bmp.readAltitude()-first_floor)/(second_floor-first_floor)) + 1;
          Serial.println(fl);
      }
      }            
      
      
     }
        if(count == 2){
          fl = ((bmp.readAltitude()-first_floor)/(second_floor-first_floor)) + 1;
          Serial.println(fl);
          if(fl<=1){
            digitalWrite(led1Pin, HIGH);
            digitalWrite(led2Pin, LOW);
            digitalWrite(led3Pin, LOW);
          }
          else if(fl==2){
            digitalWrite(led1Pin, LOW);
            digitalWrite(led2Pin, HIGH);
            digitalWrite(led3Pin, LOW);
          }
          else if(fl==3){
            digitalWrite(led1Pin, LOW);
            digitalWrite(led2Pin, LOW);
            digitalWrite(led3Pin, HIGH);
          }
          else{
            digitalWrite(led1Pin, LOW);
            digitalWrite(led2Pin, LOW);
            digitalWrite(led3Pin, LOW);
          }
        }
    }
    lastButtonState = reading;
}
