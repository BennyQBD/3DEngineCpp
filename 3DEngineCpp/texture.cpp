#include "texture.h"
#include "stb_image.h"
#include <iostream>

Texture* Texture::m_lastBind = 0;

Texture::Texture(const std::string& fileName, GLenum textureTarget, GLfloat filter)
{
	int x, y, numComponents;
	unsigned char* data = stbi_load(("./res/textures/" + fileName).c_str(), &x, &y, &numComponents, 4);

	if(data == NULL)
	{
		std::cerr << "Unable to load texture: " << fileName << std::endl;
	}

	initTexture(x,y,data,textureTarget,filter);
	stbi_image_free(data);
}

Texture::Texture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	initTexture(width, height, data, textureTarget, filter);
}

void Texture::initTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	m_textureTarget = textureTarget;
	m_freeTexture = true;
	
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
	if(m_freeTexture)
		glDeleteTextures(1, &m_textureID);
}

Texture::Texture(Texture& texture)
{
	m_textureTarget = texture.m_textureTarget;
	m_textureID = texture.m_textureID;
	m_freeTexture = true;
	texture.m_freeTexture = false;	
}

void Texture::operator=(Texture& texture)
{
	m_textureTarget = texture.m_textureTarget;
	m_textureID = texture.m_textureID;
	m_freeTexture = true;
	texture.m_freeTexture = false;
}

void Texture::bind(GLenum textureUnit)
{
	if(m_lastBind != this)
	{
		glActiveTexture(textureUnit);
		glBindTexture(m_textureTarget, m_textureID);
		m_lastBind = this;
	}
}
