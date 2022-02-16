#include <iostream>
#include <HX711_ADC.h>
#include "CSalztank.h"

class CWaegezelle 
{
public:
    CWaegezelle(int _dout_pin, int _sck_pin);

    void salztank_abrechnen(float ausgegebene_salzmenge);
    void salztank_fuellstand_speichern();
    void salztank_fuellstand_laden();
    // void salztank_fuellstand_senden();
    float messwert_wasser_in_g();
    float messwert_salz_in_g();
    float salztank_fuellstand_kalibrierung();
    float get_salztank_fuellstand_in_g();
    float get_salztank_max_fuellmenge_in_g();
    float get_salztank_krit_fuellstand_in_g();
    const float max_Fuellmenge_in_ml;

    float messwert_in_g();
    HX711_ADC LoadCell;
    void calibrate();
private:
    
    float mw_offset;
    float calFactor;
    
    CSalztank mSalztank;   
    int t = 1000;
};