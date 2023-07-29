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

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

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

    const int windowWidth = 1200;
    const int windowHeight = 900;
    
    window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", NULL, NULL);
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
    float positions[16]
    {
            100.0f,200.0f, 0.0f,0.0f,//left bottom
            500.0f,200.0f,1.0f,0.0f,//right bottom
            500.0f,600.0f,1.0f,1.0f,//right top
            100.0f,600.0f,0.0f,1.0f//left top
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexBufferLayout layout;
    layout.Push(2,GL_FLOAT);
    layout.Push(2, GL_FLOAT);

    VertexBuffer vbo(positions, sizeof(positions));
    IndexBuffer ibo(indices,sizeof(indices));
    VertexArray vao;
    vao.AddBuffer(vbo, layout);

    ///glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 proj = glm::ortho(0.0f, 1200.0f, 0.0f, 900.0f, -1.0f, 1.0f);


    Shader shader("res/shaders/Basic.shader");
    Texture texture("res/textures/opengl.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniformMat4f("u_MVP", proj);

    vbo.unBindBuffer();
    ibo.unBindBuffer();

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        shader.Bind();

        renderer.Draw(vao, ibo, shader);
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}