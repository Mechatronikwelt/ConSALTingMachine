#include <Arduino.h>
#include "CWaegezelle.h"
#include "CDosiermotor.h"
#include "CStatusLED.h"
#include "CPhotodiode.h"
#include "CBluetoothCommunication.h"
#include "CSensorData.h"

CWaegezelle mWaegezelle(14, 12);
CDosiermotor mDosiermotor(19, 23, 18, 5);
CStatusLED mStatusLED(32);

int referenzLED_pin = 25;
CPhotodiode mPhotodiode(4, mDosiermotor, referenzLED_pin);
int taster_pin = 33;

Preferences preferences;

CBluetoothCommunication mBluetoothCommunication;
CSensorData mSensorData;
float salz_pro_l_in_g;      
float wassermenge_in_ml = 0;

void salzkonzentration_laden()
{
    preferences.begin("az", false);
   
    salz_pro_l_in_g = (float)preferences.getFloat("salz_pro_l_in_g\n", 10.0f); //es werden standardmäßig 10g pro Liter dosiert
    Serial.printf("salzkonzentration geladen: %f\n", salz_pro_l_in_g);
   
};

void salzkonzentration_speichern()
{
    preferences.putFloat("salz_pro_l_in_g", salz_pro_l_in_g); //Save counter variable under "File" Start   

    preferences.end(); //Quit Preferences
    Serial.printf("salzkonzentration gespeichert: %f\n", salz_pro_l_in_g);
};

void Sensordaten_senden()
{ //Knut
    mSensorData.mSaltAmount = mWaegezelle.get_salztank_fuellstand_in_g(); // setzt Salztankfuellstand
    mSensorData.mPressure = wassermenge_in_ml;

    mBluetoothCommunication.setSensorData(mSensorData);

}

void setup() {

  Serial.begin(9600);
  pinMode(referenzLED_pin, OUTPUT);
  pinMode(mPhotodiode.sensorPin, INPUT);
  pinMode(taster_pin, INPUT); 
// w.salztank_fuellstand_speichern();
  mWaegezelle.salztank_fuellstand_laden();
  
  
  salzkonzentration_laden();

    // w.salztank_fuellstand_speichern();
    // salzkonzentration_speichern();

  mStatusLED.status_setzen(Gruen); //soll als test am anfang gruen leuchten

  mPhotodiode.Lochscheibe_Kalibrierung();
    
  mWaegezelle.LoadCell.begin();
    // long stabilisingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilising time
    // w.LoadCell.start(stabilisingtime);
    if (mWaegezelle.LoadCell.getTareTimeoutFlag()) {
        Serial.println("Tare timeout, check MCU>HX711 wiring and pin designations");
    }
    else {
        mWaegezelle.LoadCell.setCalFactor(1.0); // user set calibration value (float)
        Serial.println("Startup + tare is complete");
    }


    while (!mWaegezelle.LoadCell.update());
    mWaegezelle.calibrate();

  mBluetoothCommunication.init();
  Sensordaten_senden();
}

int taster_status = LOW;    // taster gedrückt? --> HIGH
bool first_press_flank = false; // flanke zum überprüfen, ob taster bei HIGH gedrückt gehalten wird

int doubletap_time = 150; //ms --> Zeit innerhalb der doubletab erfolgen muss
int hold_time = 300; //ms --> Zeit die der Taster min. für hold gedrückt gehalten werden muss

long pressed_timestamp = 0; // wann genau der taster gedrückt wurde

bool hold = false;     
bool doubletab = false;
bool singletab = false;

bool hold_printed= false; // um sicherzustellen, dass hold nur 1x in Konsole geprinted wird
int hold_led_counter = 0; //dummy

void reset_taster(); // resettet alle taster Werte & Zeiten

int at_singletab();
int at_doubletab();
int at_hold();



void loop()
{
  Sensordaten_senden();
 

  taster_status = digitalRead(taster_pin);
  if(taster_status == HIGH) // Beim drücken
  {
    delay(5); //entprellen
    taster_status = digitalRead(taster_pin);

    if(taster_status == HIGH && first_press_flank == false) // Beim ersten mal drücken
    {
      pressed_timestamp = millis();
      first_press_flank = true;
    }
    if(taster_status == HIGH && first_press_flank == true) // Beim gedrückt halten
    {
      if ((millis() - pressed_timestamp) > hold_time) {
        if(!hold_printed)
        {
          at_hold();

          hold_printed = true;
          usleep(500000); // unterbinden von direkt anschliessendem Druecken nach hold 
        }
      }
    }
  }

  if(taster_status == LOW && first_press_flank == true) // Beim  loslassen 
  {
    if (hold)
    {
      reset_taster();
    }
    else
    {
      long waiting_for_doubletab_time = millis();
      while(millis() - waiting_for_doubletab_time < doubletap_time) // schauen ob statt singletab doch ein doubletab gemacht wird
      {
        taster_status = digitalRead(taster_pin);
        if(taster_status == HIGH)
        {
          delay(5); //entprellen
          taster_status = digitalRead(taster_pin);

          if(taster_status == HIGH && first_press_flank == true)
          {
            at_doubletab();
            usleep(500000); // unterbinden von direkt anschliessendem Druecken nach doubletab

            break;
          }
        }
      }

      if(!doubletab) // kein doubletab --> singletab
      {
        at_singletab();
      }

      reset_taster();
    }
  }

}

