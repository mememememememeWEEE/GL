#pragma once
#include <cstdlib>

#include "../lib/glfw/glfw3.h"
#include "../lib/glew/glew.h"

//I'm too lazy to make a singleton class here
namespace Window {
    GLFWwindow* window;
    size_t WindowWidth = 600, WindowHeight = 400;
    const char* WindowTitle = "Window";

    void SetupWindow(int width, int height, const char* title) {
        WindowWidth = width; WindowHeight = height; WindowTitle = title;
    }

    void InitWindow() {
        if (!glfwInit()) {
		    fprintf(stderr, "GLFW initialization failed\n");
		    exit(EXIT_FAILURE);
        }

	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	    window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);

        if (!window) {
		    fprintf(stderr, "Window creation failed\n");
		    glfwTerminate();
		    exit(EXIT_FAILURE);
	    }

        glfwMakeContextCurrent(window);
        glViewport(0, 0, WindowWidth, WindowHeight);

        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "GLFW initialization failed\n");
            exit(EXIT_FAILURE);
        }

	    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    }

    void DestroyWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}