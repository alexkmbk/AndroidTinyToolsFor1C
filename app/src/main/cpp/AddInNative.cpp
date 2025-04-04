#include <locale.h>
#include <wchar.h>
#include <exception>
#include "AddInNative.h"
#include "StrConv.h"

static const std::u16string sClassName(u"AndroidTinyTools");

static const std::array<std::u16string, CAddInNative::eMethLast> osMethods{ u"vibrate", u"beep", u"toast", u"startbroadcastreceiver", u"getbluetoothdeviceslist", u"startbluetoothscannerhandler", u"stopbluetoothscannerhandler", u"isbluetoothscannerhandlerconnected"};

AppCapabilities g_capabilities = eAppCapabilitiesInvalid;

//---------------------------------------------------------------------------//
long GetClassObject(const WCHAR_T* wsName, IComponentBase** pInterface)
{
    if (!*pInterface)
    {
        *pInterface = new CAddInNative;
        return (long)*pInterface;
    }
    return 0;
}
//---------------------------------------------------------------------------//
AppCapabilities SetPlatformCapabilities(const AppCapabilities capabilities)
{
    g_capabilities = capabilities;
    return eAppCapabilitiesLast;
}
//---------------------------------------------------------------------------//
long DestroyObject(IComponentBase** pIntf)
{
    if (!*pIntf)
        return -1;

    delete *pIntf;
    *pIntf = 0;
    return 0;
}
//---------------------------------------------------------------------------//
const WCHAR_T* GetClassNames()
{
    return (WCHAR_T*)sClassName.c_str();
 }
//---------------------------------------------------------------------------//

// CAddInNative
//---------------------------------------------------------------------------//
CAddInNative::CAddInNative()
{
    m_iMemory = 0;
    m_iConnect = 0;
}
//---------------------------------------------------------------------------//
CAddInNative::~CAddInNative()
{
}
//---------------------------------------------------------------------------//
bool CAddInNative::Init(void* pConnection)
{
    m_iConnect = (IAddInDefBaseEx*)pConnection;
    return m_iConnect != NULL;
}
//---------------------------------------------------------------------------//
long CAddInNative::GetInfo()
{
    // Component should put supported component technology version
    // This component supports 2.1 version
    return 2100;
}
//---------------------------------------------------------------------------//
void CAddInNative::Done()
{
    m_iConnect = NULL;
}
/////////////////////////////////////////////////////////////////////////////
// ILanguageExtenderBase
//---------------------------------------------------------------------------//
bool CAddInNative::RegisterExtensionAs(WCHAR_T** wsExtensionName)
{
    if (wsExtensionName == nullptr) {
        return false;
    }
    const size_t size = (sClassName.size() + 1) * sizeof(char16_t);

    if (!m_iMemory || !m_iMemory->AllocMemory(reinterpret_cast<void**>(wsExtensionName), size) || *wsExtensionName == nullptr) {
        return false;
    };

    memcpy(*wsExtensionName, sClassName.c_str(), size);

    return true;
}
//---------------------------------------------------------------------------//
long CAddInNative::GetNProps()
{
    return ePropLast;
}
//---------------------------------------------------------------------------//
long CAddInNative::FindProp(const WCHAR_T* wsPropName)
{
    long plPropNum = -1;
    return plPropNum;
}

//---------------------------------------------------------------------------//
const WCHAR_T* CAddInNative::GetPropName(long lPropNum, long lPropAlias)
{
    return NULL;
}
//---------------------------------------------------------------------------//
bool CAddInNative::GetPropVal(const long lPropNum, tVariant* pvarPropVal)
{
    return false;
}

