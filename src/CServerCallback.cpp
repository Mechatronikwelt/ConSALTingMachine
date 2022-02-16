#include "CServerCallback.h"

void CServerCallback::onConnect(BLEServer* pServer) {
    if(!isConnected) {
        // change state variable
        isConnected = true;

        // print message
        Serial.println("-- connected --");
    }
}
void CServerCallback::onDisconnect(BLEServer* pServer) {
    // start advertising only once, if disconnection occurs
    if(isConnected) {
        // change state variable
        isConnected = false;

        // print message
        Serial.println("-- disconnected --");

        // restart advertising
        BLEDevice::startAdvertising();
    }
}

// return current connection state: true: connected,
// false: disconnected
bool CServerCallback::getConnectionState() {
    return isConnected;
}