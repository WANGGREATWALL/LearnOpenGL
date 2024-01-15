#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <log/logger.h>
volatile int G_LEVEL_LOGGER = 0;

#define WINDOW_TITLE "demo2_3"
#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

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

    const char* vshaderSource = 
        "#version 330 \n"
        "void main(void) { gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
    
    const char* fshaderSource = 
        "#version 330 \n"
        "out vec4 color; \n"
        "void main(void) { color = vec4(0.0, 0.0, 1.0, 1.0); }";
    
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, nullptr);
    glShaderSource(fShader, 1, &fshaderSource, nullptr);

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
    LOGGER_I("hello!\n");

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