//---------------------------------------------------------------------------//
bool CAddInNative::SetPropVal(const long lPropNum, tVariant *varPropVal)
{
    return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::IsPropReadable(const long lPropNum)
{
   return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::IsPropWritable(const long lPropNum)
{
    switch (lPropNum)
    {
        default:
            return false;
    }

}
//---------------------------------------------------------------------------//
long CAddInNative::GetNMethods()
{
    return eMethLast;
}

//---------------------------------------------------------------------------//
long CAddInNative::FindMethod(const WCHAR_T* wsMethodName)
{
    std::u16string usMethodName = (char16_t*)(wsMethodName);
    tolowerStr(usMethodName);

    auto it = std::find(osMethods.begin(), osMethods.end(), usMethodName);
    if (it != osMethods.end()) {
        return it - osMethods.begin();
    }

    return -1;
}
//---------------------------------------------------------------------------//
const WCHAR_T* CAddInNative::GetMethodName(const long lMethodNum, const long lMethodAlias)
{

    if (lMethodNum >= eMethLast)
        return nullptr;

    const std::basic_string<char16_t>* usCurrentName;

    usCurrentName = &osMethods[lMethodNum];

    if (usCurrentName == nullptr)
        return nullptr;

    WCHAR_T* result = nullptr;

    const size_t bytes = (usCurrentName->length() + 1) * sizeof(char16_t);

    if (!m_iMemory || !m_iMemory->AllocMemory(reinterpret_cast<void**>(&result), bytes)) {
        return nullptr;
    };

    memcpy(result, usCurrentName->c_str(), bytes);

    return result;
}

//---------------------------------------------------------------------------//
long CAddInNative::GetNParams(const long lMethodNum)
{
    switch (lMethodNum)
    {
        case eMethVibrate:
            return 1;
        case eMethBeep:
            return 1;
        case eMethToast:
            return 1;
        case eMethStartBroadcastReceiver:
            return 2;
        case eMethStartBluetoothScannerHandler:
            return 1;
        default:
            return 0;
    }

    return 0;
}

//---------------------------------------------------------------------------//
bool CAddInNative::GetParamDefValue(const long lMethodNum, const long lParamNum,
                                    tVariant *pvarParamDefValue)
{
    switch (lMethodNum)
    {
        case eMethVibrate:
        {
            TV_VT(pvarParamDefValue) = VTYPE_I4;
            pvarParamDefValue->lVal = 500;
            return true;
        }
        case eMethBeep:
        {
            TV_VT(pvarParamDefValue) = VTYPE_I4;
            pvarParamDefValue->lVal = 28;
            return true;
        }
        default:
        {
            TV_VT(pvarParamDefValue) = VTYPE_EMPTY;
            return false;
        }
    }

    TV_VT(pvarParamDefValue) = VTYPE_EMPTY;
    return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::HasRetVal(const long lMethodNum)
{
    switch (lMethodNum)
    {
        case eMethGetBluetoothDevicesList:
        {
             return true;
        }
        case eMethIsBluetoothScannerHandlerConnected:
        {
            return true;
        }
        default:
            return false;
    }

    return false;
}
//---------------------------------------------------------------------------//
bool CAddInNative::CallAsProc(const long lMethodNum,
                              tVariant* paParams, const long lSizeArray)
{
    switch (lMethodNum)
    {
        case eMethVibrate:
        {
            Vibrate(paParams, lSizeArray);
            return true;
        }
        case eMethBeep:
        {
            Beep(paParams, lSizeArray);
            return true;
        }
        case eMethToast:
        {
            Toast(paParams, lSizeArray);
            return true;
        }
        case eMethStartBroadcastReceiver:
        {
            StartBroadcastReceiver(paParams, lSizeArray);
            return true;
        }
        case eMethStopBluetoothScannerHandler:
        {
            bluetoothBarcodeScannerHandler.Stop();
            return true;
        }
        case eMethStartBluetoothScannerHandler:
        {
            StartBluetoothScannerHandler(paParams, lSizeArray);
            return true;
        }
        default:
            return false;
    }
    return true;
}

//---------------------------------------------------------------------------//
bool CAddInNative::CallAsFunc(const long lMethodNum,
                              tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray)
{
    switch (lMethodNum)
    {
        case eMethGetBluetoothDevicesList:
        {
            GetBluetoothDevicesList(pvarRetValue, paParams, lSizeArray);
            return true;
        }
        case eMethIsBluetoothScannerHandlerConnected:
        {
            bluetoothBarcodeScannerHandler.IsConnected(pvarRetValue);
            return true;
        }
        default:
            return false;
    }
    return true;
}


void CAddInNative::SetLocale(const WCHAR_T* loc)
{
#if !defined( __linux__ ) && !defined(__APPLE__) && !defined(__ANDROID__)
    _wsetlocale(LC_ALL, L"");
#else
    setlocale(LC_ALL, "");
#endif
}

bool CAddInNative::setMemManager(void* mem)
{
    m_iMemory = (IMemoryManager*)mem;
    return m_iMemory != 0;
}

void CAddInNative::Vibrate(tVariant* paParams, const long lSizeArray) {

    IAndroidComponentHelper*    helper;
    jclass                      cc;
    jobject                     obj;
    IAddInDefBaseEx*            cnn;

    cnn = m_iConnect;
    helper = (IAndroidComponentHelper*)cnn->GetInterface(eIAndroidComponentHelper);

    if (helper)
    {

        long milliseconds = paParams[0].lVal;
        jclass ccloc = helper->FindClass((const WCHAR_T*)u"com/alexkmbk/androidtinytools/VibrateClass");

        if (ccloc)
        {

            JNIEnv* jenv = getJniEnv();
            cc = static_cast<jclass>(jenv->NewGlobalRef(ccloc));
            jenv->DeleteLocalRef(ccloc);
            jobject activity = helper->GetActivity();

            jmethodID ctorID;
            jobject objloc;

            ctorID = jenv->GetMethodID(cc, "<init>", "(Landroid/app/Activity;J)V");
            objloc = jenv->NewObject(cc, ctorID, activity, (jlong)milliseconds);

            if (objloc)
            {
                obj = jenv->NewGlobalRef(objloc);
                jenv->DeleteLocalRef(objloc);
            }

            jenv->DeleteLocalRef(activity);
            jmethodID methodID = jenv->GetMethodID(cc, "vibrate", "()V");
            jenv->CallVoidMethod(obj, methodID);

            return;

        }
    }
}

void CAddInNative::Beep(tVariant* paParams, const long lSizeArray) {

    IAndroidComponentHelper*    helper;
    jclass                      cc;
    jobject                     obj;
    IAddInDefBaseEx*            cnn;

    int TONE = paParams[0].lVal;

    cnn = m_iConnect;
    helper = (IAndroidComponentHelper*)cnn->GetInterface(eIAndroidComponentHelper);

    if (helper)
    {
        jclass ccloc = helper->FindClass((const WCHAR_T*)u"com/alexkmbk/androidtinytools/BeepClass");

        if (ccloc)
        {
            JNIEnv* jenv = getJniEnv();
            cc = static_cast<jclass>(jenv->NewGlobalRef(ccloc));
            jenv->DeleteLocalRef(ccloc);
            jobject activity = helper->GetActivity();
            jmethodID ctorID = jenv->GetMethodID(cc, "<init>", "(Landroid/app/Activity;I)V");

            jobject objloc = jenv->NewObject(cc, ctorID, activity, (jint)TONE);
            if (objloc)
            {
                obj = jenv->NewGlobalRef(objloc);
                jenv->DeleteLocalRef(objloc);
            }
            jenv->DeleteLocalRef(activity);


            // Run native
            jmethodID methodID = jenv->GetMethodID(cc, "beep", "()V");
            jenv->CallVoidMethod(obj, methodID);

            return;

        }
    }
}

void CAddInNative::Toast(tVariant* paParams, const long lSizeArray) {

    IAndroidComponentHelper*    helper;
    jclass                      cc;
    jobject                     obj;
    IAddInDefBaseEx*            cnn;

    cnn = m_iConnect;
    helper = (IAndroidComponentHelper*)cnn->GetInterface(eIAndroidComponentHelper);

    if (helper)
    {

        jclass ccloc = helper->FindClass((const WCHAR_T*)u"com/alexkmbk/androidtinytools/ToastClass");

        if (ccloc)
        {

            JNIEnv* jenv = getJniEnv();
            cc = static_cast<jclass>(jenv->NewGlobalRef(ccloc));
            jenv->DeleteLocalRef(ccloc);
            jobject activity = helper->GetActivity();
            jmethodID ctorID = jenv->GetMethodID(cc, "<init>", "(Landroid/app/Activity;Ljava/lang/String;)V");

            jstring jStringParam = jenv->NewString(
                    reinterpret_cast<const jchar *>(paParams[0].pwstrVal), paParams[0].wstrLen);
            jobject objloc = jenv->NewObject(cc, ctorID, activity, jStringParam);
            if (objloc)
            {
                obj = jenv->NewGlobalRef(objloc);
                jenv->DeleteLocalRef(objloc);
            }
            jenv->DeleteLocalRef(activity);

            jenv->CallVoidMethod(obj, jenv->GetMethodID(cc, "toast", "()V"));

            return;

        }
    }
}

void CAddInNative::StartBroadcastReceiver(tVariant *paParams, const long lSizeArray) {

    broadcastReceiver.Start(m_iConnect, m_iMemory, paParams);
}

void CAddInNative::StopBroadcastReceiver() {

    broadcastReceiver.Stop();
}


void CAddInNative::GetBluetoothDevicesList(tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray) {

    IAndroidComponentHelper*    helper;
    jclass                      cc;
    jobject                     obj;
    IAddInDefBaseEx*            cnn;

    cnn = m_iConnect;
    helper = (IAndroidComponentHelper*)cnn->GetInterface(eIAndroidComponentHelper);

    if (helper)
    {

        jclass ccloc = helper->FindClass((const WCHAR_T*)u"com/alexkmbk/androidtinytools/BluetoothClass");

        if (ccloc)
        {

            JNIEnv* jenv = getJniEnv();
            cc = static_cast<jclass>(jenv->NewGlobalRef(ccloc));
            jenv->DeleteLocalRef(ccloc);
            jobject activity = helper->GetActivity();
            jmethodID ctorID = jenv->GetMethodID(cc, "<init>", "(Landroid/app/Activity;)V");

            jobject objloc = jenv->NewObject(cc, ctorID, activity);
            if (objloc)
            {
                obj = jenv->NewGlobalRef(objloc);
                jenv->DeleteLocalRef(objloc);

            } else
            {
                TV_VT(pvarRetValue) = VTYPE_PWSTR;
                pvarRetValue->wstrLen = 0;
                return;
            }

            jenv->DeleteLocalRef(activity);

            jstring res = (jstring)jenv->CallObjectMethod(obj, jenv->GetMethodID(cc, "getBluetoothDevicesList", "()Ljava/lang/String;"));

            TV_VT(pvarRetValue) = VTYPE_PWSTR;

            pvarRetValue->wstrLen = jstring2v8string(jenv, m_iMemory, res, &(pvarRetValue->pwstrVal)) / sizeof(uint16_t) - 1;

            /*TV_VT(pvarRetValue) = VTYPE_TM;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            char* buf;
            strftime(buf, 20, "%d-%b-%Y %H:%M", ltm);*/
            return;
        }
    }
}

void CAddInNative::StartBluetoothScannerHandler(tVariant *paParams, const long lSizeArray){

    bluetoothBarcodeScannerHandler.Start(m_iConnect, m_iMemory, paParams);

}

static const char16_t g_EventSource[] = u"AndroidTinyTools";
static const char16_t g_OnBarcodeEventName[] = u"Barcode";

extern "C" JNIEXPORT void JNICALL Java_com_alexkmbk_androidtinytools_BroadcastReceiverClass_BroadcastMessage(JNIEnv* jenv, jclass jClass, jlong pObject, jstring jsEventName, jstring jsExtraParam)
{

    BroadcastReceiver *broadcastReceiver = (BroadcastReceiver *) pObject;

    if (broadcastReceiver) {

        WCHAR_T *wcEventName = nullptr;
        jstring2v8string(jenv, broadcastReceiver->m_iMemory, jsEventName, &wcEventName);

        WCHAR_T *wcExtraParam = nullptr;
        jstring2v8string(jenv, broadcastReceiver->m_iMemory, jsExtraParam, &wcExtraParam);

        if (broadcastReceiver->m_iConnect != NULL) {
            broadcastReceiver->m_iConnect->ExternalEvent((WCHAR_T*) g_EventSource,
                                                           wcEventName,
                                                           wcExtraParam);
        }
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_alexkmbk_androidtinytools_BluetoothBarcodeScannerHandlerClass_OnBarcode(JNIEnv* jenv, jclass jClass, jlong pObject, jstring sBarcode)
{

    BluetoothBarcodeScannerHandler *bluetoothBarcodeScannerHandler = (BluetoothBarcodeScannerHandler *) pObject;

    if (bluetoothBarcodeScannerHandler) {

        WCHAR_T *wcBarcode = nullptr;
        jstring2v8string(jenv, bluetoothBarcodeScannerHandler->m_iMemory, sBarcode, &wcBarcode);

        if (bluetoothBarcodeScannerHandler->m_iConnect != NULL) {
            bluetoothBarcodeScannerHandler->m_iConnect->ExternalEvent((WCHAR_T*) g_EventSource,
                                                                      (WCHAR_T*) g_OnBarcodeEventName,
                                                                      wcBarcode);
        }
    }
}

void ADDIN_API CAddInNative::SetUserInterfaceLanguageCode(const WCHAR_T* lang)
{
}
