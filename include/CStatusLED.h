#include <iostream>
#include <Adafruit_NeoPixel.h>

enum LED_Status
{   
    Rot,
    Blau,
    Weiss,
    Gruen,
    Gruen_schwach,
    Gelb,

    Kalibriervorgang,
    Fehler,
    Salztank_leer,
    Verbindungsaufbau,
};

class CStatusLED
{
public:
    CStatusLED(int led_pin);
    void status_setzen(LED_Status _status);
    
private:
    Adafruit_NeoPixel LED;
    LED_Status status;
    int Blinkfrequenz_in_Hz;
    int Helligkeit;
    int Helligkeit_schwach;

    void off();

    void red();
    void blue();
    void green(bool weak);
    void white();
    void yellow();
    
    // ACHTUNG: MÜSSEN IN WHILE SCHLEIFE AUFGERUFEN WERDEN:
    void red_blink();
    void blue_blink();
    void green_blink();
    void white_blink();
    void red_blue_blink();

};
