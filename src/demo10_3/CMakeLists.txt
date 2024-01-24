set(DEMO_NAME "demo10_3")

set(INC_DIR 
        "../../depends"
        "../../depends/includes")

set(SRC_FILE 
        "main.cpp"
        "../../depends/glad.c"
        "../../depends/Utils.cpp"
        "../../depends/Torus.cpp"
        "../../depends/Sphere.cpp"
        "../../depends/ImportedModel.cpp")

set(LIB_DIR "../../depends/libs")

set(LIB_LIST 
        "glfw3" 
        "opengl32")

include_directories(${INC_DIR})
link_directories(${LIB_DIR})
link_libraries(${LIB_LIST})

file(GLOB SHADERS
        "*.vs"
        "*.fs"
        "*.jpg"
        "*.obj")

add_executable(${DEMO_NAME} ${SRC_FILE})
add_custom_command(TARGET ${DEMO_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADERS} $<TARGET_FILE_DIR:${DEMO_NAME}>)