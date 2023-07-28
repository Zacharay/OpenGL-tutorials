#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

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

    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
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
    float positions[16] =
    {
        -0.5f,-0.5f,0.0f,0.0f,//left bottom
        0.5f,-0.5f, 1.0f,0.0f,//right bottom
        0.5f,0.5f,1.0f,1.0f,//right top
        -0.5f,0.5f,0.0f,1.0f //left top
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexBufferLayout layout;
    layout.Push(2,GL_FLOAT);
    layout.Push(2, GL_FLOAT);

    VertexBuffer vbo(positions, sizeof(float)*20);
    IndexBuffer ibo(indices,sizeof(indices));
    VertexArray vao;
    vao.AddBuffer(vbo, layout);

    Shader shader("res/shaders/Basic.shader");
    Texture texture("res/textures/stone.jpg");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    

    vbo.unBindBuffer();
    ibo.unBindBuffer();
    shader.Unbind();

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        renderer.Draw(vao, ibo, shader);
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}