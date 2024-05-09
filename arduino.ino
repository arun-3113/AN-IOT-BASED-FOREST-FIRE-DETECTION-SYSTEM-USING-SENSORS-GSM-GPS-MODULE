#include <dht.h>
#include <dht.h>  // Include library
#define alcohol A2  // Defines pin number to which the sensor is connected
dht DHT;      // Creates a DHT object

#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
SoftwareSerial mySerial(6,7);
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int gas = A0;


void setup() {
   Serial.begin(9600);    
   mySerial.begin(9600);
   pinMode(2,INPUT);//ir
   pinMode(A0,INPUT);
   //attachInterrupt(digitalPinToInterrupt(2), change, LOW);
   pinMode(13,OUTPUT);//buzzer
   digitalWrite(13,HIGH);delay(500);
   digitalWrite(13,LOW);delay(500);
}

void loop() {

  int readData = DHT.read11(alcohol);
  int temp = DHT.temperature;  // Read temperature
  float h = DHT.humidity;   // Read humidity
  int Fire = !digitalRead(2);
  int Gas = analogRead(A0);

 
  Serial.print(" temp :");
  Serial.println(temp);
  
  Serial.print(" Fire :");
  Serial.println(Fire);
 
  Serial.print(" Gas :");
  Serial.println(Gas);

  
 if (Fire == 1)
   { 
    digitalWrite(13,HIGH);delay(2000);digitalWrite(13,LOW);delay(2000);
   }
   
    else if (Gas > 350)
   {
    
    digitalWrite(13,HIGH);delay(2000);digitalWrite(13,LOW);delay(2000);
   
   } 
   else if (temp > 38)
   {
    digitalWrite(13,HIGH);delay(2000);digitalWrite(13,LOW);delay(2000);
   }

  String data= String(temp)+"@"+String(Gas)+"#"+String(Fire)+"$";
  Serial.println(data);
  delay(100);
   
   
   
 if(Fire == 1)
{
     MakeCall1();
     delay(15000);
     MakeCall();
     delay(150000);
    SendMessage();
    delay(15000);
    SendMessage1();
     delay(15000);
    Serial.print("EMERGENCY!!!!!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EMERGENCY!!!!!");
    lcd.setCursor(0,1);
    lcd.print("SMS/CallingSend");
    Serial.println("Received");
}
  else  if (Gas > 450) 
  {            
   digitalWrite(13,HIGH);
   delay(1000);
  }   
 else
 {
digitalWrite(13,LOW);
//Serial.println("Normal State");
lcd.clear();
lcd.setCursor(0,0);
//lcd.print("Normal State");
delay(1000);
} 
}
void SendMessage()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+918838647593\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Emergency Alert Forest Fire Detected!!!!!!");// The SMS text you want to send
delay(1000);
mySerial.println("https://maps.app.goo.gl/F7Tk9smy7FPHWVW59");
delay(1000);
mySerial.println((char)26);// ASCII code of CTRL+Z

delay(1000);

//mySerial.println((char)26);// ASCII code of CTRL+Z

}
void SendMessage1()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=2"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+918838647593\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Emergency Alert Forest Fire Detected!!!");
delay(1000);
mySerial.println("Lat : 12.922915, Log : 80.127457");
delay(1000);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
void MakeCall()
{
  mySerial.println("ATH");
  delay(1000);
  mySerial.println("ATD+918838647593;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  delay(1000);
  mySerial.println("Calling  "); // print response over serial port
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CALLING");
  lcd.setCursor(0, 1);
  lcd.print("+919344887029");
  Serial.println("918838647593");
}
void MakeCall1()
{
  mySerial.println("ATH");
  delay(1000);
  mySerial.println("ATD+918838647593;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  delay(1000);
  mySerial.println("Calling  "); // print response over serial port
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CALLING");
  lcd.setCursor(0, 1);
  lcd.print("+918838647593");
  Serial.println("918838647593");
}
