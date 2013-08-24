#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include <string>

class Texture
{
public:
	Texture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
	Texture(int width = 0, int height = 0, unsigned char* data = 0, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
	~Texture();

	void bind(GLenum textureUnit = GL_TEXTURE0);
	Texture(Texture& texture);
	void operator=(Texture& texture);
protected:
private:
	static Texture* m_lastBind;

	GLenum m_textureTarget;
	GLuint m_textureID;
	bool m_freeTexture;

	void initTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter);
};

#endif