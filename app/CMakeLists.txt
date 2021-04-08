# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories(${PROJECT_SOURCE_DIR}../../../include)

add_compile_options(-O2)


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             AndroidTinyTools

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/jnienv.cpp src/main/cpp/StrConv.cpp src/main/cpp/BroadcastReceiver.cpp src/main/cpp/BluetoothBarcodeScannerHandler.cpp src/main/cpp/AddInNative.cpp )

set_target_properties(AndroidTinyTools PROPERTIES LINK_FLAGS_RELEASE -s)
set_target_properties(AndroidTinyTools PROPERTIES LINK_FLAGS_DEBUG -s)

if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set_target_properties(AndroidTinyTools PROPERTIES SUFFIX "_ARM.so")
else()
    set_target_properties(AndroidTinyTools PROPERTIES SUFFIX "_i386.so")
endif()

set_target_properties(AndroidTinyTools PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}../../Package)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
             log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                        AndroidTinyTools

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )


