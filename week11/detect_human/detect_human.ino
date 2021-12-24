#define PIROUT 2
#define POTOUT A0
#define LEDPIN 3
void setup()
{
  Serial.begin(9600); 
  pinMode(PIROUT, INPUT);
  pinMode(LEDPIN, OUTPUT);
}
void loop()
{
  int light = analogRead(POTOUT);
  Serial.println(light);
  
  if(light > 300){
    digitalWrite(LEDPIN,LOW);
  }else{
    if(digitalRead(PIROUT)==HIGH){
      Serial.println("Some body is here");
      digitalWrite(LEDPIN,HIGH);
    }
    else{
      Serial.println("Nothing Detected by PIR Sensor");
      digitalWrite(LEDPIN,LOW);
    }
    delay(1000);
  }
}
