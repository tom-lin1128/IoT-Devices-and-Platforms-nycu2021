int melody[10] = {0};
int pushButton = 2;
int counter = 0;


int lastButtonState = LOW; 
int buttonState; 



unsigned long debounceDelay = 50; 
unsigned long lastDebounceTime = 0;

unsigned long timer = 0;


void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
  pinMode(pushButton , INPUT);
}

void loop() {

  int reading = digitalRead(pushButton);
  int sensorReading = analogRead(A0);
  //Serial.println(sensorReading);
  int thisPitch = map(sensorReading, 0, 1024, 120, 1500);


  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH && counter < 10) {
          melody[counter] = thisPitch;
          counter += 1;
          Serial.println(counter);
      }
    }
  }
  //Serial.println(buttonState);

  if(lastButtonState == LOW && buttonState == HIGH){
     timer = millis();
  }



  if (buttonState == HIGH && ( (millis()-timer) > 5000) && counter == 10) {
        Serial.println("restart");
        for(int i = 0;i < 10; i++){
            tone(8,melody[i],100);
            delay(1000);
        }
        timer=millis();
  }
  
  lastButtonState = reading;
}
