int led = 12;
int pushButton = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(led,OUTPUT);
} 

void loop() {
  // put your main code here, to run repeatedly:
  //int buttonState = digitalRead(pushButton);
  //Serial.println(buttonState);
  //if(buttonState == 1){
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    delay(100);
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    delay(100);
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    delay(100);
    
    digitalWrite(led,HIGH);
    delay(300);
    digitalWrite(led,LOW);
    delay(300);
    digitalWrite(led,HIGH);
    delay(300);
    digitalWrite(led,LOW);
    delay(300);
    digitalWrite(led,HIGH);
    delay(300);
    digitalWrite(led,LOW);
    delay(300);
  
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    delay(100);
    
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    delay(100);
    
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    delay(1000);
  //}
}
