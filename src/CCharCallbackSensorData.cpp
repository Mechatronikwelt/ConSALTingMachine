#include "CCharCallbackSensorData.h"

// update buffer with new sensor data
void CCharCallbackSensorData::updateSensorData(CSensorData& pSensorData) {
    mSensorData = pSensorData;
}

// callback method: is executed if the device reads from 
// sensordata characteristic
void CCharCallbackSensorData::onRead(BLECharacteristic* pCharacteristic) {
    Serial.println("sensor data request");
}