#pragma once
#include <string>
struct ShaderSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	unsigned int m_RenderedId;
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind();
	void Unbind();

	void SetUniform4f(const std::string&name,float v0,float v1,float v2,float v3);
private:
	unsigned int GetUniformLocation(const std::string& name);
	void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderSources ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
};