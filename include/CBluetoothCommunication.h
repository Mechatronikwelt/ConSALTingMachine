#ifndef CBLUETOOTHCOMMUNICATION_H
#define CBLUETOOTHCOMMUNICATION_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "CCharCallbackSensorData.h"
#include "CCharCallbackMachineControl.h"
#include "CServerCallback.h"
#include "CSensorData.h"

// class for bluetooth communication: configure device and two characteristics
// to receive instructions and transmit sensordata
class CBluetoothCommunication {
public:
    CBluetoothCommunication();
    void init();                    // initialize Device and start advertising
    bool getConnectionState();      // get state: true: connected, false: disconnected
    void setSensorData(CSensorData& pSensorData);   // set new sensor data to buffer, data is transmitted
                                                    // only if the android device requests new sensor data
private:
    // constant variables for UUIDs (universally unique identifier)
    const char SERVICE_UUID[37];
    const char CHARACTERISTIC_SENSORDATA_UUID[37];
    const char CHARACTERISTIC_MACHINE_CONTROL_UUID[37];

    // Pointer for BLE-Characteristics
    BLECharacteristic* mPtrCharacteristicSensorData;
    BLECharacteristic* mPtrCharacteristicMachineControl;

    // Define Callback-Objects
    CServerCallback mServerCallback;
    CCharCallbackSensorData mCharCallbackSensorData;
    CCharCallbackMachineControl mCharCallbackMachineControl;

    // variables for bluetooth states
    bool isConnected;
};

#endif