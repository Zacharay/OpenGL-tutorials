#pragma once
#include <string>

class Texture {
private:
	unsigned int m_RendererID;
	std::string m_filePath;
	unsigned char* m_LocalBuffer;

	int m_Width;
	int m_Height;
	int m_BPP;
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot =0)const;
	void Unbind()const;

	inline unsigned int getWidth()const { return m_Width; };
	inline unsigned int getHeight()const { return m_Height; };
};