#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <vector>
#include <string>

#include "vector3f.h"
#include "matrix4f.h"
#include "material.h"

class Shader
{
public:
	Shader();
	virtual ~Shader();

	void Bind();
	void AddUniform(const std::string& uniform);
	void AddVertexShaderFromFile(const std::string& text);
	void AddGeometryShaderFromFile(const std::string& text);
	void AddFragmentShaderFromFile(const std::string& text);
	void AddVertexShader(const std::string& text);
	void AddGeometryShader(const std::string& text);
	void AddFragmentShader(const std::string& text);
	void CompileShader();

	virtual void UpdateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, const Material& material);

	void SetAttribLocation(const std::string& attributeName, int location);
	void SetUniformi(const std::string& name, int value);
	void SetUniformf(const std::string& name, float value);
	void SetUniform(const std::string& name, const Vector3f& value);
	void SetUniform(const std::string& name, const Matrix4f& value);
protected:
private:
	int m_program;
	std::map<std::string, int> m_uniforms;
	std::vector<int> m_shaders;

	void AddProgram(const std::string& text, int type);
};

#endif
