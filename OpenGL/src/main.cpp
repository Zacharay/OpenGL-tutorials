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
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

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
            0.0f,0.0f, 0.0f,0.0f,//left bottom
            400.0f,0.0f,1.0f,0.0f,//right bottom
            400.0f,400.0f,1.0f,1.0f,//right top
            0.0f,400.0f,0.0f,1.0f//left top
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

    glm::mat4 proj = glm::ortho(0.0f, 1200.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    glm::mat4 view= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));



    Shader shader("res/shaders/Basic.shader");
    Texture texture("res/textures/opengl.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    

    vbo.unBindBuffer();
    ibo.unBindBuffer();

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);
    glm::vec3 translationA(0.0f, 0.0f, 0.0f);
    glm::vec3 translationB(200.0f, 0.0f, 0.0f);
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Hello, world!");

            ImGui::SliderFloat("TranslationA X", &translationA.x, 0.0f, windowWidth-400);
            ImGui::SliderFloat("TranslationA Y", &translationA.y, 0.0f, windowHeight-400);
            ImGui::SliderFloat("TranslationB X", &translationB.x, 0.0f, windowWidth - 400);
            ImGui::SliderFloat("TranslationB Y", &translationB.y, 0.0f, windowHeight - 400);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        shader.Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
        glm::mat4 mvp = proj * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(vao, ibo, shader);

        model = glm::translate(glm::mat4(1.0f), translationB);
        mvp = proj * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(vao, ibo, shader);

        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}