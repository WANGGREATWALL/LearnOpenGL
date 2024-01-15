include_directories(../../depends/includes)

link_directories(../../depends/libs)

link_libraries(glfw3 opengl32)

add_executable(demo2_3 main.cpp ../../depends/glad.c)