#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{  
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
//  if (isnan(h) || isnan(t) || isnan(f)) 
//  {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//  }

 Serial.print("{\"Temperature_C\":");
 Serial.print(t);
 Serial.println(",");
 Serial.print("\"Temperature_F\":");
 Serial.print(f);
 Serial.println(",");
 Serial.print("\"Humidity\":");
 Serial.print(h);
 Serial.println(",");
 Serial.println("}");
 Serial.println();
}
