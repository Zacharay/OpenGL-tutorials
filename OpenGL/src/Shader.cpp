#include "Shader.h"
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(const std::string& filePath)
{
    ShaderSources shadersSrc = ParseShader(filePath);
    CreateShader(shadersSrc.VertexSource,shadersSrc.FragmentSource);
    glUseProgram(m_RenderedId);
}

Shader::~Shader()
{
    glDeleteProgram(m_RenderedId);
}

void Shader::Bind()
{
    glUseProgram(m_RenderedId);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    unsigned int location = GetUniformLocation(name);
    glUniform4f(location, v0, v1, v2, v3);

}

ShaderSources Shader::ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
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

unsigned int Shader::CompileShader(unsigned int type, const std::string& sourceCode)
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
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void  Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    m_RenderedId = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(m_RenderedId, vs);
    glAttachShader(m_RenderedId, fs);
    glLinkProgram(m_RenderedId);
    glValidateProgram(m_RenderedId);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_RenderedId, name.c_str());
}
