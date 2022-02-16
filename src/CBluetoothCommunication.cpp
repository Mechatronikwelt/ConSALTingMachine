#include "CBluetoothCommunication.h"

// constructor: define constants and initialize variables
CBluetoothCommunication::CBluetoothCommunication() : 
    SERVICE_UUID{"1ae5a3bc-bd4f-4440-ae95-b4a0d576313f"},
    CHARACTERISTIC_SENSORDATA_UUID{"2bdedda6-0dce-4c9e-b2bd-383633f7d38a"},
    CHARACTERISTIC_MACHINE_CONTROL_UUID{"b96ebc3f-23ed-4de6-b6e4-092230831a32"},
    mPtrCharacteristicSensorData{NULL},
    mPtrCharacteristicMachineControl{NULL},
    mServerCallback(),
    mCharCallbackSensorData(),
    mCharCallbackMachineControl(),
    isConnected{false} {
}

// initialize device, define service and two characteristics
// (sensordata and machine control)
void CBluetoothCommunication::init() {
    // set bluetooth device name
    BLEDevice::init("ConSALTing Machine");

    // create bluetooth server and define callback method to
    // process connection state changes
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(&mServerCallback);

    // Create BLE-Service (is required to define characteristics)
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create two BLE-Characteristics (machine control and sensordata) with read or write property
    mPtrCharacteristicSensorData = pService->createCharacteristic(CHARACTERISTIC_SENSORDATA_UUID,
        BLECharacteristic::PROPERTY_READ);
    mPtrCharacteristicMachineControl = pService->createCharacteristic(CHARACTERISTIC_MACHINE_CONTROL_UUID,
        BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);
    
    // define callbacks of characteristics
    mPtrCharacteristicSensorData->setCallbacks(&mCharCallbackSensorData);
    mPtrCharacteristicMachineControl->setCallbacks(&mCharCallbackMachineControl);

    // start Service
    pService->start();

    // define advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);

    // start advertising -> Android device can find ConSALTing Machine via bluetooth
    BLEDevice::startAdvertising();
}

// return connection state: true: connected, false: disconnected
bool CBluetoothCommunication::getConnectionState() {
    return mServerCallback.getConnectionState();
}

// set new sensor data to buffer, data is transmitted only if the android device
// requests new sensor data
void CBluetoothCommunication::setSensorData(CSensorData& pSensorData) {
    // convert SensorData to byte array
    uint8_t mByteArray[sizeof(CSensorData)] = {0};
    pSensorData.convertToByteArray(mByteArray);

    // update bluetooth characteristic
    mPtrCharacteristicSensorData->setValue(mByteArray, sizeof(CSensorData));
}