#include <iostream>
#include <Preferences.h>

class CSalztank
{
public:
    CSalztank();

    float fuellstand_in_g;

    void fuellstand_speichern();
    void fuellstand_laden();
    // void fuellstand_senden();
    void fuellstand_dekrementieren(float dosierte_Salzmenge_in_g);
    const float max_fuellmenge_in_g;
    const float kritische_fuellmenge_in_g;

private: 
    Preferences preferences; // zum Abspeichern der Salztank Füllmenge

};