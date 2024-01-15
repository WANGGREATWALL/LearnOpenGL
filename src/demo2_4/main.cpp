#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <log/logger.h>
volatile int G_LEVEL_LOGGER = 0;

#define WINDOW_TITLE "demo2_4"
#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

std::string readShaderSource(const char* filePath)
{
    std::ifstream ifile(filePath, std::ifstream::in | std::ifstream::binary);
	if (!ifile.is_open())
		LOGGER_E("failed to open %s!\n", filePath);

	std::ostringstream buffStream;
	std::string str;
	while (std::getline(ifile, str))
		buffStream << str << std::endl;
	
	return buffStream.str();
}

void printShaderLog(GLuint shader)
{
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        LOGGER_E("shader error log: %s\n", log);
        free(log);
    }
}

void printProgramLog(GLuint prog)
{
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        LOGGER_E("gl program error log: %s\n", log);
        free(log);
    }
}

bool checkOpenGLError()
{
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        LOGGER_E("glError: %d\n", glErr);
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

GLuint createShaderProgram()
{
    GLint vertCompiled = 0;
    GLint fragCompiled = 0;
    GLint linked = 0;

    std::string vertShaderStr = readShaderSource("shader.vs");
    std::string fragShaderStr = readShaderSource("shader.fs");

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();
    
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vertShaderSrc, nullptr);
    glShaderSource(fShader, 1, &fragShaderSrc, nullptr);

    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
        LOGGER_E("vertex compilation failed!\n");
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
        LOGGER_E("fragment compilation failed!\n");
        printShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        LOGGER_E("linking failed!\n");
        printProgramLog(vfProgram);
    }

    return vfProgram;
}

void init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime)
{
    glUseProgram(renderingProgram);
    glPointSize(30.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

int main()
{
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 600, WINDOW_TITLE, nullptr, nullptr);
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

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}