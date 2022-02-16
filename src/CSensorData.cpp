#include "CSensorData.h"

// empty constructor
CSensorData::CSensorData() {
    mBatteryState = 0.0f;
    mSaltAmount = 0.0f;
    mPressure = 0.0f;
}

// constructor with parameters
CSensorData::CSensorData(float pBatteryState, float pSaltAmount, float pPressure) {
    mBatteryState = pBatteryState;
    mSaltAmount = pSaltAmount;
    mPressure = pPressure;
}

// CONVERSION BETWEEN BYTE ARRAY AND CSENSORDATA
// create object from byte array
CSensorData::CSensorData(uint8_t* source) {
    CSensorData* mPtr = reinterpret_cast<CSensorData*>(source);
    this->mBatteryState = mPtr->mBatteryState;
    this->mSaltAmount = mPtr->mSaltAmount;
    this->mPressure = mPtr->mPressure;
}

// create byte array from object
void CSensorData::convertToByteArray(uint8_t* result) {
    for(unsigned char i = 0; i < sizeof(CSensorData); i++) {
        // copy all bytes of object
        result[i] = *(reinterpret_cast<uint8_t*>(this)+i);
    }
}