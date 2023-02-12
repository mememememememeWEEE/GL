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
}