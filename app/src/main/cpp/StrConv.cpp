#include "StrConv.h"

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
/*
inline void tolowerPtr(char16_t *p);

// Приведение к нижнему регистру только для Кириллицы и Латиницы
//
char16_t* tolowerStr(const char16_t* str, size_t len)
{
    if (len == 0)
        len = strlen16(str);

    char16_t* res = new char16_t[len];
    memcpy(res, str, len * sizeof(char16_t));
    char16_t* c = res;
    while (c){
        tolowerPtr(c);
        c++;
    }
    return res;
};

inline void tolowerPtr(char16_t *p)
{
    if (((*p >= u'А') && (*p <= u'Я')) || ((*p >= u'A') && (*p <= u'Z')))
        *p = *p + 32;

    else if (*p == u'Ё')
        *p = u'ё';
}

int strlen16(const char16_t* strarg)
{
    if(!strarg)
        return -1; //strarg is NULL pointer
    const char16_t* str = strarg;
    for(;*str;++str)
        ; // empty body
    return str-strarg;
}*/

inline void tolowerPtr(char16_t*);

// Приведение к нижнему регистру только для Кириллицы и Латиницы
//
void tolowerStr(std::basic_string<char16_t> & s)
{
    char16_t* c = const_cast<char16_t*>(s.c_str());
    size_t l = s.size();
    for (char16_t* c2 = c; c2 < c + l; c2++)tolowerPtr(c2);
};

inline void tolowerPtr(char16_t *p)
{
    if (((*p >= u'А') && (*p <= u'Я')) || ((*p >= u'A') && (*p <= u'Z')))
        *p = *p + 32;

    else if (*p == u'Ё')
        *p = u'ё';
}

