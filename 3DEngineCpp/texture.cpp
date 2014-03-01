#include "texture.h"
#include "stb_image.h"
#include <iostream>
#include <cassert>

const Texture* Texture::s_lastBind = 0;

Texture::Texture(const std::string& fileName, GLenum textureTarget, GLfloat filter)
{
	int x, y, bytesPerPixel;
	unsigned char* data = stbi_load(("./res/textures/" + fileName).c_str(), &x, &y, &bytesPerPixel, 4);

	if(data == NULL)
	{
		std::cerr << "Unable to load texture: " << fileName << std::endl;
	}

	InitTexture(x,y,data,textureTarget,filter);
	stbi_image_free(data);
}

Texture::Texture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	InitTexture(width, height, data, textureTarget, filter);
}

void Texture::InitTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	m_textureTarget = textureTarget;
	
	if(width > 0 && height > 0 && data != 0)
	{
		glGenTextures(1, &m_textureID);
		glBindTexture(textureTarget, m_textureID);
		glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);
		glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		m_textureID = 0;
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
}

void Texture::Bind(unsigned int unit) const
{
	if(s_lastBind != this)
	{
		assert(unit >= 0 && unit <= 31);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(m_textureTarget, m_textureID);
		s_lastBind = this;
	}
}
