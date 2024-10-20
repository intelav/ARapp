//
// Created by avaish on 10-10-2024.
//

#ifndef ARSELFIE_AR_SELFIE_H
#define ARSELFIE_AR_SELFIE_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <jni.h>

#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include "arcore_c_api.h"
#include "background_renderer.h"
#include "glm.h"
#include "obj_renderer.h"
#include "plane_renderer.h"
#include "point_cloud_renderer.h"
#include "texture.h"
#include "util.h"
#include <mutex>

namespace ar_selfie {

class ArSelfie{
public:
    explicit ArSelfie(AAssetManager* asset_manager);
    ~ArSelfie();

    void OnPause();

    void OnResume(JNIEnv* env, void* context, void* activity);

    void OnSurfaceCreated();

    void OnDisplayGeometryChanged(int display_rotation, int width, int height);

    void OnDrawFrame(bool depthColorVisualizationEnabled,
                     bool useDepthForOcclusion);

    void OnTouched(float x, float y);

    bool HasDetectedPlanes() const { return plane_count_ > 0; }

    bool IsDepthSupported();

    void OnSettingsChange(bool is_instant_placement_enabled);

private:
    glm::mat3 GetTextureTransformMatrix(const ArSession* session,
                                        const ArFrame* frame);
    std::mutex frame_image_in_use_matrix;
    ArSession* ar_session_ = nullptr;
    ArFrame* ar_frame_ = nullptr;

    bool install_requested_ = false;
    bool calculate_uv_transform_ = false;
    int width_ = 1;
    int height_ = 1;
    int display_rotation_ = 0;
    bool is_instant_placement_enabled_ = true;

    AAssetManager*  asset_manager_;

    struct ColoredAnchor {
        ArAnchor* anchor;
        ArTrackable* trackable;
        float color[4];
    };
    std::vector<ColoredAnchor> anchors_;
    PointCloudRenderer point_cloud_renderer_;
    BackgroundRenderer background_renderer_;
    PlaneRenderer plane_renderer_;
    ObjRenderer andy_renderer_;
    Texture depth_texture_;

    int32_t plane_count_ = 0;

    void ConfigureSession();

    void UpdateAnchorColor(ColoredAnchor* colored_anchor);

    void ChangeCameraConfig(int32_t option);
};


}

#endif //ARSELFIE_AR_SELFIE_H
