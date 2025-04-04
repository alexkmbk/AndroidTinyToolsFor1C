//
// Created by Alexey on 04.04.2021.
//

#ifndef ANDROIDTINYTOOLSFOR1C_BLUETOOTHBARCODESCANNERHANDLER_H
#define ANDROIDTINYTOOLSFOR1C_BLUETOOTHBARCODESCANNERHANDLER_H

#include <jni.h>
#include <AddInDefBase.h>
#include <IAndroidComponentHelper.h>
#include <IMemoryManager.h>

class BluetoothBarcodeScannerHandler {
private:

    jclass cc;
    jobject obj;

public:
    BluetoothBarcodeScannerHandler(){obj = NULL; cc = NULL;};
    ~BluetoothBarcodeScannerHandler();
    void Start(IAddInDefBaseEx *cnn, IMemoryManager* iMemory, tVariant *paParams);
    void Stop();
    void IsConnected(tVariant* pvarRetValue);

    IAddInDefBaseEx      *m_iConnect;
    IMemoryManager     *m_iMemory;

};


#endif //ANDROIDTINYTOOLSFOR1C_BLUETOOTHBARCODESCANNERHANDLER_H
