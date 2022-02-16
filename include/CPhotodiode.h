#include <iostream>
#include "CDosiermotor.h"

class CPhotodiode
{
public:
    CPhotodiode(int sensorPin_, CDosiermotor Dosiermotor_, int referenzLED_pin_);
    void Lochscheibe_Kalibrierung();
    int sensorPin;

private:
    int offset;
    int Helligkeit();
    CDosiermotor Dosiermotor;
    int referenzLED_pin;
    int Richtwert_Dunkel;
    int Richtwert_Hell; 
    int Anzahl_Motorschritte_nach_Einruch_der_Helligkeit_fuer_Kalibrierung;

    void ReferenzLED_on();
    void ReferenzLED_off();

};
