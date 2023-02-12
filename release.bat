@echo off
g++ main.cpp lib/glew/libglew32.a lib/glfw/libglfw3.a -lopengl32 -lgdi32 -o main -std=c++17 -O3 -mwindows
