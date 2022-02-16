#include "CStatusLED.h"


CStatusLED::CStatusLED(int led_pin)
            : LED(1, led_pin, NEO_GRB + NEO_KHZ800), 
            Blinkfrequenz_in_Hz(250), Helligkeit(30), Helligkeit_schwach(5)
            {
                LED.begin();
                LED.clear();
            };


void CStatusLED::status_setzen(LED_Status _state)
{
    status = _state;
    switch(status)
    {        
        case Rot:
            red();
            break;

        case Blau:
            blue();
            break;

        case Gruen:
            green(false);
            break;

        case Gruen_schwach:
            green(true);
            break;
            
        case Weiss:
            white();
            break;

        case Gelb:
            yellow();
            break;

        // case Verbindungsaufbau:
        //     red_blue_blink();
        //     break;

        // case  Kalibriervorgang:
        //     green_blink();  
        //     break;

        // case  Salztank_leer:
        //     blue_blink();
        //     break;

        // case  Fehler:
        //     red_blink();
        //     break;

        default:
            off();

    };
    LED.show();
}

void CStatusLED::off()
{
    LED.clear();

}
            
void CStatusLED::red()
{
    LED.setPixelColor(0, LED.Color(Helligkeit, 0, 0));
};
void CStatusLED::blue()
{
    LED.setPixelColor(0, LED.Color(0, 0, Helligkeit));
};
void CStatusLED::green(bool weak = false)
{
    if (weak)
        LED.setPixelColor(0, LED.Color(0, Helligkeit_schwach, 0));
    else
        LED.setPixelColor(0, LED.Color(0, Helligkeit, 0));
};
void CStatusLED::white()
{
    LED.setPixelColor(0, LED.Color(Helligkeit, Helligkeit, Helligkeit));
};
void CStatusLED::yellow()
{
    LED.setPixelColor(0, LED.Color(Helligkeit, Helligkeit, 0));
};








void CStatusLED::red_blink()
{
    red();
    usleep(Blinkfrequenz_in_Hz);
    off();
    usleep(Blinkfrequenz_in_Hz);  
};
void CStatusLED::blue_blink()
{
    blue();
    usleep(Blinkfrequenz_in_Hz);
    off();
    usleep(Blinkfrequenz_in_Hz);
};
void CStatusLED::green_blink()
{
    green();
    usleep(Blinkfrequenz_in_Hz);
    off();
    usleep(Blinkfrequenz_in_Hz);
};
void CStatusLED::white_blink()
{
    white();
    usleep(Blinkfrequenz_in_Hz);
    off();
    usleep(Blinkfrequenz_in_Hz);
};

void CStatusLED::red_blue_blink()
{
    red();
    usleep(Blinkfrequenz_in_Hz);
    blue();
    usleep(Blinkfrequenz_in_Hz);  
};