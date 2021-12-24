int guess_number;
int guess = -1;
int y;
int buttonpin = 3;
int ledpin = 4;
int sensorpin = A0;
int sensorvalue = 0;
int buttonstate = 0;
int flag = 0;
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(buttonpin,INPUT);
  pinMode(ledpin,OUTPUT);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}



void loop() {
  sensorvalue = analogRead(sensorpin);
  buttonstate = digitalRead(buttonpin);
  if(buttonstate == HIGH && guess == -1){
    guess = sensorvalue;
    Serial.println(guess);
  }
  //Serial.println(buttonstate); 
  if(Serial.available()){
    guess_number = Serial.parseInt();
    y = Serial.parseInt();
    Serial.println(guess_number);
    flag = 1;
  }
  if(guess_number > 0){
    if(guess_number > guess && flag == 1){
      Serial.println("too big");
      flag = 0;
    }else if(guess_number < guess && flag == 1){
      Serial.println("too small");
      flag = 0;
    }else if(guess_number == guess && flag == 1){
      Serial.println("correct");
      digitalWrite(ledpin,HIGH);
      flag = 0;
    }
  }
}
