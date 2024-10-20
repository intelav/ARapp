//
// Created by avaish on 09-10-2024.
//
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <jni.h>
#include "ar_selfie.h"
#include "util.h"


#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_svargames_arselfie_JniInterface_##method_name

extern "C" {
namespace {
    static JavaVM *g_vm = nullptr;

    inline jlong jptr(ar_selfie::ArSelfie *native_ar_selfie) {
        return reinterpret_cast<intptr_t>(native_ar_selfie);
        //}
    }

    inline ar_selfie::ArSelfie *native(jlong ptr) {
        return reinterpret_cast<ar_selfie::ArSelfie *>(ptr);
    }
}


jint JNI_OnLoad(JavaVM *vm, void *) {
    g_vm = vm;
    return JNI_VERSION_1_6;
}

JNI_METHOD(jlong, createNativeApplication)
(JNIEnv *env, jclass, jobject j_asset_manager) {
    AAssetManager *asset_manager = AAssetManager_fromJava(env, j_asset_manager);
    LOGI("%s called", __func__);
    return jptr(new ar_selfie::ArSelfie(asset_manager));
}
JNI_METHOD(jboolean, isDepthSupported)
(JNIEnv *, jclass, jlong native_application) {
    LOGI("%s called", __func__);
    return native(native_application)->IsDepthSupported();
}

JNI_METHOD(void, onSettingsChange)
(JNIEnv *, jclass, jlong native_application,
 jboolean is_instant_placement_enabled) {
    LOGI("%s called", __func__);
    native(native_application)->OnSettingsChange(is_instant_placement_enabled);
}

JNI_METHOD(void, destroyNativeApplication)
(JNIEnv *, jclass, jlong native_application) {
    LOGI("%s called", __func__);
    delete native(native_application);
}

JNI_METHOD(void, onPause)
(JNIEnv *, jclass, jlong native_application) {
    LOGI("%s called", __func__);
    native(native_application)->OnPause();
}

JNI_METHOD(void, onResume)
(JNIEnv *env, jclass, jlong native_application, jobject context,
 jobject activity) {
    LOGI("%s called", __func__);
    native(native_application)->OnResume(env, context, activity);
}

JNI_METHOD(void, onGlSurfaceCreated)
(JNIEnv *, jclass, jlong native_application) {
    LOGI("%s called", __func__);
    native(native_application)->OnSurfaceCreated();
}

JNI_METHOD(void, onDisplayGeometryChanged)
(JNIEnv *, jclass, jlong native_application, int display_rotation, int width,
 int height) {
    LOGI("%s called", __func__);
    native(native_application)
            ->OnDisplayGeometryChanged(display_rotation, width, height);
}

JNI_METHOD(void, onGlSurfaceDrawFrame)

(JNIEnv *, jclass, jlong native_application,
 jboolean depth_color_visualization_enabled, jboolean use_depth_for_occlusion) {
   // LOGI("%s called", __func__);
    native(native_application)
            ->OnDrawFrame(depth_color_visualization_enabled, use_depth_for_occlusion);
}

JNI_METHOD(void, onTouched)
(JNIEnv *, jclass, jlong native_application, jfloat x, jfloat y) {
    LOGI("%s called", __func__);
    native(native_application)->OnTouched(x, y);
}

JNI_METHOD(jboolean, hasDetectedPlanes)
(JNIEnv *, jclass, jlong native_application) {
    LOGI("%s called", __func__);
    return static_cast<jboolean>(
            native(native_application)->HasDetectedPlanes() ? JNI_TRUE : JNI_FALSE);
}

JNIEnv *GetJniEnv() {
    JNIEnv *env;
    jint result = g_vm->AttachCurrentThread(&env, nullptr);
    return result == JNI_OK ? env : nullptr;
}

jclass FindClass(const char *classname) {
    JNIEnv *env = GetJniEnv();
    return env->FindClass(classname);
}
} //extern C