#include<SoftwareSerial.h>

SoftwareSerial mycode(34,35);
 void setup() 
 {
  Serial.begin(115200);
  mycode.begin(9600);
 }
 
void loop() 
{
   String message = mycode.readStringUntil('\r');
   Serial.println(message);
}
