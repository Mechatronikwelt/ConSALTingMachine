#ifndef CCHARCALLBACKMACHINECONTROL_H
#define CCHARCALLBACKMACHINECONTROL_H

#include <BLEServer.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <Arduino.h>
#include "CMachineControlData.h"
#include "EInstructions.h"
#include <Preferences.h>


// callback class for machine control bluetooth characteristic
// if the android device sends a new instruction to ConSALTing Machine,
// onWrite method will be called automatically
class CCharCallbackMachineControl : public BLECharacteristicCallbacks {
    // callback method: process machine control events
    // from smartphone
    void onWrite(BLECharacteristic* pCharacteristic) override;
};

#endif