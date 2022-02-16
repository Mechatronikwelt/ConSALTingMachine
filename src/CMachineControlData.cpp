#include "CMachineControlData.h"

// empty constructor
CMachineControlData::CMachineControlData() {
    mSaltConcentration = 0.0f;
    mInstruction = EInstructions::SET_SALT_CONCENTRATION;
}

// CONVERSION BETWEEN BYTE ARRAY AND CSENSORDATA
// create object from byte array
CMachineControlData::CMachineControlData(uint8_t* source) {
    CMachineControlData* mPtr = reinterpret_cast<CMachineControlData*>(source);
    
    this->mInstruction = mPtr->mInstruction;
    this->mSaltConcentration = mPtr->mSaltConcentration;
}

// create byte array from object
void CMachineControlData::convertToByteArray(uint8_t* result) {
    for(unsigned char i = 0; i < sizeof(CMachineControlData); i++) {
        // copy all bytes of object
        result[i] = *(reinterpret_cast<uint8_t*>(this)+i);
    }
}