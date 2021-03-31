 #include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
#define TRIGGERPIN D1
#define ECHOPIN D2
#define ir D5
WidgetLCD lcd(V1);
char auth[] = ""; 
int water_pump=13;
int buzzer=15;

char ssid[] = "";
char pass[] = "";
int threshold=70;

// V1 LED Widget is blinking


void setup()
{
  Serial.begin(9600); 
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Blynk.begin(auth, ssid, pass);
  lcd.clear();
  lcd.print(0, 0, "Distance:");
  pinMode(D5,INPUT);
  pinMode(water_pump,OUTPUT);
  pinMode(buzzer,OUTPUT);
}

void loop()
{
  lcd.clear();
  lcd.print(0, 0, "Distance:");
  digitalWrite(TRIGGERPIN, LOW);

  delayMicroseconds(3);

  digitalWrite(TRIGGERPIN, HIGH);

  delayMicroseconds(12);

  digitalWrite(TRIGGERPIN, LOW);

  float duration = pulseIn(ECHOPIN, HIGH);

  float distance = (duration/2) / 29.1;

  Serial.print(distance);

  Serial.println("Cm");

  lcd.print(9,0, distance);
  lcd.print(0,1,"IR sensor:"+String(digitalRead(D5)));
  Blynk.run(); 
  if(distance<threshold){
  lcd.print(0,0,"Somebody entered");
  lcd.print(0,1,"Somebody entered");
  delay(10000);
  }
}
