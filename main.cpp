#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC
#define DEBUG //for now

#include <cstdio>
#include <cstdlib>
#include "lib/glew/glew.h"
#include "lib/glfw/glfw3.h"
#include "app.hpp"

static GLuint CompileShader(GLuint type, const char* source) {
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

#ifdef DEBUG
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*) __builtin_alloca(length * sizeof(char)); //based stack allocation versus virgin malloc
		glGetShaderInfoLog(id, length, &length, message);
		printf("Failed to compile %s shader: \n%s\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
		glDeleteShader(id);
		exit(-1);
	}
#endif
	
	return id;
}

static int CreateShader(const char* vertexShader, const char* fragmentShader) {
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void error_callback([[maybe_unused]] int error, const char* description) {
	fprintf(stderr, "%s", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	
// 	GLFWwindow* window;
// 	if (!glfwInit()) {
// #ifdef DEBUG
// 		printf("GLFW initialization failed\n");
// #endif
// 		return -1;
// 	}

// 	glfwSetErrorCallback(error_callback);

// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
// 	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// 	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// 	window = glfwCreateWindow(600, 400, "Hello", NULL, NULL);
// 	if (!window) {
// #ifdef DEBUG
// 		printf("Window creation failed\n");
// #endif
// 		glfwTerminate();
// 		return -1;
// 	}

// 	glfwMakeContextCurrent(window);
// 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

// 	if (glewInit() != GLEW_OK) {
// #ifdef DEBUG
// 		printf("GLEW initialization failed\n");
// #endif
// 		return -1;
// 	}

// #ifdef DEBUG
// 	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
// #endif

	// glViewport(0, 0, 600, 400);
	Window::SetupWindow(600, 400, "Hello World");
	Window::InitWindow();

	float positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f, 
		0.5f, -0.5f
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); 

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

	const char * vertexShader = 
		"#version 330 core\n"
		"layout(location=0) in vec4 position;\n"
		"void main() {\n"
		"gl_Position = position;\n"
		"}\n";

	const char * fragmentShader = 
		"#version 330 core\n"
		"layout(location=0) out vec4 color;\n"
		"void main() {\n"
		"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	GLuint shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	while (!glfwWindowShouldClose(Window::window)) {
		//render here:
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		//exchange front and back buffers
		glfwSwapBuffers(Window::window);

		//Poll for and process events
		glfwPollEvents();
	}

	Window::DestroyWindow();
	return 0;
}
