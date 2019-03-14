/* Made by: Alvaro Munhoz Mota
 * This project is a simple IoT application, where your
 * device turns on/off a relay connected to a water pump.
 * The objective is to water some plants while you're not
 * home.
 * 
 * The project uses the ESP8266 DeepSleep function, to
 * achieve a low power consumption. Time passed to DeepSleep
 * functions is in micro seconds!
 * The device will "wake up" from time to time, connect to
 * the internet, check the pump activation value, turn the
 * pump on for some time if it is the case, than will sleep
 * again.
 * It will consume something close to 5,5% of the power it would
 * use if it was 24h on.
 * 
 * To achieve the IoT communication, we use the ThingSpeak
 * platform, where we have a public channel containing 2 
 * fields.
 * The first field will store the pump activation variable.
 * The second one will store the pump status variable, so we
 * can know if the device obeyed the command properly.
 * 
 * The Serial messages are only usefull to check the
 * if everything is allright while you code.
 * Once it is done, you can remove them.
 */
#include "ThingSpeak.h"
#include "secrets.h" // Edit your secrets.h file with your keys and information.
#include <ESP8266WiFi.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
unsigned long irrigadorChannelNumber = SECRET_CH_ID;
unsigned int activatePumpFieldNumber = 1;
unsigned int pumpInformationFieldNumber = 2;
unsigned long counterChannelNumber = SECRET_CH_ID_COUNTER;
const char * myCounterReadAPIKey = SECRET_READ_APIKEY_COUNTER;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
unsigned int counterFieldNumber = 1;
unsigned int infoFieldNumber = 2;
/* In WeMos D1 mini, the pinout is different from 
 * Arduino IDE mapping.
 * You can see a nice table here:
 * https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
 * 
 * In this example, pin1 is the D1 from your board, and 5
 * in the code.
 */

int pin1 = 5;

void setup() {
  Serial.begin(115200);  // Initialize serial
  pinMode(pin1, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(pin1, LOW);
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  digitalWrite(BUILTIN_LED, HIGH);
  int statusCode = 0;
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected");
  }

  // Read in field 1 of the public channel
  int activatePumpInF = ThingSpeak.readFloatField(irrigadorChannelNumber, activatePumpFieldNumber);  

  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    if(activatePumpInF == 1){
      Serial.println(activatePumpInF);
      Serial.println("Pump On");
      digitalWrite(pin1, HIGH);
      ThingSpeak.writeField(irrigadorChannelNumber, infoFieldNumber, 1, myWriteAPIKey);
      delay(10000);
      digitalWrite(pin1, LOW);
      ThingSpeak.writeField(irrigadorChannelNumber, activatePumpFieldNumber, 0, myWriteAPIKey);
      delay(16000);
      ThingSpeak.writeField(irrigadorChannelNumber, infoFieldNumber, 0, myWriteAPIKey);
    }
    if(activatePumpInF == 0){
      Serial.println(activatePumpInF);
      Serial.println("Pump Off");
      digitalWrite(pin1, LOW);
      ThingSpeak.writeField(irrigadorChannelNumber, infoFieldNumber, 0, myWriteAPIKey);
    }
  }
  else{
    Serial.println(statusCode);
    Serial.println("Read Error");
    digitalWrite(pin0, LOW);
    ThingSpeak.writeField(irrigadorChannelNumber, activatePumpFieldNumber, 0, myWriteAPIKey);
    ThingSpeak.writeField(irrigadorChannelNumber, infoFieldNumber, 0, myWriteAPIKey);
  }
  Serial.println("Going to sleep!");
  ESP.deepSleep(10*60*1000000); // Sleep 10 min
  /* 
   *  You can change the first multiplying number for a different
   *  sleeping interval. For instance: ESP.deepSleep(60*60*1000000);
   *  would make your device sleep for 60 minuts (one hour).
   */
  
  delay(1000); // This delay is necessary for deepSleep working properly.
}
