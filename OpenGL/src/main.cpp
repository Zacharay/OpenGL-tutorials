#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) glClearError();\
    x;\
    ASSERT(glLogCall())

struct ShaderSources
{
    std::string VertexSource;
    std::string FragmentSource;
};

static void glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool glLogCall()
{
    while (GLenum error = glGetError()) {
        std::cout << "[OPENGL ERROR] " << error << std::endl;
        return false;
    }
    return true;
}

static ShaderSources ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE=-1,
        VERTEX=0,
        FRAGMENT=1
    };
    std::stringstream ss[2];
    std::string line;
    ShaderType type = ShaderType::NONE;


    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(),ss[1].str() };
}

static unsigned int CompileShader(unsigned int type,const std::string& sourceCode)
{
    unsigned int id = glCreateShader(type);
    const char* src = sourceCode.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(900, 900, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);


    if (GLEW_OK != glewInit())
    {
        std::cout << "Glew not ok" << std::endl;
    }
    float positions[20] =
    {
        0.3f,0.4f,
        0.0f,1.0f,
        -0.3f,0.4f,
        -0.9f,0.4f,
        -0.3f,-0.2f,
        0.3f,-0.2f,
        0.9f,0.4f,
        0.0f,-0.6f,
        0.8f,-1.0f,
        -0.8f,-1.0f
    };
    unsigned int indices[] = {
        0,1,2,  
        2,3,4,  
        0,2,4, 
        4,0,5, 
        0,5,6, 
        5,4,7,
        7,5,8,
        7,4,9
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*20, positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);
    glEnableVertexAttribArray(0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    ShaderSources source = ParseShader("res/shaders/Basic.shader");

    unsigned int program = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(program);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        

        GLCall(glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}