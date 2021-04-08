//
// Created by Alexey on 04.04.2021.
//

#include "BluetoothBarcodeScannerHandler.h"

#include <IAndroidComponentHelper.h>
#include "AddInDefBase.h"
#include "jnienv.h"


BluetoothBarcodeScannerHandler::~BluetoothBarcodeScannerHandler()
{
    if (obj)
    {
        Stop(); // call to unregister broadcast receiver
        JNIEnv *env = getJniEnv();
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(cc);
    }
}

void BluetoothBarcodeScannerHandler::Start(IAddInDefBaseEx *cnn, IMemoryManager* iMemory, tVariant *paParams) {

    m_iMemory = iMemory;
    m_iConnect = cnn;
    JNIEnv *jenv = getJniEnv();

    IAndroidComponentHelper *helper = (IAndroidComponentHelper *) cnn->GetInterface(
            eIAndroidComponentHelper);
    if (helper) {
        if (obj == NULL){
        jclass ccloc = helper->FindClass((uint16_t *) u"com/alexkmbk/androidtinytools/BluetoothBarcodeScannerHandlerClass");
        if (ccloc) {
            cc = static_cast<jclass>(jenv->NewGlobalRef(ccloc));
            jenv->DeleteLocalRef(ccloc);
            jobject activity = helper->GetActivity();
            // call of constructor for java class
            jmethodID ctorID = jenv->GetMethodID(cc, "<init>", "(Landroid/app/Activity;Ljava/lang/String;J)V");

            jstring jMACAddress = jenv->NewString(paParams[0].pwstrVal, paParams[0].wstrLen);
            jobject objloc = jenv->NewObject(cc, ctorID, activity, jMACAddress, (jlong)this);
            if (objloc)
            {
                obj = jenv->NewGlobalRef(objloc);
                jenv->DeleteLocalRef(objloc);
            }
            jenv->DeleteLocalRef(activity);

        }
        }
        if (obj != NULL)
            jenv->CallVoidMethod(obj, jenv->GetMethodID(cc, "StartBluetoothBarcodeScannerHandler", "()V"));
    }
}

void BluetoothBarcodeScannerHandler::Stop() {
    if (obj != NULL)
    {
        JNIEnv* env = getJniEnv();
        jmethodID methID = env->GetMethodID(cc, "StopBluetoothBarcodeScannerHandler", "()V");
        env->CallVoidMethod(obj, methID);
        if (obj != NULL){
            env->DeleteLocalRef(obj);
            obj = NULL;
        }
    }
}

void BluetoothBarcodeScannerHandler::IsConnected(tVariant *pvarRetValue) {

    TV_VT(pvarRetValue) = VTYPE_BOOL;

    bool IsConnected = false;

    if (obj != NULL)
    {
    JNIEnv* env = getJniEnv();
    jmethodID methID = env->GetMethodID(cc, "IsConnected", "()Z");
    IsConnected = (bool)env->CallBooleanMethod(obj, methID);
    }
    pvarRetValue->bVal = IsConnected;

}