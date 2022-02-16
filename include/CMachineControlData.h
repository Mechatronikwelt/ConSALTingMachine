#ifndef CMACHINECONTROLDATA_H
#define CMACHINECONTROLDATA_H

#include <Arduino.h>
#include "EInstructions.h"

// class CMachineControlData: contains instructions from android device
class CMachineControlData {
public:
    // empty constructor
    CMachineControlData();

    // CONVERSION BETWEEN BYTE ARRAY AND CSENSORDATA
    // create object from byte array
    CMachineControlData(uint8_t* source);
    // create byte array from object
    void convertToByteArray(uint8_t* result);

public:
    float mSaltConcentration;       // salt concentration in gram/liter
    EInstructions mInstruction;     // instruction to ConSALTing Machine from smartphone
};

#endif