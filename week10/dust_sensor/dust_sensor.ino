int pin = 8;
int red = 11;
int green = 12;
int blue = 13;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000; //sample 30s
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  starttime = millis();//get the current time;
}

void loop() {
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) >= sampletime_ms) //if the sampel time = = 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0); // Integer percentage 0~100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
    // using spec sheet curve
    //Serial.print(ratio);
    Serial.print("concentration = ");
    Serial.print(concentration);
    Serial.println(" pcs/0.01cf");
    Serial.println("\n");
    
    if(concentration < 500){
      analogWrite(red,0);
      analogWrite(green,255);
      analogWrite(blue,0);
    }else if(concentration >= 500 && concentration < 1000){
      analogWrite(red,0);
      analogWrite(green,0);
      analogWrite(blue,255);
    }else{
      analogWrite(red,255);
      analogWrite(green,0);
      analogWrite(blue,0);
    }
      
    lowpulseoccupancy = 0;
    starttime = millis();
  }
}
