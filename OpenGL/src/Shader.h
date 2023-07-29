#pragma once
#include <string>
#include <unordered_map>
#include "vendor/glm/glm.hpp"
struct ShaderSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	unsigned int m_RenderedId;
	std::unordered_map<std::string,int>m_uniformLocationCache;
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind()const;
	void Unbind()const;

	void SetUniform4f(const std::string&name,float v0,float v1,float v2,float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& proj);
	void SetUniform1i(const std::string&name,int value);
private:
	int GetUniformLocation(const std::string& name);
	void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderSources ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
};