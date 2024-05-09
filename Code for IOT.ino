#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
 
char ssid[] = "Redmi 10A";   // your network SSID (name)
char pass[] = "www12345";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
 
unsigned long myChannelNumber = 2535861;
const char * myWriteAPIKey = "ETTW9TBERNBDUJQ1";
String myStatus = "";
 
void setup()
{
  Serial.begin(9600);  // Initialize serial
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}
 
void loop()
{
 
  String data;
  while (Serial.available())
  {
    data = Serial.readStringUntil('@');
    data.trim();
    String temp = data;
    data = Serial.readStringUntil('#');
    data.trim();
    String Gas = data;
    data = Serial.readStringUntil('%');
    data.trim();
    String Fire = data;
  
 
Serial.print("temp level :");
Serial.println(temp);
Serial.print("Gas Sensor:");
Serial.println(Gas);
Serial.print("Fire Level:");
Serial.println(Fire);


 
 
    // set the fields with the values
    ThingSpeak.setField(1, temp);
    ThingSpeak.setField(2, Gas);
    ThingSpeak.setField(3, Fire);

   
 
 
 
    ThingSpeak.setStatus(myStatus);
 
    // write to the ThingSpeak channel
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey );
    if (x == 200)
    {
      Serial.println("Channel update successful.");
    }
    else
    {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
 
    delay(100); // Wait 20 seconds to update the channel again
  }
}
