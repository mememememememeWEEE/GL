#pragma once
#include <cstdlib>

#include "../lib/glfw/glfw3.h"
#include "../lib/glew/glew.h"
#include "KXRM.hpp"

namespace KXRM::Rendering {
    void Initialize() {
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "GLFW initialization failed\n");
            exit(EXIT_FAILURE);
        }
    }

    class Texture final {
    public:
        unsigned int RendererID;
        const char * FilePath;
        unsigned char * LocalBuffer;
        int Width, Height;
        
        inline int GetWidth() const { return Width; }
        inline int GetHeight() const { return Height; }
    }
}