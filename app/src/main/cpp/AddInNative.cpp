#if !defined( __linux__ ) && !defined(__APPLE__) && !defined(__ANDROID__)
#include "stdafx.h"
#endif

#if defined(__ANDROID__) //MOBILE_PLATFORM_WINRT

#include "../../include/AddInDefBase.h"
#include "../../include/mobile.h"
#include "../include/IAndroidComponentHelper.h"
#include "jnienv.h"
#include <jni.h>

#endif

#include <locale.h>
#include <wchar.h>
#include <exception>
#include "AddInNative.h"

static AppCapabilities g_capabilities = eAppCapabilitiesInvalid;

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
    static char16_t cls_names[] = u"AndroidTinyTools";
    return reinterpret_cast<WCHAR_T *>(cls_names);
}
//---------------------------------------------------------------------------//

// CAddInNative
//---------------------------------------------------------------------------//
CAddInNative::CAddInNative()
{
    m_iMemory = NULL;
    m_iConnect = NULL;

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
    char16_t name[] = u"AndroidTinyTools";

    if (!m_iMemory || !m_iMemory->AllocMemory(reinterpret_cast<void **>(wsExtensionName), sizeof(name))) {
        return false;
    };

    memcpy(*wsExtensionName, name, sizeof(name));

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

    long plMethodNum = -1;

    if (memcmp(wsMethodName, u"Vibrate", (sizeof(u"Vibrate")) - sizeof(char16_t)) == 0){
        plMethodNum = eMethVibrate;
    }
    else if (memcmp(wsMethodName, u"Beep", (sizeof(u"Beep")) - sizeof(char16_t)) == 0){
        plMethodNum = eMethBeep;
    }
    else if (memcmp(wsMethodName, u"Toast", (sizeof(u"Toast")) - sizeof(char16_t)) == 0) {
        plMethodNum = eMethToast;
    }
    else if (memcmp(wsMethodName, u"StartBroadcastReceiver", (sizeof(u"StartBroadcastReceiver")) - sizeof(char16_t)) == 0) {
        plMethodNum = eMethStartBroadcastReceiver;
    }
    return plMethodNum;
}
//---------------------------------------------------------------------------//
const WCHAR_T* CAddInNative::GetMethodName(const long lMethodNum, const long lMethodAlias)
{

    if (lMethodNum >= eMethLast)
        return NULL;

    const char16_t* usCurrentName = NULL;
    size_t len = 0;

    switch (lMethodAlias) {
        case 0: // First language
        {
            switch (lMethodNum) {
                case eMethVibrate: {
                    usCurrentName = u"Vibrate";
                    break;
                }
                case eMethBeep: {
                    usCurrentName = u"Beep";
                    break;
                }
                case eMethToast: {
                    usCurrentName = u"Toast";
                    break;
                }
                case eMethStartBroadcastReceiver: {
                    usCurrentName = u"StartBroadcastReceiver";
                    break;
                }
            }
        }
      }

    len = sizeof(usCurrentName);

    WCHAR_T *result = nullptr;

    if ((usCurrentName == NULL) || !m_iMemory || !m_iMemory->AllocMemory(reinterpret_cast<void **>(&result), len)) {
        return nullptr;
    };

    memcpy(result, usCurrentName, len);

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
        default:
            return false;
    }
    return true;
}

/*uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len=0)
{
    if (!len)
        len = static_cast<uint32_t>(::wcslen(Source) + 1);

    if (!*Dest)
        *Dest = new WCHAR_T[len];

    WCHAR_T* tmpShort = *Dest;
    wchar_t* tmpWChar = (wchar_t*)Source;
    uint32_t res = 0;

    for (; len; --len, ++res, ++tmpWChar, ++tmpShort)
    {
        *tmpShort = (WCHAR_T)*tmpWChar;
    }

    return res;
}*/

//---------------------------------------------------------------------------//
bool CAddInNative::CallAsFunc(const long lMethodNum,
                              tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray)
{
    switch (lMethodNum)
    {
        default:
            return false;
    }
    return true;
}

