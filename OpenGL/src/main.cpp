#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) glClearError();\
    x;\
    ASSERT(glLogCall())

;

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
    glfwSwapInterval(1);

    if (GLEW_OK != glewInit())
    {
        std::cout << "Glew not ok" << std::endl;
    }
    float positions[20] =
    {
        0.5f,-0.5f,//right bottom
        -0.5f,-0.5f,//left bottom
        0.5f,0.5f,//right top
        -0.5f,0.5f //left top
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,1
    };

    VertexBufferLayout layout;
    layout.Push(2,GL_FLOAT);

    VertexBuffer vbo(positions, sizeof(float)*20);
    IndexBuffer ibo(indices,sizeof(indices));
    VertexArray vao;
    vao.AddBuffer(vbo, layout);

    const std::string filepath = "res/shaders/Basic.shader";
    Shader shader(filepath);


    vbo.unBindBuffer();
    ibo.unBindBuffer();
    shader.Unbind();


    float r = 1.0f;
    float increment = 0.05f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        vbo.BindBuffer();
        ibo.BindBuffer();
        shader.Bind();
        shader.SetUniform4f("u_Color",r, 1.0f, 0.5f, 1.0f);
        GLCall(glDrawElements(GL_TRIANGLES , 6, GL_UNSIGNED_INT, nullptr));
        
        if (r > 1.0f)
            increment = -0.05f;
        else if (r<0.0f)
            increment = 0.05f;
        
        r += increment;
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}