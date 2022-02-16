#ifndef CSENSORDATA_H
#define CSENSORDATA_H

#include <Arduino.h>

// CSensorData: contains all sensor values which are sent to android device
class CSensorData {
public:
    // empty constructor
    CSensorData();

    // constructor with parameters
    CSensorData(float pBatteryState, float pSaltAmount, float pPressure);

    // CONVERSION BETWEEN BYTE ARRAY AND CSENSORDATA
    // create object from byte array
    CSensorData(uint8_t* source);
    // create byte array from object
    void convertToByteArray(uint8_t* result);

public:
    float mBatteryState;        // battery state (in %)
    float mSaltAmount;          // remaining salt amount in ConSALTing Machine
    float mPressure;            // detected pressure of pressure sensor
};

#endif