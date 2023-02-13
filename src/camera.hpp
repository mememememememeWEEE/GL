#pragma once
#include <cstdlib>

#include "../lib/glfw/glfw3.h"
#include "../lib/glew/glew.h"
#include "../lib/glm/glm.hpp"
#include "KXRM.hpp"

namespace KXRM::Camera {
    glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 CameraDirection; //sussy stuff
}