//---------------------------------------------------------------------------//
// Платформа передает в компоненту текущее название локали.
// Название локали зависит от системы и возможно от настроек платформы,
// может принимать самые различные значения: "ru_RU", "rus", "ru" и т.д.
// Название локали можно использовать для инициализации локали в стандартной библиотеке шаблонов (STL)
// языка C++. От установленной локали в STL зависит:
// - правила конвертации из строки в число (напр. символ разделения дробной части)
// - мультибайтовая кодировка (UTF-8, CP1521 и т.д.) в которую будет преобразовываться строка из широких символов функцией wcstombs.
// - мультибайтовая кодировка, которая будет принята за основу при преобразовании строки из мультибайтовых символов в широкие функцией mbstowcs.
// - множество прочих национальных особенностей
// На текущий момент (v1С = 8.3.6.1760), в функцию могут передаваться названия локалей которые не подходят для передачи
// в функцию setlocale и она возвращает NULL, с этим надо бы разобраться. Если функция setlocale возвращает NULL,
// то в неё передается пустая строка, это приводит к установке текущих языковых настроек операционной системы.
//
void CAddInNative::SetLocale(const WCHAR_T* loc)
{
#if !defined( __linux__ ) && !defined(__APPLE__) && !defined(__ANDROID__)
    _wsetlocale(LC_ALL, L"");
#else
    setlocale(LC_ALL, "");
#endif
}

/////////////////////////////////////////////////////////////////////////////
// LocaleBase
//---------------------------------------------------------------------------//
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

        WCHAR_T* className = 0;
        long milliseconds = paParams[0].lVal;

        jclass ccloc = helper->FindClass((uint16_t*)u"com/alexkmbk/androidtinytools/VibrateClass");


        delete[] className;
        className = 0;

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

        jclass ccloc = helper->FindClass((uint16_t*)u"com/alexkmbk/androidtinytools/BeepClass");

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

        jclass ccloc = helper->FindClass((uint16_t*)u"com/alexkmbk/androidtinytools/ToastClass");

        if (ccloc)
        {

            JNIEnv* jenv = getJniEnv();
            cc = static_cast<jclass>(jenv->NewGlobalRef(ccloc));
            jenv->DeleteLocalRef(ccloc);
            jobject activity = helper->GetActivity();
            jmethodID ctorID = jenv->GetMethodID(cc, "<init>", "(Landroid/app/Activity;Ljava/lang/String;)V");

            jstring jStringParam = jenv->NewString(paParams[0].pwstrVal, paParams[0].wstrLen);
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

long jstring2v8string(JNIEnv *jenv, IMemoryManager *m_iMemory, jstring jstrIn, WCHAR_T **output){

    if (jstrIn == NULL)
        return  0;

    jsize lengthInChars = jenv->GetStringLength(jstrIn);
    jsize size = (lengthInChars + 1)* sizeof(uint16_t);

    if (!m_iMemory || !m_iMemory->AllocMemory(reinterpret_cast<void **>(output), size)) {
        return 0;
    };

    const jchar* jStringChars = jenv->GetStringChars(jstrIn, 0);

    memcpy((*output), jStringChars, size);
    (*output)[lengthInChars] = 0;
    jenv->ReleaseStringChars(jstrIn, jStringChars);
    return size;
}

static const char16_t g_EventSource[] = u"AndroidTinyTools";

extern "C" JNIEXPORT void JNICALL Java_com_alexkmbk_androidtinytools_BroadcastReceiverClass_BroadcastMessage(JNIEnv* jenv, jclass jClass, jlong pObject, jstring jsEventName, jstring jsExtraParam)
{

    BroadcastReceiver *broadcastReceiver = (BroadcastReceiver *) pObject;

    if (broadcastReceiver) {

        WCHAR_T *wcEventName = nullptr;
        jstring2v8string(jenv, broadcastReceiver->m_iMemory, jsEventName, &wcEventName);

        WCHAR_T *wcExtraParam = nullptr;
        jstring2v8string(jenv, broadcastReceiver->m_iMemory, jsExtraParam, &wcExtraParam);

        if (broadcastReceiver->m_iConnect != NULL) {
            broadcastReceiver->m_iConnect->ExternalEvent((uint16_t *) g_EventSource,
                                                           wcEventName,
                                                           wcExtraParam);
        }
    }
}