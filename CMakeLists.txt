cmake_minimum_required(VERSION 3.10)

project(LearnOpenGL)

include_directories(./depends)

link_directories(./libs)
link_libraries(glfw3 opengl32)

add_executable(LearnOpenGL src/main.cpp depends/glad/glad.c)