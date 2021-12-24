#include <SoftwareSerial.h>
#define WiFi_TX 2
#define WiFi_RX 3
int red = 11;
int green = 12;
int blue = 13;
SoftwareSerial WiFi_Serial(WiFi_TX, WiFi_RX);

#define SSID "LAPTOP-38QQ92E4 0218"
#define PASS "31Q66k4/"

#define IP "api.thingspeak.com"

#define sensorPower 7
#define sensorPin A0

int val = 0;

String GET = "GET /update?key=5J14GFCRCJWMAADE";

int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000; //sample 30s
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup(){
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  starttime = millis();
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  WiFi_Serial.begin(115200);
  WiFi_Send("AT");
  delay(1000);
  if(WiFi_Serial.find("OK")){
    Serial.println("RECEIVED:OK");
    WiFi_Send("AT+CIPMUX=0");
    delay(1000);
    if(WiFi_Serial.find("OK")){
      Serial.println("RECEIVED: OK");
    }

    while(!connectWiFi());
  }
  else{
    Serial.println("NO RESPONSE!");
  }
}

boolean connectWiFi(){
  WiFi_Serial.println("AT+CWMODE=1");
  delay(1000);
  String cmd="AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  WiFi_Send(cmd);
  delay(1000);
  if(WiFi_Serial.find("OK")){
    Serial.println("RECEIVED: OK");
    return true;
  }
  else{
    Serial.println("RECEIVED: Error");
    return false;
  }
}

void loop() {
  double Hum = 66;
  double Temp = 20.5;
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;
  if((millis()-starttime) >= sampletime_ms){
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio, 2) + 520*ratio + 0.62;
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
  int level = readSensor();
  Serial.print("Water level: ");
  Serial.println(level);

  String CC, LL;
  CC = String(concentration);
  LL = String(level); 
  updateDHT11(CC, LL);
  delay(5000);
}

int readSensor(){
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}

void updateDHT11(String T, String H){
  String cmd = "AT+CIPSTART=\"TCP\",\""; //建立TCP連線
  cmd += IP;
  cmd += "\",80";
  WiFi_Send(cmd);
  delay(1000);
  if(WiFi_Serial.find("ERROR")){
    Serial.println("RECEIVED: TCP Connect Error");
    return;
  }
  cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";
  WiFi_Serial.print("AT+CIPSEND="); //傳送資料的指令
  WiFi_Serial.println(cmd.length()); //資料的長
  if(WiFi_Serial.find(">")){      //確定WiFi模組有接收到指令
    Serial.print(">");
    Serial.print(cmd);
    WiFi_Serial.print(cmd);      //傳送資料
    delay(1000);
    if(WiFi_Serial.find("OK")){
      Serial.println("RECEIVED: SEND OK");
    }
    else{
      Serial.println( "RECEIVED: SEND Error_2" );
    }
  }
  else{
    Serial.println( "RECEIVED: SEND Error" );
  }
}
void WiFi_Send(String cmd){
  Serial.print("SEND: ");
  WiFi_Serial.println(cmd);
  Serial.println(cmd);
}
