const int numReadings = 10;

int sensorMin = 0;
int sensorMax = 1023;
int readings[numReadings];
int readIndex = 0; 
int sensorValue = 0;   
int ave = 0;
int sum2 = 0;
int total = 0;

const int sensorPin = A0;    
const int ledPin = 9;

void Calibration(int sensorPin){
  int flag = millis();
  int sensorValue = 0;
 while (millis() - flag < 5000) {
    sensorValue = analogRead(sensorPin);

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

int Smoothing(int inputPin){
  int average = 0;  
  
  total = total - readings[readIndex];
  readings[readIndex] = inputPin;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;
  delay(1);
  return average;
}

int sum(){
  int sum1 = 0;
  for(int i = 0;i < numReadings; i++){
    sum1 += (i+1);
  }
  return sum1;
}

int Smoothing2(int inputPin,int numofsum){
  int average = 0;  
  int weightTotal = 0;

  readings[readIndex] = inputPin;
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  for(int i = 0; i < numReadings ; i++){
    weightTotal += (i+1)*readings[readIndex];
  }
  average = weightTotal / numofsum;
  //average = total / numReadings;
  delay(1);
  return average;
}


void setup() {
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Calibration(13);
  Serial.println(sensorMin);
  Serial.println(sensorMax);
  digitalWrite(13, LOW);
}

void loop() {
  int i = 0;
  if(i == 1){
    int input = analogRead(sensorPin);
    ave = Smoothing(input);
    ave = constrain(ave, sensorMin, sensorMax);
    ave = map(ave, sensorMin, sensorMax, 0, 255);
    //Serial.println(ave);
    if(ave < 120){
      digitalWrite(ledPin, HIGH);
    }else{
      digitalWrite(ledPin,LOW);
    }
  }else{
    sum2 = sum();
    int input = analogRead(sensorPin);
    ave = Smoothing2(input,sum2);
    ave = constrain(ave, sensorMin, sensorMax);
    ave = map(ave, sensorMin, sensorMax, 0, 255); 
    Serial.println(ave);
    if(ave < 60){
      digitalWrite(ledPin, HIGH);
    }else{
      digitalWrite(ledPin,LOW);
    }  
  }
}
