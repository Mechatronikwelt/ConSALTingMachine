#include "CSalztank.h"
#include <Arduino.h>


CSalztank::CSalztank() : fuellstand_in_g(0.0f), max_fuellmenge_in_g(120.0f), kritische_fuellmenge_in_g(15.0f)
{

};

void CSalztank::fuellstand_speichern()
{
    preferences.putFloat("fuellstand_in_g", fuellstand_in_g); //Save counter variable under "File" Start   
    preferences.end(); //Quit Preferences

    Serial.printf("fuellstand gespeichert: %f\n", fuellstand_in_g);
};

void CSalztank::fuellstand_laden()
{
    preferences.begin("az", false);
    fuellstand_in_g = preferences.getFloat("fuellstand_in_g", 500.0f);

    Serial.printf("fuellstand geladen: %f\n", fuellstand_in_g);
};

// void CSalztank::fuellstand_senden()
// {
// 
//     // mSensorData.mSaltAmount = fuellstand_in_g; // setzt Salztankfuellstand
//     // mBluetoothCommunication.setSensorData(mSensorData);
  
//     Serial.printf("Sent fuellstand: %f\n", fuellstand_in_g);
// };

void CSalztank::fuellstand_dekrementieren(float dosierte_Salzmenge_in_g)
{
    fuellstand_in_g -= dosierte_Salzmenge_in_g;
};



