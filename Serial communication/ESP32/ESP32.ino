#include<WiFi.h>
#define RXp2 16
#define TXp2 17
// Update these with values suitable for your network.
const char* ssid = "Superman";
const char* password = "AGT007110";
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

void setup() 
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

//  Serial.setTimeout(500);// Set time out for 
  setup_wifi();
}
void loop() 
{
   Serial.println(Serial2.readString());
   delay(1000);
}
