//
// Created by avaish on 10-10-2024.
//

#ifndef ARSELFIE_BACKGROUND_RENDERER_H
#define ARSELFIE_BACKGROUND_RENDERER_H

#include <android/asset_manager.h>
#include <arcore_c_api.h>
#include <GLES2/gl2.h>

namespace ar_selfie{
    class BackgroundRenderer {
    public:
        BackgroundRenderer() = default;
        ~BackgroundRenderer() = default;

        void InitializeGlContent(AAssetManager* asset_manager, int depthTextureId);

        void Draw(const ArSession* session, const ArFrame* frame,
                  bool debug_show_depth_map);

        GLuint GetTextureId() const;

    private:
        static constexpr  int kNumVertices = 4;

        GLuint camera_program_;
        GLuint depth_program_;

        GLuint camera_texture_id_;
        GLuint depth_texture_id_;
        GLuint depth_color_palette_id_;

        GLuint camera_position_attrib_;
        GLuint camera_tex_coord_attrib_;
        GLuint camera_texture_uniform_;

        GLuint depth_texture_uniform_;
        GLuint depth_color_palette_uniform_;
        GLuint depth_position_attrib_;
        GLuint depth_tex_coord_attrib_;

        float transformed_uvs_[kNumVertices * 2];
        bool uvs_initialized_ = false;
    };

}
#endif //ARSELFIE_BACKGROUND_RENDERER_H
