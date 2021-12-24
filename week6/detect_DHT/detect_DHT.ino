#define echoPin 7
#define trigPin 6
#define DHTPIN 2

#include "DHT.h"
#define DHTTYPE DHT11 

int maximumRange = 200;
int minimumRange = 0;
long duration, distance;
const int redPin = 10;
const int greenPin = 11;
const int bluePin = 12;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float h = dht.readHumidity();
  float e = (h / 100) * 6.105 * exp(17.27*t /(237.7 + t));

  float dewpoint = t - ((100 - h) / 5); 
  Serial.print(F("Dew point : "));
  Serial.print(dewpoint);

  float HI = -41.379 + (2.04901523 * f) + (10.14333127 * h) + (-0.22475541 * f * h) + (-0.00683783 * f * f) + (-0.05481717 * h * h) + (0.00122874 * f * f * h) + (0.00085282 * f * h * h) + (-0.00000199 * f * f * h * h);
  
  Serial.print(F(" Heat index : "));
  Serial.print(HI);

  float at = 1.04 * t + 0.2 * e - 0.65 * 2.7 -2.7;

  Serial.print(F(" apparent temperature : "));
  Serial.println(at);

  float c = 1.0 / (331.3 + 0.606 * t) * 10000 * 2;
  Serial.println(duration);
  distance = duration / c;

  if(distance >= 30 && distance <= 100){
    //Serial.println(distance);
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    tone(8, 392, 200);
    delay(250);
  }
  else if(distance < 30){
    //Serial.println(distance);
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    tone(8, 392, 100);
    delay(250);
  }
  else{
    //Serial.println(distance);
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    delay(50);
  }
}
