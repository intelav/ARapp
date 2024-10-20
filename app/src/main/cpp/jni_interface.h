//
// Created by avaish on 10-10-2024.
//

#ifndef ARSELFIE_JNI_INTERFACE_H
#define ARSELFIE_JNI_INTERFACE_H
#include <jni.h>
/**
 * Helper functions to provide access to Java from C via JNI.
 */
extern "C" {

// Helper function used to access the jni environment on the current thread.
// In this sample, no consideration is made for detaching the thread when the
// thread exits. This can cause memory leaks, so production applications should
// detach when the thread no longer needs access to the JVM.
JNIEnv *GetJniEnv();

jclass FindClass(const char *classname);
}  // extern "C"

#endif //ARSELFIE_JNI_INTERFACE_H
