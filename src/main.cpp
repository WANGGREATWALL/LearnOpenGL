#include <string>
#include <fstream>
#include <iostream>
#include <log/logger.h>
#include <rapidjson/rapidjson_helper.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

volatile int G_LEVEL_LOGGER = 0;

void showBanner(const std::string version)
{
    printf("========================================================================================\n");
    printf("*  __    _____ _____ _____ __  _   _____ _____ _____ __  _ _____ __                     \n");
    printf("* |  |  |  ___|  _  |  __ |  \\| | |     |  __ |  ___|  \\| |   __|  |                    \n");
    printf("* |  |__|  ___|     |   __|     | |  |  |   __|  ___|     |  |_ |  |__                  \n");
    printf("* |_____|_____|__|__|__|\\_|_|\\__| |_____|__|  |_____|_|\\__|_____|_____| version:%s      \n", version.c_str());
    printf("*                                                                                       \n");
    printf("========================================================================================\n");
}

void display(GLFWwindow* window, double currentTime)
{
    glClearColor(1.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

int firstOpenGLDemo()
{
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 600, __FUNCTION__, nullptr, nullptr);
    if (window == nullptr) {
        LOGGER_E("Failed to create GLFW window! (%s:%d)\n", __FILE__, __LINE__);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOGGER_E("Failed to initialize GLAD! (%s:%d)\n", __FILE__, __LINE__);
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

int main()
{
    std::string pathJson("../../params.json");
    RapidJsonHelper json;
    int retLoadJson = json.loadFromFile(pathJson);
    CHECK_WITH_RET(retLoadJson == ErrCode::success, ErrCode::file_open_error);

    showBanner(json.getString("version"));

    int retFirstOpenGLDemo = firstOpenGLDemo();
    CHECK_WITH_RET(retFirstOpenGLDemo == EXIT_SUCCESS, retFirstOpenGLDemo);

    return ErrCode::success;
}