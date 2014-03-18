#include "shader.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <cstdlib>

#include "util.h"

static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);

Shader::Shader()
{
	m_program = glCreateProgram();

	if (m_program == 0) 
	{
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
}

Shader::~Shader()
{
	for(std::vector<int>::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it) 
	{
		glDetachShader(m_program,*it);
		glDeleteShader(*it);
	}
	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::AddUniform(const std::string& uniform)
{
	unsigned int location = glGetUniformLocation(m_program, uniform.c_str());

	assert(location != INVALID_VALUE);

	m_uniforms.insert(std::pair<std::string, int>(uniform, location));
}

void Shader::AddVertexShaderFromFile(const std::string& text)
{
	AddVertexShader(LoadShader(text));
}

void Shader::AddGeometryShaderFromFile(const std::string& text)
{
	AddGeometryShader(LoadShader(text));
}

void Shader::AddFragmentShaderFromFile(const std::string& text)
{
	AddFragmentShader(LoadShader(text));
}

void Shader::AddVertexShader(const std::string& text)
{
	AddProgram(text, GL_VERTEX_SHADER);
}

void Shader::AddGeometryShader(const std::string& text)
{
	AddProgram(text, GL_GEOMETRY_SHADER);
}

void Shader::AddFragmentShader(const std::string& text)
{
	AddProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::AddProgram(const std::string& text, int type)
{
	int shader = glCreateShader(type);

	if(shader == 0)
	{
		fprintf(stderr, "Error creating shader type %d\n", type);
		exit(1);
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();//strlen(text.c_str());

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) 
	{
        GLchar InfoLog[1024];

        glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", shader, InfoLog);

        exit(1);
    }

	glAttachShader(m_program, shader);
	m_shaders.push_back(shader);
}

void Shader::CompileShader()
{
    glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");
 //   glGetProgramiv(program, GL_LINK_STATUS, &success);
	//if (success == 0) 
	//{
	//	glGetProgramInfoLog(program, sizeof(error), NULL, ErrorLog);
	//	fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
 //       exit(1);
	//}

    glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");
    //glGetProgramiv(program, GL_VALIDATE_STATUS, &Success);
    //if (!success) {
    //    glGetProgramInfoLog(ShaderProgram, sizeof(error), NULL, ErrorLog);
    //    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    //    exit(1);
    //}

    //glUseProgram(program);

    //gScaleLocation = glGetUniformLocation(ShaderProgram, "gScale");
    //assert(gScaleLocation != 0xFFFFFFFF);
}

void Shader::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{

}

void Shader::SetUniformi(const std::string& name, int value)
{
	glUniform1i(m_uniforms.at(name), value);
}

void Shader::SetUniformf(const std::string& name, float value)
{
	glUniform1f(m_uniforms.at(name), value);
}

void Shader::SetUniform(const std::string& name, const Vector3f& value)
{
	glUniform3f(m_uniforms.at(name), value.GetX(), value.GetY(), value.GetZ());
}

void Shader::SetUniform(const std::string& name, const Matrix4f& value)
{
	glUniformMatrix4fv(m_uniforms.at(name), 1, GL_FALSE, &(value[0][0]));
}

void Shader::SetAttribLocation(const std::string& attributeName, int location)
{
	glBindAttribLocation(m_program, location, attributeName.c_str());
}

static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
    GLchar error[1024] = { 0 };

	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(!success)
	{
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		fprintf(stderr, "%s: '%s'\n", errorMessage.c_str(), error);
	}
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(("./res/shaders/" + fileName).c_str());

	std::string output;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
};
