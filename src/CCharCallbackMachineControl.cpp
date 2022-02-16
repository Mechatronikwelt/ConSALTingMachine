#include "CCharCallbackMachineControl.h"
extern float salz_pro_l_in_g;
extern Preferences preferences;
extern void salzkonzentration_speichern();


// callback method: process machine control events from smartphone
void CCharCallbackMachineControl::onWrite(BLECharacteristic* pCharacteristic) {
    uint8_t* receivedByteArray = pCharacteristic->getData();

    // initialize new CMachineControlData object with receivedByteArray
    CMachineControlData mMachineControlData(receivedByteArray);

    // process transferred instruction
    switch (mMachineControlData.mInstruction)
    {
    case EInstructions::SET_SALT_CONCENTRATION:
        // new salt concentration is stored in mMachineControlData.mSaltConcentration
        Serial.print("neue salzkoncentration empfangen: ");
        Serial.println(mMachineControlData.mSaltConcentration);
        salz_pro_l_in_g = mMachineControlData.mSaltConcentration;
        salzkonzentration_speichern();
        break;
    
    default:
        Serial.println("Bluetooth-Fehler: empfangene Daten nicht dekodierbar!");
        break;
    }
}