#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{  
  Serial.begin(9600);
  dht.begin();
}
   
void loop() 
  {
  // Wait a few seconds between measurements.
  int A = analogRead(A0);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if(A>600)
  {
  Serial.print(t);
  Serial.print(h);
  delay(2000);
  }
}
