#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#define HEIGHT 800
#define WIDTH 600

typedef unsigned int uint;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
std::string load_shader_src(const char* filename);

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(HEIGHT, WIDTH, "Aboba", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "FAILED" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "FAILED GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSrc = load_shader_src("assets/vertex_core.glsl");
    const GLchar* vertexShaderGLCHAR = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderGLCHAR, NULL);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        process_input(window);

        glClearColor(0.4, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}
void process_input(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
std::string load_shader_src(const char* filename)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filename);

    if(file.is_open())
    {
        buf << file.rdbuf();
        ret = buf.str();
    }
    else
        std::cout << "FAIL LOAD SHADERS" << std::endl;

    file.close();
    
    return ret;
}