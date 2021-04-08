//
// Created by Alexey on 17.05.2020.
//

#ifndef ANDROIDTINYTOOLSFOR1C_STRCONV_H
#define ANDROIDTINYTOOLSFOR1C_STRCONV_H

#include <jni.h>
#include <cstring>
#include <string>
#include <types.h>
#include <IMemoryManager.h>


long jstring2v8string(JNIEnv *jenv, IMemoryManager *m_iMemory, jstring jstrIn, WCHAR_T **output);

/*char16_t* tolowerStr(const char16_t* str, size_t len = 0);

int strlen16(const char16_t* strarg);*/


// Приведение к нижнему регистру только для Кириллицы и Латиницы
//
void tolowerStr(std::basic_string<char16_t> & s);

#endif //ANDROIDTINYTOOLSFOR1C_STRCONV_H
