#pragma once
#include <cstdlib>

#include "../lib/glfw/glfw3.h"
#include "../lib/glew/glew.h"
#include "../lib/glm/glm.hpp"
#include "KXRM.hpp"

namespace KXRM::Loader {
    GLuint LoadBMP(const char* ImagePath) {
        unsigned char headerp[54];
        unsigned int DataPosition;
        unsigned int width, height;
        unsigned int ImageSize;
        unsigned char * data;

        FILE * file = fopen(ImagePath, "rb");

        if (!file) {
            fprintf(stderr, "Couldn't open the image");
            return 0;
        }

        if (fread(header, 1, 54, file) != 54) {
            fprintf(stderr, "Not a correct BMP file");
            return 0;
        }

        if (header[0] != 'B' || header[1] != 'M') {
            fprintf(stderr, "Not a correct BMP file");
            return 0;
        }

        DataPosition = *(int)&(header[0x0A]);
        ImageSize = *(int)&(header[0x22]);
        width = *(int)&(header[0x12]);
        height = *(int)&(header[0x16]);

        if (ImageSize == 0) ImageSize = width*height*3;
        if (DataPosition == 0) DataPosition = 54;

        data = new unsigned char[ImageSize];
        fread(data, 1, ImageSize, file);
        fclose(file);

        GLuint TextureID;
        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        return TextureID;
    }
}