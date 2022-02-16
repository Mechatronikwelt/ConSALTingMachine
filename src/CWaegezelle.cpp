#include "CWaegezelle.h"

CWaegezelle::CWaegezelle(int _dout_pin, int _sck_pin)
            : max_Fuellmenge_in_ml(1500), LoadCell(_dout_pin, _sck_pin), 
                mw_offset(13996), calFactor(626.3f),
                mSalztank(CSalztank())
{}

void CWaegezelle::calibrate()
{
    LoadCell.setCalFactor(calFactor);
}

float CWaegezelle::messwert_in_g()
{
    LoadCell.powerUp();
    LoadCell.update();
    float mw = LoadCell.getData();

    mw = mw - mw_offset;
    mw = mw * 1.47;

    return mw;
}


float CWaegezelle::messwert_wasser_in_g()
{
    float wassermenge_in_ml = 0;

    float summe = 0;
    float anzahl_messwerte = 20;
    float wassermenge_in_ml_mw = 0; 

    for(int i = 75 + anzahl_messwerte; i > 0; i--)
    {  
        wassermenge_in_ml = messwert_in_g();    
        Serial.print("wassermenge_in_ml: ");
        Serial.println(wassermenge_in_ml);

        if(i <= anzahl_messwerte)
        {
            summe = summe + wassermenge_in_ml;
        }
    }

    wassermenge_in_ml_mw = (summe / anzahl_messwerte) - mSalztank.fuellstand_in_g;
    Serial.print("wassermenge_in_ml_mw: ");
    Serial.println(wassermenge_in_ml_mw);


    return wassermenge_in_ml_mw;
};

float CWaegezelle::messwert_salz_in_g()
{
    float salzmenge_in_g = 0;

    float summe = 0;
    float anzahl_messwerte = 40;
    float salzmenge_in_g_mw = 0; 

    for(int i = 75 + anzahl_messwerte; i > 0; i--)
    {  
        salzmenge_in_g = messwert_in_g();    
        Serial.print("salzmenge_in_mg: ");
        Serial.println(salzmenge_in_g);

        if(i <= anzahl_messwerte)
        {
            summe = summe + salzmenge_in_g;
        }
    }

    salzmenge_in_g_mw = summe / anzahl_messwerte;
    Serial.print("salzmenge_in_g_mw: ");
    Serial.println(salzmenge_in_g_mw);

    return salzmenge_in_g_mw;
};

void CWaegezelle::salztank_abrechnen(float ausgegebene_salzmenge)
{
    mSalztank.fuellstand_dekrementieren(ausgegebene_salzmenge);
};
void CWaegezelle::salztank_fuellstand_speichern()
{
    mSalztank.fuellstand_speichern();
};
void CWaegezelle::salztank_fuellstand_laden()
{
    mSalztank.fuellstand_laden();
};
// void CWaegezelle::salztank_fuellstand_senden()
// {
//     mSalztank.fuellstand_senden();
// };
float CWaegezelle::salztank_fuellstand_kalibrierung()
{
    mSalztank.fuellstand_in_g = messwert_salz_in_g();
    return mSalztank.fuellstand_in_g;
};
float CWaegezelle::get_salztank_fuellstand_in_g()
{
    return mSalztank.fuellstand_in_g;
};
float CWaegezelle::get_salztank_max_fuellmenge_in_g()
{
    return mSalztank.max_fuellmenge_in_g;
};
float CWaegezelle::get_salztank_krit_fuellstand_in_g()
{
    return mSalztank.kritische_fuellmenge_in_g;
};