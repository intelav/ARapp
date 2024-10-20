//
// Created by avaish on 10-10-2024.
//

#ifndef ARSELFIE_OBJ_RENDERER_H
#define ARSELFIE_OBJ_RENDERER_H

#include <android/asset_manager.h>
#include <GLES2/gl2.h>
#include "glm.h"
#include <string>

namespace ar_selfie {
    class ObjRenderer {
    public:
        ObjRenderer() = default;
        ~ObjRenderer() = default;

        void InitializeGlContent(AAssetManager* asset_manager,
                                 const std::string& obj_file_name,
                                 const std::string& png_file_name);

        void SetMaterialProperty(float ambient, float diffuse, float specular,
                                 float specular_power);

        void Draw(const glm::mat4& projection_mat, const glm::mat4& view_mat,
                  const glm::mat4& model_mat, const float* color_correction4,
                  const float* object_color4) const;

        void SetUvTransformMatrix(const glm::mat3& uv_transform) {
            uv_transform_ = uv_transform;
        }

        void SetDepthTexture(int texture_id, int width, int height) {
            depth_texture_id_ = texture_id;
            depth_aspect_ratio_ = (float)width / (float)height;
        }

        void setUseDepthForOcclusion(AAssetManager* asset_manager,
                                     bool use_depth_for_occlusion);

    private:
        void compileAndLoadShaderProgram(AAssetManager* asset_manager);

        // Shader material lighting pateremrs
        float ambient_ = 0.0f;
        float diffuse_ = 2.0f;
        float specular_ = 0.5f;
        float specular_power_ = 6.0f;

        // Model attribute arrays
        std::vector<GLfloat> vertices_;
        std::vector<GLfloat> uvs_;
        std::vector<GLfloat> normals_;

        // Model triangle indices
        std::vector<GLushort> indices_;

        // Loaded TEXTURE_2D object name
        GLuint texture_id_;
        GLuint depth_texture_id_;

        // Shader program details
        GLuint shader_program_;
        GLint position_attrib_;
        GLint tex_coord_attrib_;
        GLint normal_attrib_;
        GLint mvp_mat_uniform_;
        GLint mv_mat_uniform_;
        GLint texture_uniform_;
        GLint lighting_param_uniform_;
        GLint material_param_uniform_;
        GLint color_correction_param_uniform_;
        GLint color_uniform_;
        GLint depth_texture_uniform_;
        GLint depth_uv_transform_uniform_;
        GLint depth_aspect_ratio_uniform_;

        bool use_depth_for_occlusion_ = false;
        float depth_aspect_ratio_ = 0.0f;
        glm::mat3 uv_transform_ = glm::mat3(1.0f);




    };
}
#endif //ARSELFIE_OBJ_RENDERER_H
