#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

WidgetLCD lcd(V0);
char auth[] = "";//Add Authorisation Key from Blynk App Channel 


char ssid[] = "";//Add WiFi name
char pass[] = "";//Add Password (To be Left Empty for Open Networks)
#define DHTPIN 0
int smokeA0 = A0;
int sensorThres = 100;
int threshold = 100;
int buzzer = D2; 

DHT dht(DHTPIN, DHT11);
BlynkTimer timer;
float t;

void sendSensor()
{
  t = dht.readTemperature();
  lcd.print(0,1,t);
}

void setup()
{
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);
  lcd.clear();
  dht.begin();
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); 
  timer.run();
  lcd.clear();
  int analogSensor = analogRead(smokeA0);
 lcd.print(0,0,"Smoke: "+String(analogSensor));
 lcd.print(0,1,"Temp: "+String(t));
 if(t>threshold && analogSensor>sensorThres){
    lcd.print(0,0,"Fire");
    lcd.print(0,1,"Fire");
    Serial.print("fire");
    delay(2000);
 }
 Serial.println("Temperature: " +String(t)+" Celsius");
 Serial.print("Smoke value ");
 Serial.println(analogSensor);
 // Checks if it has reached the threshold value
 delay(100); 
}
