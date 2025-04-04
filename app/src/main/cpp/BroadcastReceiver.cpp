//
// Created by Alexey on 15.04.2020.
//
#include <AddInDefBase.h>
#include <IAndroidComponentHelper.h>
#include "BroadcastReceiver.h"
#include "jnienv.h"


BroadcastReceiver::~BroadcastReceiver()
{
   if (obj)
   {
      Stop(); // call to unregister broadcast receiver
      JNIEnv *env = getJniEnv();
      env->DeleteGlobalRef(obj);
      env->DeleteGlobalRef(cc);
   }
}

void BroadcastReceiver::Start(IAddInDefBaseEx *cnn, IMemoryManager* iMemory, tVariant *paParams) {

   if (started)
      return;

   m_iMemory = iMemory;
   m_iConnect = cnn;

   IAndroidComponentHelper *helper = (IAndroidComponentHelper *) cnn->GetInterface(
           eIAndroidComponentHelper);
   if (helper) {
      jclass ccloc = helper->FindClass((const WCHAR_T *) u"com/alexkmbk/androidtinytools/BroadcastReceiverClass");
      if (ccloc) {
         JNIEnv *jenv = getJniEnv();
         cc = static_cast<jclass>(jenv->NewGlobalRef(ccloc));
         jenv->DeleteLocalRef(ccloc);
         jobject activity = helper->GetActivity();
         // call of constructor for java class
         jmethodID ctorID = jenv->GetMethodID(cc, "<init>", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;J)V");

         jstring jActionName = jenv->NewString(
                 reinterpret_cast<const jchar *>((WCHAR_T *) paParams[0].pwstrVal), paParams[0].wstrLen);
         jstring jStringParam = jenv->NewString(
                 reinterpret_cast<const jchar *>(paParams[1].pwstrVal), paParams[1].wstrLen);
         jobject objloc = jenv->NewObject(cc, ctorID, activity, jActionName, jStringParam, (jlong)this);
         if (objloc)
         {
            obj = jenv->NewGlobalRef(objloc);
            jenv->DeleteLocalRef(objloc);
         }
         jenv->DeleteLocalRef(activity);

         jenv->CallVoidMethod(obj, jenv->GetMethodID(cc, "StartBroadcastReceiver", "()V"));
         started = true;
      }
   }
}

void BroadcastReceiver::Stop() {

   if (started)
   {
      JNIEnv* env = getJniEnv();
      jmethodID methID = env->GetMethodID(cc, "StopBroadcastReceiver", "()V");
      env->CallVoidMethod(obj, methID);
   }

}
