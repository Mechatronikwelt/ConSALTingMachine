#include "CDosiermotor.h"

CDosiermotor::CDosiermotor(int _motor_pin_1, int _motor_pin_2,
                         int _motor_pin_3, int _motor_pin_4)
                        : motor_pin_1(_motor_pin_1), 
                        motor_pin_2(_motor_pin_2), 
                        motor_pin_3(_motor_pin_3), 
                        motor_pin_4(_motor_pin_4),
                        Uebersetzung_Zahnrad (4.5f),
                        Anzahl_Schritte_pro_Umdrehung(200), 
                        Schrittmotor(Anzahl_Schritte_pro_Umdrehung, motor_pin_1, motor_pin_2, motor_pin_3, motor_pin_4),
                        Anzahl_Dosiereinheiten_pro_Umdrehung(6), 
                        Salzmenge_pro_Dosiereinheit_in_mg(380),
                        IN1(0), IN2(0), IN3(0), IN4(0)
                         
{
    Schrittmotor.setSpeed(100); 
    StepperOff();
}

void CDosiermotor::dosieren(float Salzmenge_in_mg)
{
    float stepsProLoch = (float)Anzahl_Schritte_pro_Umdrehung / (float)Anzahl_Dosiereinheiten_pro_Umdrehung; // 60 Grad

    float Dosierloch_counter = Salzmenge_in_mg / Salzmenge_pro_Dosiereinheit_in_mg; // wie oft die 60 Grad gefahren werden müssen
    
    //Auf oder Abrunden:
    if((Dosierloch_counter - (int)Dosierloch_counter) < 0.5)
      Dosierloch_counter = (int)Dosierloch_counter;
    else
      Dosierloch_counter = (int)Dosierloch_counter + 1;

    int Motorsteps = Dosierloch_counter * stepsProLoch * Uebersetzung_Zahnrad;

    // Motor anschalten --> Dosieren --> Motor Ausschalten:
    Serial.printf("Dosiervorgang für %f mg Salz:\n", Salzmenge_in_mg);
    StepperOn();
      Serial.print("Motor macht ");
      Serial.print(Motorsteps);
      Serial.println(" steps");
	  schrittanzahl_verfahren(Motorsteps);
    StepperOff();
 
}

void CDosiermotor::schrittanzahl_verfahren(int schritte)
{
  Schrittmotor.step(schritte);
}


void CDosiermotor::StepperOff()
{
  delay(100);     //Warten damit der Zeiger nicht die Position überschiesst
  StepperSave();  //Motor zustand Speichern

  digitalWrite(motor_pin_1, LOW); //Motorwicklungen ausschalten
  digitalWrite(motor_pin_2, LOW);
  digitalWrite(motor_pin_3, LOW);
  digitalWrite(motor_pin_4, LOW);
}

/************************(Funktion zum einschalten des Motores)****************************/
void CDosiermotor::StepperOn()
{
  digitalWrite(motor_pin_1, IN1); //Motorwicklungen letzter Zustand wiederherstellen
  digitalWrite(motor_pin_2, IN2);
  digitalWrite(motor_pin_3, IN3);
  digitalWrite(motor_pin_4, IN4);
  delay(100);
}

/*************(Funktion zum Speichern der bestromten Wicklungen des Motores)***************/
void CDosiermotor::StepperSave()
{
  IN1 = digitalRead(motor_pin_1); //Zustand Lesen und Speichern
  IN2 = digitalRead(motor_pin_2);
  IN3 = digitalRead(motor_pin_3);
  IN4 = digitalRead(motor_pin_4);
}