void reset_taster()
{
 first_press_flank = false;

 pressed_timestamp = 0;

 hold = false;
 doubletab = false;
 singletab = false;

 hold_printed= false;
};

bool Dosiervorgang()
{
  if (wassermenge_in_ml > 0 || wassermenge_in_ml > mWaegezelle.max_Fuellmenge_in_ml)
  {  
    float Salzmenge_in_mg = salz_pro_l_in_g * wassermenge_in_ml; // in milligramm
      Serial.println("Salztankfuellstand in g: ");
      Serial.println(mWaegezelle.get_salztank_fuellstand_in_g());      
      Serial.println("Wasserfuellstand in g: ");
      Serial.println(Salzmenge_in_mg / 1000);      
    if((Salzmenge_in_mg / 1000) > mWaegezelle.get_salztank_fuellstand_in_g()) // nicht genug Salz im Tank
    {
      mStatusLED.status_setzen(Rot);
      return false;
    }

    // Dosieren:    
    mStatusLED.status_setzen(Gruen_schwach);
    mDosiermotor.dosieren(Salzmenge_in_mg);
    mWaegezelle.salztank_abrechnen(Salzmenge_in_mg / 1000);
      Serial.println("Salztank nach abrechnung in g: ");
      Serial.println(mWaegezelle.get_salztank_fuellstand_in_g());
    mWaegezelle.salztank_fuellstand_speichern();
    Sensordaten_senden();
    return true;
  }

  else
  {
    Serial.println("Messwert zu klein oder zu groß");
    mStatusLED.status_setzen(Rot);
    sleep(2);
    if(mWaegezelle.get_salztank_fuellstand_in_g() > mWaegezelle.get_salztank_krit_fuellstand_in_g())
      mStatusLED.status_setzen(Gruen);
    else
      mStatusLED.status_setzen(Gelb);
    return false;
  }
};

int at_singletab() // Dosiermenge berechnen
{
  Serial.println("single press");     
  singletab = true;

  mStatusLED.status_setzen(Blau);
  float mw = mWaegezelle.messwert_wasser_in_g();

  if(mw < 0 || mw > 2000)
  {
    Serial.println("Messwert zu klein oder zu groß");
    mStatusLED.status_setzen(Rot);
    sleep(2);
  }
  else 
    wassermenge_in_ml = mw;

  if(mWaegezelle.get_salztank_fuellstand_in_g() > mWaegezelle.get_salztank_krit_fuellstand_in_g())
    mStatusLED.status_setzen(Gruen);
  else
    mStatusLED.status_setzen(Gelb);

  return 1;
};

int at_doubletab() // Salzfuellstand neu kalibrieren
{
  Serial.println("double press");
  doubletab = true; 

  mStatusLED.status_setzen(Weiss);


  float mw = mWaegezelle.salztank_fuellstand_kalibrierung();
  Serial.print("Salzfuellstand mw: ");
  Serial.println(mw);

  if(mw < 0 || mw > 2000)
  {
    Serial.println("Messwert zu klein oder zu groß");
    mStatusLED.status_setzen(Rot);
    sleep(2);
  }
  else
    mWaegezelle.salztank_fuellstand_speichern();

  if(mWaegezelle.get_salztank_fuellstand_in_g() > mWaegezelle.get_salztank_krit_fuellstand_in_g())
    mStatusLED.status_setzen(Gruen);
  else
    mStatusLED.status_setzen(Gelb);

  return 1;
};

int at_hold() // Dosieren
{
  Serial.println("hold press");
  hold = true;  

  Sensordaten_senden();

  if (Dosiervorgang() == false)
    return 0;

  mPhotodiode.Lochscheibe_Kalibrierung();

  // Statusanzeige des restlichen Salzgehalts:
  if(mWaegezelle.get_salztank_fuellstand_in_g() > mWaegezelle.get_salztank_krit_fuellstand_in_g())
    mStatusLED.status_setzen(Gruen);
  else
    mStatusLED.status_setzen(Gelb);
  
  return 1;
};
