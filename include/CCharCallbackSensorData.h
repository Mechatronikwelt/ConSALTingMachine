#ifndef CCHARCALLBACKSENSORDATA_H
#define CCHARCALLBACKSENSORDATA_H

#include <BLEServer.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <Arduino.h>
#include "CSensorData.h"

// callback class for sensor data bluetooth characteristic
// to update sensor data, use updateSensorData method
class CCharCallbackSensorData : public BLECharacteristicCallbacks {
public:
    // update buffer with new sensor data
    void updateSensorData(CSensorData& pSensorData);

    // callback method: is executed if the device requests new sensor data
    void onRead(BLECharacteristic* pCharacteristic) override;

public:
    // transmitted object
    CSensorData mSensorData;
};

#endif