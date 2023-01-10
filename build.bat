@echo off
gcc main.cpp lib/glew/libglew32.a lib/glfw/libglfw3.a -lopengl32 -lgdi32 -o main -O2 -Wall -Wextra
