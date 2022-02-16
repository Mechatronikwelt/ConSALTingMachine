#include <iostream>
#include <Stepper.h>
#include <Arduino.h>

#ifndef CDosiermotor_H
#define CDosiermotor_H

class CDosiermotor
{
public:
    CDosiermotor(int _motor_pin_1, int _motor_pin_2,
                int _motor_pin_3, int _motor_pin_4);
    
    void dosieren(float Salzmenge_in_g);

    void schrittanzahl_verfahren(int schritte);

    void StepperOff();
    void StepperOn();

private:

    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;   

    float Uebersetzung_Zahnrad;

    int Anzahl_Schritte_pro_Umdrehung; 
    Stepper Schrittmotor;
    int Anzahl_Dosiereinheiten_pro_Umdrehung;
    float Salzmenge_pro_Dosiereinheit_in_mg;

    // Hilfsvariablen zum Abspeichern der bestromten Wicklungen beim Ausschalten
    bool IN1;
    bool IN2;
    bool IN3;
    bool IN4;

    void StepperSave();
};

#endif