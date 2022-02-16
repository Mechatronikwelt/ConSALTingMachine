#include "CPhotodiode.h"
#include <Arduino.h>

CPhotodiode::CPhotodiode(int sensorPin_, CDosiermotor Dosiermotor_, int referenzLED_pin_) 
: sensorPin(sensorPin_), offset(2400), Dosiermotor(Dosiermotor_), referenzLED_pin(referenzLED_pin_), Richtwert_Dunkel(800), Richtwert_Hell(1000),
Anzahl_Motorschritte_nach_Einruch_der_Helligkeit_fuer_Kalibrierung(-10)
{}

int CPhotodiode::Helligkeit()
{
   return analogRead(sensorPin) - offset;
}

void CPhotodiode::Lochscheibe_Kalibrierung()
{
   int sensorValue = 0;
//    Serial.println(sensorValue);
   sensorValue = Helligkeit();
   ReferenzLED_on();

   Dosiermotor.StepperOn(); 

   do  // erst zurück ins dunkle fahren
   {
       Dosiermotor.schrittanzahl_verfahren(1);
       sensorValue = Helligkeit();
    //    Serial.println(sensorValue);
   } while(sensorValue > Richtwert_Dunkel);

   while(sensorValue < Richtwert_Hell) // dann richtig kalibrieren
   {
       Dosiermotor.schrittanzahl_verfahren(-1);
       sensorValue = Helligkeit();
    //    Serial.println(sensorValue);
   }
   
   Dosiermotor.schrittanzahl_verfahren(Anzahl_Motorschritte_nach_Einruch_der_Helligkeit_fuer_Kalibrierung);
   
   Dosiermotor.StepperOff(); 
   ReferenzLED_off();

}

void CPhotodiode::ReferenzLED_on()
{
    digitalWrite(referenzLED_pin, HIGH);
};
void CPhotodiode::ReferenzLED_off()
{
    digitalWrite(referenzLED_pin, LOW);
};

