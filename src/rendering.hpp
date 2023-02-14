#pragma once
#include <cstdlib>

#include "../lib/glfw/glfw3.h"
#include "../lib/glew/glew.h"
#include "../lib/stb/stb_image.h"
#include "KXRM.hpp"

namespace KXRM::Rendering {
    void Initialize() {
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "GLFW initialization failed\n");
            exit(EXIT_FAILURE);
        }
    }

    class Texture final {
    protected:
        GLuint texture;
        int width, height;

    public:
        Texture(const char* path, GLenum type) {
            unsigned char* image = stbi_load(path, &this->width, &this->height, NULL, STBI_rgb_alpha);

            glGenTextures(1, &this->texture);
            glBindTexture(type, texture);

            glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            if (image) {
                glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
                glGenerateMipmap(type);
            } else {
                LOG("TEXTURE LOADING FAILED: %s\n", path);
            }

            glActiveTexture(0);
            glBindTexture(type, 0);
            stbi_image_free(image);
        }

        ~Texture() {
            glDeleteTextures(1, &this->texture);
        }

        inline GLuint getID() const { return this->texture; }
        inline int GetWidth() const { return width; }
        inline int GetHeight() const { return height; }

        void bind(GLint TextureUnit, GLenum type) {
            glActiveTexture(GL_TEXTURE0 + TextureUnit);
            glBindTexture(type, this->texture);
        }

        void unbind(GLenum type) {
            glActiveTexture(0);
            glBindTexture(type, 0);
        }
    };
}