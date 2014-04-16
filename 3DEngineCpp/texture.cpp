#include "texture.h"
#include "stb_image.h"
#include <iostream>
#include <cassert>

std::map<std::string, TextureData*> Texture::s_resourceMap;

TextureData::TextureData(GLenum textureTarget)
{
	glGenTextures(1, &m_textureID);
	m_textureTarget = textureTarget;
}

TextureData::~TextureData()
{
	if(m_textureID) glDeleteTextures(1, &m_textureID);
}


Texture::Texture(const std::string& fileName, GLenum textureTarget, GLfloat filter)
{
 	m_fileName = fileName;

	std::map<std::string, TextureData*>::const_iterator it = s_resourceMap.find(fileName);
	if(it != s_resourceMap.end())
	{
		m_textureData = it->second;
		m_textureData->AddReference();
	}
	else
	{
		int x, y, bytesPerPixel;
		unsigned char* data = stbi_load(("./res/textures/" + fileName).c_str(), &x, &y, &bytesPerPixel, 4);

		if(data == NULL)
		{
			std::cerr << "Unable to load texture: " << fileName << std::endl;
		}

		InitTexture(x,y,data,textureTarget,filter);
		stbi_image_free(data);
		
		s_resourceMap.insert(std::pair<std::string, TextureData*>(fileName, m_textureData));
	}
}

Texture::Texture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	m_fileName = "";
	InitTexture(width, height, data, textureTarget, filter);
}

Texture::~Texture()
{
	if(m_textureData && m_textureData->RemoveReference())
	{
		if(m_fileName.length() > 0)
			s_resourceMap.erase(m_fileName);
			
		delete m_textureData;
	}
}

void Texture::InitTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	if(width > 0 && height > 0 && data != 0)
	{
		m_textureData = new TextureData(textureTarget);
		glBindTexture(textureTarget, m_textureData->GetTextureID());
		
		glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);
		
		glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}

void Texture::Bind(unsigned int unit) const
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(m_textureData->GetTextureTarget(), m_textureData->GetTextureID());
}
