include_directories(../../depends)
include_directories(../../depends/log)
include_directories(../../depends/glad)
include_directories(../../depends/glfw/include)

link_directories(../../depends/glfw/lib)

link_libraries(glfw3 opengl32)

add_executable(proj2_1 main.cpp ../../depends/glad/glad.c)