#include <SoftwareSerial.h>
#define WiFi_TX 2
#define WiFi_RX 3
#define IP "api.thingspeak.com"
SoftwareSerial WiFi_Serial(WiFi_TX,WiFi_RX);
int flag = 0;
String TalkBack_ID = "40992";         // Use you own TalkBack ID
String API_Key = "Y1BPJ5W7WBWVIPPE";  // Use you own API Key
String getStr;
int led=13;

//請輸入自己WiFi熱點的名稱
#define SSID "TestWiFi" // Use you own SSID

//請輸入自己WiFi熱點的密碼
#define PASS "12345678" // Use you own Password
  
  
void setup() {
   pinMode(led,OUTPUT);
   digitalWrite(led, LOW);
   Serial.begin(9600);          // PC Arduino Serial Monitor
   WiFi_Serial.begin(115200);   // Arduino to ESP01 Communication // RXD - TX1, TXD - RX1
   while(!esp01Check());        // Check if ESP01 AT command works or not
   while(!connectWiFi());       // Check WiFi connection
   getStr = "GET /talkbacks/"+TalkBack_ID+"/commands/execute?api_key=" + API_Key +"\r\n";
   talkBackSendCommand(getStr); // Sent Get request via ESP01 
   // if you want to check message to debug, comment out the following code. When you down, please recomment.
//   checkMessage();
   checkExecuteLEDCommand(); // Check command string to determine if turn on the LED
}

void loop() {
  // put your main code here, to run repeatedly:

}

bool esp01Check(){
  WiFi_Serial.println("AT");
  delay(100);
  if (WiFi_Serial.find("OK")){
    Serial.println("esp01 check");
    return true;
  }
  else {
    Serial.println("esp01 is running");
    return false; 
  }
  delay(1000);
}


boolean connectWiFi() {
    // Connect to Wifi Function
    WiFi_Serial.println("AT+CWMODE=1\r\n"); // Setting Mode = 1
    delay(2000);
    String cmd = "AT+CWJAP=\"";         // Connect to WiFi
    cmd += SSID;                   // Replace ssid_name here
    cmd += "\",\"";
    cmd += PASS;                // Replace password here
    cmd += "\"\r\n";              
    
    Serial.println(cmd);                // Display Connect Wifi Command on PC
    WiFi_Serial.println(cmd);               // send Connect WiFi command to Rx1, Tx1 
    
    delay(10000);                       // wait for 10 sec
  
    WiFi_Serial.println("AT+CWJAP?");       // Verify Connected WiFi
    delay(100);
    if(WiFi_Serial.find("+CWJAP"))        
    {
      Serial.println("OK, Connected to WiFi.");         // Display Confirmation msg on PC
      return true;
    }
    else
    {
      Serial.println("Can not connect to the WiFi.");   // Display Error msg on PC
      return false;
    }
   
}


void talkBackSendCommand(String getStr){
   WiFi_Serial.println("AT+CIPMUX=0");
   delay(1000);
   if (WiFi_Serial.find("OK")){
    Serial.println("CIPMUX OK");
   }
   String cmd = "AT+CIPSTART=\"TCP\",\"";   // TCP connection with https://thingspeak.com server
    cmd += IP;
    cmd += "\",80";
    WiFi_Serial.println(cmd);                  // Send above command to Rx1, Tx1
    Serial.println(cmd);
    if(WiFi_Serial.find("OK")){                // If returns error in TCP Connection{ ]
      Serial.println("AT+CIPSTART OK");
      cmd = "AT+CIPSEND="; 
      cmd += String(getStr.length());
      cmd+="\r\n";
      WiFi_Serial.println(cmd); 
      if(WiFi_Serial.find(">")){
        Serial.println("AT+CIPSEND OK");
        Serial.println(getStr);
        WiFi_Serial.println(getStr); //傳送資料
      }
      else{
        Serial.println("AT+CIPSEND Fail");
        while(1);
      }       
    }
    else{                                   // If returns error in TCP Connection
      Serial.println("AT+CIPSTART Fail");   // Display error msg to PC
      while(1);
    }
    WiFi_Serial.println("AT+CIPCLOSE");  // Close the connection
}   

void checkExecuteLEDCommand(){
  if (WiFi_Serial.find("LED_ON")){
    Serial.println("Command:LED_ON");
    digitalWrite(led, HIGH);
  }
  else{
    Serial.println("Unknown command");
  }
}

void checkMessage(){
  if(WiFi_Serial.available()){
    String res;
    while(WiFi_Serial.available()){   
      res += WiFi_Serial.readString();
    }
    Serial.println("____________");
    Serial.println(res);
    Serial.println("____________");
   }
}
