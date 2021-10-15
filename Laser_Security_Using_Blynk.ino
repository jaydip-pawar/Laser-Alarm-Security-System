#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "5NVlygsunNKxfBM6Ypq9CEdE7Yn4m0Pg";

////////////////////////////////////
// SSID and PASSWORD
////////////////////////////////////
char ssid[] = "olaPrimeDriver";
char pass[] = "olasmart";

////////////////////////////////////
// PIN DECLERATION
////////////////////////////////////

const int ledPin = D2;     // This is GPIO4 pin which is labeled as D2 on NodeMCU
const int buzzerPin = D1;   // This is GPIO5 pin which is labeled as D1 on NodeMCU
const int ldrPin = D0;    // LDR data pin connected to Analog pin 0
WidgetLED led1(V1);
WidgetLED led2(V2);
WidgetLED led3(V3);

void setup () 
{
  
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  pinMode(ledPin, OUTPUT);     

  pinMode(buzzerPin, OUTPUT);

  led1.on();
    
}

////////////////////////////////////
// Send Email
////////////////////////////////////

void sendEmail()
{
  String body = String("Laser Breaked!!!");
  Blynk.email("jaydippawar30@gmail.com", "Subject: Alert", body);
}

////////////////////////////////////
// Notification
////////////////////////////////////

void notification()
{
  Blynk.notify("Laser is breaked!!!!");
}

void loop() 
{
  
  int ldrStatus = analogRead(ldrPin);
  int i=0;

  if (digitalRead(ldrPin)) {     //if the value of buzzer goes higher and equal to 20 then buzzer will beep else no
    led1.off();
    led2.on();  
    led3.on();
    sendEmail();
    notification();
    a:
     
      tone(buzzerPin, 1000); 
      
      digitalWrite(ledPin, HIGH);
      
      delay(100);
      
      noTone(buzzerPin);
      
      digitalWrite(ledPin, LOW);
      
      delay(100);
      i++;
      
      if(i<50)
      {
        goto a;
      }
      
    Serial.println("----------- ALARM ACTIVATED -----------");

  }
  else 
  {
    
  led2.off();
  led1.on();
    noTone(buzzerPin);
  
    digitalWrite(ledPin, LOW);
  
    Serial.println("ALARM DEACTIVATED");
  
  }

  Blynk.run();

}
