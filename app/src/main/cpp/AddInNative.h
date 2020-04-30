#ifndef __ADDINNATIVE_H__
#define __ADDINNATIVE_H__


#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"
#include "BroadcastReceiver.h"


///////////////////////////////////////////////////////////////////////////////
// class CAddInNative
class CAddInNative : public IComponentBase
{
public:
    enum Props
    {
        ePropLast      // Always last
    };

    enum Methods
    {
		eMethVibrate = 0,
        eMethBeep = 1,
        eMethToast = 2,
        eMethStartBroadcastReceiver = 3,
        eMethLast      // Always last
    };

    CAddInNative(void);
    virtual ~CAddInNative();
    // IInitDoneBase
    virtual bool ADDIN_API Init(void*);
    virtual bool ADDIN_API setMemManager(void* mem);
    virtual long ADDIN_API GetInfo();
    virtual void ADDIN_API Done();
    // ILanguageExtenderBase
    virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T**);
    virtual long ADDIN_API GetNProps();
    virtual long ADDIN_API FindProp(const WCHAR_T* wsPropName);
    virtual const WCHAR_T* ADDIN_API GetPropName(long lPropNum, long lPropAlias);
    virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant* pvarPropVal);
    virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant* varPropVal);
    virtual bool ADDIN_API IsPropReadable(const long lPropNum);
    virtual bool ADDIN_API IsPropWritable(const long lPropNum);
    virtual long ADDIN_API GetNMethods();
    virtual long ADDIN_API FindMethod(const WCHAR_T* wsMethodName);
    virtual const WCHAR_T* ADDIN_API GetMethodName(const long lMethodNum, 
                            const long lMethodAlias);
    virtual long ADDIN_API GetNParams(const long lMethodNum);
    virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum,
                            tVariant *pvarParamDefValue);   
    virtual bool ADDIN_API HasRetVal(const long lMethodNum);
    virtual bool ADDIN_API CallAsProc(const long lMethodNum,
                    tVariant* paParams, const long lSizeArray);
    virtual bool ADDIN_API CallAsFunc(const long lMethodNum,
                tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);
    // LocaleBase
    virtual void ADDIN_API SetLocale(const WCHAR_T* loc);

    IAddInDefBaseEx      *m_iConnect;
    IMemoryManager     *m_iMemory;

private:
    //long findName(const char16_t* names[], const char16_t* name, const uint32_t size) const;
	void Vibrate(tVariant* paParams, const long lSizeArray);
    void Beep(tVariant* paParams, const long lSizeArray);
    void Toast(tVariant* paParams, const long lSizeArray);
    void StartBroadcastReceiver(tVariant *paParams, const long lSizeArray);
    void StopBroadcastReceiver();

    BroadcastReceiver broadcastReceiver;
};

#endif //__ADDINNATIVE_H__
