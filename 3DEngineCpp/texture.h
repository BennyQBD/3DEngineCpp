#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
	Texture(int width = 0, int height = 0, unsigned char* data = 0, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
	virtual ~Texture();

	void Bind(unsigned int unit = 0) const;	
protected:
private:
	Texture(Texture& texture) {}
	void operator=(Texture& texture) {}
	static const Texture* s_lastBind;

	GLenum m_textureTarget;
	GLuint m_textureID;

	void InitTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter);
};

#endif
