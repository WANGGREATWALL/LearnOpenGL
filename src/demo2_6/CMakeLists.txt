set(DEMO_NAME "demo2_6")

include_directories(../../depends/includes)
link_directories(../../depends/libs)

link_libraries(glfw3 opengl32)

file(GLOB SHADERS
        "*.vs"
        "*.fs")

add_executable(${DEMO_NAME} main.cpp ../../depends/glad.c)
add_custom_command(TARGET ${DEMO_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADERS} $<TARGET_FILE_DIR:${DEMO_NAME}>)