#pragma once
#include <cstdlib>

#include "../lib/glfw/glfw3.h"
#include "../lib/glew/glew.h"
#include "KXRM.hpp"


//I'm too lazy to make a singleton class here
namespace KXRM::Window {
    struct RenderConfig final {
        int OpenGL_VERSION_MAJOR = 3;
        int OpenGL_VERSION_MINOR = 0;
        int Window_RESIZEABLE = GL_TRUE;
    };

    GLFWwindow* window;
    size_t WindowWidth = 600;
    size_t WindowHeight = 400;
    const char* WindowTitle = "Window";

    void SetupWindow(int width, int height, const char* title) {
        WindowWidth = width; 
        WindowHeight = height;
        WindowTitle = title;
    }

    void InitWindow(RenderConfig settings) {
        if (!glfwInit()) {
		    fprintf(stderr, "GLFW initialization failed\n");
		    exit(EXIT_FAILURE);
        }

	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.OpenGL_VERSION_MAJOR);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.OpenGL_VERSION_MINOR);
        glfwWindowHint(GLFW_RESIZABLE, settings.Window_RESIZEABLE);

	    window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);

        if (!window) {
		    fprintf(stderr, "Window creation failed\n");
		    glfwTerminate();
		    exit(EXIT_FAILURE);
	    }

        glfwMakeContextCurrent(window);
        glViewport(0, 0, WindowWidth, WindowHeight);

	    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    }

    void DestroyWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool IsOpen() {
        return (!glfwWindowShouldClose(window));
    }
}