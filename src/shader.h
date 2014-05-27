#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <vector>
#include <string>

#include "referenceCounter.h"
#include "math3d.h"
#include "material.h"
#include "renderingEngine.h"
#include "lighting.h"
#include "transform.h"

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

class ShaderData : public ReferenceCounter
{
public:
	ShaderData(const std::string& fileName);
	virtual ~ShaderData();
	
	inline int GetProgram() { return m_program; }
	inline std::vector<int>& GetShaders() { return m_shaders; }
	inline std::vector<std::string>& GetUniformNames() { return m_uniformNames; }
	inline std::vector<std::string>& GetUniformTypes() { return m_uniformTypes; }
	inline std::map<std::string, unsigned int>& GetUniformMap() { return m_uniformMap; }
private:
	void AddVertexShader(const std::string& text);
	void AddGeometryShader(const std::string& text);
	void AddFragmentShader(const std::string& text);
	void AddProgram(const std::string& text, int type);
	
	void AddAllAttributes(const std::string& vertexShaderText);
	void AddShaderUniforms(const std::string& shaderText);
	void AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs);
	void CompileShader();

	int m_program;
	std::vector<int> m_shaders;
	std::vector<std::string> m_uniformNames;
	std::vector<std::string> m_uniformTypes;
	std::map<std::string, unsigned int> m_uniformMap;
};

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();
	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);

	void SetUniformi(const std::string& uniformName, int value);
	void SetUniformf(const std::string& uniformName, float value);
	void SetUniformMatrix4f(const std::string& uniformName, const Matrix4f& value);
	void SetUniformVector3f(const std::string& uniformName, const Vector3f& value);
protected:
private:
	static std::map<std::string, ShaderData*> s_resourceMap;

	ShaderData* m_shaderData;
	std::string m_fileName;
	
	void SetUniformDirectionalLight(const std::string& uniformName, const DirectionalLight& value);
	void SetUniformPointLight(const std::string& uniformName, const PointLight& value);
	void SetUniformSpotLight(const std::string& uniformName, const SpotLight& value);
};

#endif
