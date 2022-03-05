#include<WiFi.h>
#include<SoftwareSerial.h>

SoftwareSerial meraserial (28,35); // rx and tx
// Update these with values suitable for your network.
const char* ssid = "coco";
const char* password = "yougotitdidyou";
void setup_wifi() 
{
    delay(10000);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  meraserial.begin(9600);
//  Serial.setTimeout(500);// Set time out for 
  setup_wifi();
}

void loop() {
   String message = meraserial.readStringUntil('\r');
   Serial.println(message);
   delay(1000);
 }
