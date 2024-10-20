//
// Created by avaish on 10-10-2024.
//

#ifndef ARSELFIE_POINT_CLOUD_RENDERER_H
#define ARSELFIE_POINT_CLOUD_RENDERER_H

#include <android/asset_manager.h>
#include <arcore_c_api.h>
#include <GLES2/gl2.h>
#include "glm.h"

namespace ar_selfie{
    class PointCloudRenderer {
    public:
        PointCloudRenderer() = default;
        ~PointCloudRenderer() = default;

        void InitializeGlContent(AAssetManager* asset_manager);

        void Draw(const glm::mat4& mvp_matrix, ArSession* ar_session,
                  ArPointCloud* ar_point_cloud) const;

    private:
        GLuint shader_program_;
        GLint attribute_vertices_;
        GLint uniform_mvp_mat_;
        GLint uniform_color_;
        GLint uniform_point_size_;
    };

}
#endif //ARSELFIE_POINT_CLOUD_RENDERER_H
