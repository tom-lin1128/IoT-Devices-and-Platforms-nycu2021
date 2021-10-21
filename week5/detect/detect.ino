#define echoPin 7
#define trigPin 6

int maximumRange = 200;
int minimumRange = 0;
long duration, distance;
const int redPin = 10;
const int greenPin = 11;
const int bluePin = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration/58.2;

  if(distance >= 30 && distance <= 100){
    Serial.println(distance);
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    tone(8, 392, 200);
    delay(250);
  }
  else if(distance < 30){
    Serial.println(distance);
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    tone(8, 392, 100);
    delay(250);
  }
  else{
    Serial.println(distance);
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    delay(50);
  }
}
