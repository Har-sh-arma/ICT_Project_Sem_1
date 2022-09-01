#include<WiFi.h>
#include<String.h>
#define RXp2 16
#define TXp2 17

const char* ssid     = "Superman";
const char* password = "AGT007110";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Set your Static IP address
IPAddress local_IP(192,168,29,20);
// Set your Gateway IP address
IPAddress gateway(192,168,29,1);   

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(1,0,0,1);   //optional
IPAddress secondaryDNS(1,1,1,1); //optional

void setup() {
  Serial.begin(115200);
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  delay(10000);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  //acquiring data from Arduino
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
}

void loop(){

  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
       digitalWrite(18,HIGH);
       delay(1000);
       digitalWrite(18,LOW);
       String input = Serial2.readString();
       String data="";
       String data_1="";
       for(int i =input.length()-5;i<input.length();i++)
       {
          data= data+input[i];
       }
       for(int i =input.length()-10;i<input.length()-5;i++)
       {
          data_1 = data_1+input[i];
       }
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,

        
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.print("<!DOCTYPE html><html lang=""en""><head><meta http-equiv=""Content-Type"" content=""text/html; charset=windows-1252""><title>Physical Condidion</title>");
            client.print("<style>body{background-image:url(""https://wallpaperaccess.com/full/402525.jpg"");background-size:cover;background-attachment: fixed;}");
            client.print(".wrapper{display:grid;grid-template-columns:1fr 2fr 2fr 4fr 1fr;grid-auto-rows:90px;}");          
            client.print(".wrapper > div{border:1px black solid;}");
            client.print("#RPCS{top:0;left:0;padding: 10px;position: fixed;color : transparent;background-image: url(""https://wallpaperaccess.com/full/402525.jpg"");-webkit-background-clip: text;background-size:cover;background-attachment: fixed;width:100%;text-align: center;vertical-align: text-top;font: bold small-caps 100px Georgia, serif;}");
            client.print("#cover{top:0;left:0;padding: 10px;position:fixed;color : transparent;background-color:#000;width:100%;text-align: center;vertical-align: text-top;font: bold small-caps 100px Georgia, serif;opacity: 0.8;z-index: -1;}");
            client.print("#card{border:none;border-radius: 25px;grid-column: 2/5;grid-row: 4/7;background-color: black;opacity: 0.8;z-index: 1;}");
            client.print("#text{padding:30px;border:none;grid-column: 2/5;grid-row: 4/7;color : transparent;background-color:#ABABAB ;-webkit-background-clip: text;background-size:cover;background-attachment: fixed;font: bold small-caps 90px Georgia, serif;z-index: 2;}");
            client.print("</style></head>""<body><div id=""RPCS"">Physical Conditions</div><div id =""cover"">Physical Conditions</div><div class=""wrapper""><div id=""card""></div><div id=""text"">Temperature :"+data_1+"&#186;C Humidity :"+data+"%</div>");
            client.print("<div id = ""highlight""></div></div></body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    if(client)
    {
    Serial.println("Client disconnected.");
    }
    Serial.println("");
  }
}
