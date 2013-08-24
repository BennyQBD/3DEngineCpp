#ifndef SHADER_H
#define SHADER_H

#include <unordered_map>
#include <string>

#include "vector3f.h"
#include "matrix4f.h"
#include "material.h"

class Shader
{
public:
	Shader();
	~Shader();

	void bind();
	void addUniform(const std::string& uniform);
	void addVertexShaderFromFile(const std::string& text);
	void addGeometryShaderFromFile(const std::string& text);
	void addFragmentShaderFromFile(const std::string& text);
	void addVertexShader(const std::string& text);
	void addGeometryShader(const std::string& text);
	void addFragmentShader(const std::string& text);
	void compileShader();

	virtual void updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Material& material);

	void setUniformi(const std::string& name, int value);
	void setUniformf(const std::string& name, float value);
	void setUniform(const std::string& name, const Vector3f& value);
	void setUniform(const std::string& name, const Matrix4f& value);
protected:
private:
	int m_program;
	std::unordered_map<std::string, int> m_uniforms;
	std::vector<int> m_shaders;

	void addProgram(const std::string& text, int type);
};

#endif