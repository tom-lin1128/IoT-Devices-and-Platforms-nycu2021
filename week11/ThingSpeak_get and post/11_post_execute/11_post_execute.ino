#include <SoftwareSerial.h>
#define WiFi_TX 8
#define WiFi_RX 9
#define IP "api.thingspeak.com"
SoftwareSerial WiFi_Serial(WiFi_TX,WiFi_RX);
int flag = 0;
String uri;
String postMessage;
int led=13;
char Headers[] = "POST /talkbacks/44534/commands.json HTTP/1.1\r\nHost: api.thingspeak.com\r\nContent-Type: application/x-www-form-urlencoded\r\nConnection: close\r\nContent-Length: 52\r\n\r\napi_key=A7ZMROX78SOU5ZD3&command_string=ON&position=1";;

//請輸入自己WiFi熱點的名稱
#define SSID "LAPTOP-38QQ92E4 0218" // Use you own SSID

//請輸入自己WiFi熱點的密碼
#define PASS "31Q66k4/" // Use you own Password
  
  
void setup() {
  String TalkBack_ID = "44534";         // Use you own TalkBack ID
  String API_Key = "A7ZMROX78SOU5ZD3";  // Use you own API Key
  //String postStr;
   pinMode(led,OUTPUT);
   digitalWrite(led, LOW);
   Serial.begin(9600);          // PC Arduino Serial Monitor
   WiFi_Serial.begin(115200);   // Arduino to ESP01 Communication // RXD - TX1, TXD - RX1
   while(!esp01Check());        // Check if ESP01 AT command works or not
   while(!connectWiFi());       // Check WiFi connection
   uri = "/talkbacks/"+TalkBack_ID+"/commands/execute?";
   postMessage = "api_key=" + API_Key;
   char *postStr = postCommand(uri, postMessage);
   talkBackSendCommand(postStr); // Sent Get request via ESP01 
   // if you want to check message to debug, comment out the following code. When you down, please recomment.
//   checkMessage();
   checkHttpStatus();// Check command string to determine if turn on the LED
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


void talkBackSendCommand(char* getStr){
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
      cmd += String(227);
      cmd+="\r\n";
      WiFi_Serial.println(cmd); 
      if(WiFi_Serial.find(">")){
        Serial.println("AT+CIPSEND OK");
        Serial.println(Headers);
        WiFi_Serial.println(Headers); //傳送資料
      }
      else{
        Serial.println("AT+CIPSEND Fail");
        //while(1);
      }   
//        
    }
    else{                                   // If returns error in TCP Connection
      Serial.println("AT+CIPSTART Fail");   // Display error msg to PC
      //while(1);
    }
    WiFi_Serial.println("AT+CIPCLOSE");  // Close the connection
}   

void checkHttpStatus(){
  if (WiFi_Serial.find("200")){
    Serial.println("Success");
    digitalWrite(led, HIGH);
  }
  else{
    Serial.println("Fail");
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

char* postCommand (String uri, String postMessage){
//    postMessage += "&headers=false";
    //postMessage +=  "\r\ncommand_string=LED_ON\r\nposition=1\r\n";
    /*String Headers = String("POST ") + uri + String(" HTTP/1.1\r\n") +
                    String("Host: api.thingspeak.com\r\n") +
                    String("Content-Type: application/x-www-form-urlencoded\r\n") +
                    String("Connection: close\r\n") +
                    String("Content-Length: ") + String(postMessage.length()) +
                    String("\r\n\r\n");
                    //String("command : LED_ON\r\n");*/
    //Headers[224] = "POST /talkbacks/44534/commands/execute? HTTP/1.1\r\nHost: api.thingspeak.com\r\nContent-Type: application/x-www-form-urlencoded\r\nConnection: close\r\nContent-Length: 24\r\n\r\napi_key=A7ZMROX78SOU5ZD3&command_string=LED_ON&position=1";
    //Serial.println(Headers);
    delay(1000);
    char * a;
    return a;
}
