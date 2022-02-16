#ifndef CSERVERCALLBACK_H
#define CSERVERCALLBACK_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <Arduino.h>

// ServerCallback class: check current connection state
class CServerCallback : public BLEServerCallbacks {
public:
    void onConnect(BLEServer* pServer) override;
    void onDisconnect(BLEServer* pServer) override;
    bool getConnectionState();

private:
    bool isConnected;
};

#endif