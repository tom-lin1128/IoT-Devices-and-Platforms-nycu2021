#include <Servo.h>
int guess_number=0;
int y;
Servo myservo;  

int pos = 0;    

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  
}

void loop() {
  if(Serial.available()){
    myservo.write(pos); 
    guess_number = Serial.parseInt();
    y = Serial.parseInt();
    Serial.println(guess_number);
    if(guess_number >= 0 && guess_number <= 180){
    for (pos = 0; pos <= guess_number; pos += 1) {
      myservo.write(pos);             
      delay(40);                      
      }
    }else if(guess_number >= -180 && guess_number < 0){
      for (pos = -(guess_number); pos > 0; pos -= 1) { 
      // in steps of 1 degree
        myservo.write(pos);            
        delay(40);
      }       
    }else Serial.println("Invaild number clockwise : (1~180) counterclockwise : (-180 ~ 0)");
  }
}
