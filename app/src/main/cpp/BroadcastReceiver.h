//
// Created by Alexey on 15.04.2020.
//

#ifndef VIBRATEADDIN_BROADCASTRECEIVER_H
#define VIBRATEADDIN_BROADCASTRECEIVER_H


#include <jni.h>
#include "AddInDefBase.h"
#include "IAndroidComponentHelper.h"
#include "IMemoryManager.h"

class BroadcastReceiver {

private:

    jclass cc;
    jobject obj;
    bool started;

public:
    BroadcastReceiver(){started = false; obj = NULL; cc = NULL;};
    ~BroadcastReceiver();
    void Start(IAddInDefBaseEx *cnn, IMemoryManager* iMemory, tVariant *paParams);
    void Stop();

    IAddInDefBaseEx      *m_iConnect;
    IMemoryManager     *m_iMemory;

};

#endif //VIBRATEADDIN_BROADCASTRECEIVER_H
