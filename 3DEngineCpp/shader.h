#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <vector>
#include <string>

#include "math3d.h"
#include "material.h"
#include "renderingEngine.h"
#include "transform.h"

struct UniformData
{
    unsigned int Location;
    std::string Type;
    
    UniformData(unsigned int UniformLocation, const std::string& UniformType)
    {
        Location = UniformLocation;
        Type = UniformType;
    }
};

struct TypedData
{
	std::string name;
	std::string type;
};

struct UniformStruct
{
	std::string name;
	std::vector<TypedData> memberNames;
};

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();
	void AddVertexShader(const std::string& text);
	void AddGeometryShader(const std::string& text);
	void AddFragmentShader(const std::string& text);
	void CompileShader();

	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);

	void SetAttribLocation(const std::string& attributeName, int location);
	void SetUniformi(const std::string& name, int value);
	void SetUniformf(const std::string& name, float value);
	void SetUniform(const std::string& name, const Matrix4f& value);
	void SetUniform(const std::string& name, const Vector3f& value);
protected:
private:
	int m_program;
	std::map<std::string, UniformData> m_uniforms;
	std::vector<int> m_shaders;
	
	void AddShaderUniforms(const std::string& shaderText);
	void AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs);
	void AddAllAttributes(const std::string& vertexShaderText);

	void AddProgram(const std::string& text, int type);
};

#endif
