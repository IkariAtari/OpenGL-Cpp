#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <math.h>

using namespace std;

const char* vertex_shader_source = "#version 460 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
const char* fragment_shader_source = "#version 460 core\nout vec4 FragColor\nvoidmain()\n{\nFragColor=vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\0";
unsigned int VBO;
unsigned int VAO;
unsigned int vertex_shader;
unsigned int fragment_shader;
unsigned int shader_program;
GLFWwindow* window;

long time = 0;

float verticles[] =
{
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f,
    0.5f, 0.60f, 0.0f,
  
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1080, 900, "Game", NULL, NULL);

    glfwMakeContextCurrent(window);


    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;

        return -1;
    }
}

void Render()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main()
{
    Init();

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    GLint success;
    char log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, log);
        std::cout << "Shader error:" << log << std::endl;
    }

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, log);
    }

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        time++;
        processInput(window);

        Render();
        
    }

    glfwTerminate();

    return 0;
}