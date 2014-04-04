#include "shader.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <cstdlib>

#include "util.h"

//--------------------------------------------------------------------------------
// Variable Initializations
//--------------------------------------------------------------------------------
std::map<std::string, ShaderData*> Shader::s_resourceMap;

//--------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------
static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);
static std::vector<UniformStruct> FindUniformStructs(const std::string& shaderText);
static std::string FindUniformStructName(const std::string& structStartToOpeningBrace);
static std::vector<TypedData> FindUniformStructComponents(const std::string& openingBraceToClosingBrace);
static std::string LoadShader(const std::string& fileName);

//--------------------------------------------------------------------------------
// Constructors/Destructors
//--------------------------------------------------------------------------------
ShaderData::ShaderData(const std::string& fileName)
{
	m_program = glCreateProgram();

	if (m_program == 0) 
	{
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
    
    std::string vertexShaderText = LoadShader(fileName + ".vs");
    std::string fragmentShaderText = LoadShader(fileName + ".fs");
    
    AddVertexShader(vertexShaderText);
    AddFragmentShader(fragmentShaderText);
    
    AddAllAttributes(vertexShaderText);
    
    CompileShader();
    
    AddShaderUniforms(vertexShaderText);
    AddShaderUniforms(fragmentShaderText);
}

ShaderData::~ShaderData()
{
	for(std::vector<int>::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it) 
	{
		glDetachShader(m_program,*it);
		glDeleteShader(*it);
	}
	glDeleteProgram(m_program);
}

Shader::Shader(const std::string& fileName)
{
	m_fileName = fileName;

	std::map<std::string, ShaderData*>::const_iterator it = s_resourceMap.find(fileName);
	if(it != s_resourceMap.end())
	{
		m_shaderData = it->second;
		m_shaderData->AddReference();
	}
	else
	{
		m_shaderData = new ShaderData(fileName);
		s_resourceMap.insert(std::pair<std::string, ShaderData*>(fileName, m_shaderData));
	}
}

Shader::~Shader()
{
	if(m_shaderData && m_shaderData->RemoveReference())
	{
		if(m_fileName.length() > 0)
			s_resourceMap.erase(m_fileName);
			
		delete m_shaderData;
	}
}

//--------------------------------------------------------------------------------
// Member Function Implementation
//--------------------------------------------------------------------------------
void Shader::Bind()
{
	glUseProgram(m_shaderData->GetProgram());
}

void Shader::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	
	for(unsigned int i = 0; i < m_shaderData->GetUniformNames().size(); i++)
	{
		std::string uniformName = m_shaderData->GetUniformNames()[i];
		std::string uniformType = m_shaderData->GetUniformTypes()[i];
		
		if(uniformType == "sampler2D")
		{
			int samplerSlot = renderingEngine->GetSamplerSlot(uniformName);
			material.GetTexture(uniformName)->Bind(samplerSlot);
			SetUniformi(uniformName, samplerSlot);
		}
		else if(uniformName.substr(0, 2) == "T_")
		{
			if(uniformName == "T_MVP")
				SetUniformMatrix4f(uniformName, projectedMatrix);
			else if(uniformName == "T_model")
				SetUniformMatrix4f(uniformName, worldMatrix);
			else
				throw "Invalid Transform Uniform: " + uniformName;
		}
		else if(uniformName.substr(0, 2) == "R_")
		{
			std::string unprefixedName = uniformName.substr(2, uniformName.length());
			
			if(uniformType == "vec3")
				SetUniformVector3f(uniformName, renderingEngine->GetVector3f(unprefixedName));
			else if(uniformType == "float")
				SetUniformf(uniformName, renderingEngine->GetFloat(unprefixedName));
			else if(uniformType == "DirectionalLight")
				SetUniformDirectionalLight(uniformName, *(DirectionalLight*)renderingEngine->GetActiveLight());
			else if(uniformType == "PointLight")
				SetUniformPointLight(uniformName, *(PointLight*)renderingEngine->GetActiveLight());
			else if(uniformType == "SpotLight")
				SetUniformSpotLight(uniformName, *(SpotLight*)renderingEngine->GetActiveLight());
			else
				renderingEngine->UpdateUniformStruct(transform, material, this, uniformName, uniformType);
		}
		else if(uniformName.substr(0, 2) == "C_")
		{
			if(uniformName == "C_eyePos")
				SetUniformVector3f(uniformName, renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
			else
				throw "Invalid Camera Uniform: " + uniformName;
		}
		else
		{
			if(uniformType == "vec3")
				SetUniformVector3f(uniformName, material.GetVector3f(uniformName));
			else if(uniformType == "float")
				SetUniformf(uniformName, material.GetFloat(uniformName));
			else
				throw uniformType + " is not supported by the Material class";
		}
	}
}

void Shader::SetUniformi(const std::string& uniformName, int value)
{
	glUniform1i(m_shaderData->GetUniformMap().at(uniformName), value);
}

void Shader::SetUniformf(const std::string& uniformName, float value)
{
	glUniform1f(m_shaderData->GetUniformMap().at(uniformName), value);
}

void Shader::SetUniformVector3f(const std::string& uniformName, const Vector3f& value)
{
	glUniform3f(m_shaderData->GetUniformMap().at(uniformName), value.GetX(), value.GetY(), value.GetZ());
}

void Shader::SetUniformMatrix4f(const std::string& uniformName, const Matrix4f& value)
{
	glUniformMatrix4fv(m_shaderData->GetUniformMap().at(uniformName), 1, GL_FALSE, &(value[0][0]));
}

void Shader::SetUniformDirectionalLight(const std::string& uniformName, const DirectionalLight& directionalLight)
{
	SetUniformVector3f(uniformName + ".direction", directionalLight.GetTransform().GetTransformedRot().GetForward());
	SetUniformVector3f(uniformName + ".base.color", directionalLight.color);
	SetUniformf(uniformName + ".base.intensity", directionalLight.intensity);
}

void Shader::SetUniformPointLight(const std::string& uniformName, const PointLight& pointLight)
{
	SetUniformVector3f(uniformName + ".base.color", pointLight.color);
	SetUniformf(uniformName + ".base.intensity", pointLight.intensity);
	SetUniformf(uniformName + ".atten.constant", pointLight.atten.constant);
	SetUniformf(uniformName + ".atten.linear", pointLight.atten.linear);
	SetUniformf(uniformName + ".atten.exponent", pointLight.atten.exponent);
	SetUniformVector3f(uniformName + ".position", pointLight.GetTransform().GetTransformedPos());
	SetUniformf(uniformName + ".range", pointLight.range);
}

void Shader::SetUniformSpotLight(const std::string& uniformName, const SpotLight& spotLight)
{
	SetUniformVector3f(uniformName + ".pointLight.base.color", spotLight.color);
	SetUniformf(uniformName + ".pointLight.base.intensity", spotLight.intensity);
	SetUniformf(uniformName + ".pointLight.atten.constant", spotLight.atten.constant);
	SetUniformf(uniformName + ".pointLight.atten.linear", spotLight.atten.linear);
	SetUniformf(uniformName + ".pointLight.atten.exponent", spotLight.atten.exponent);
	SetUniformVector3f(uniformName + ".pointLight.position", spotLight.GetTransform().GetTransformedPos());
	SetUniformf(uniformName + ".pointLight.range", spotLight.range);
	SetUniformVector3f(uniformName + ".direction", spotLight.GetTransform().GetTransformedRot().GetForward());
	SetUniformf(uniformName + ".cutoff", spotLight.cutoff);
}

void ShaderData::AddVertexShader(const std::string& text)
{
	AddProgram(text, GL_VERTEX_SHADER);
}

void ShaderData::AddGeometryShader(const std::string& text)
{
	AddProgram(text, GL_GEOMETRY_SHADER);
}

void ShaderData::AddFragmentShader(const std::string& text)
{
	AddProgram(text, GL_FRAGMENT_SHADER);
}

void ShaderData::AddProgram(const std::string& text, int type)
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
	lengths[0] = text.length();

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

void ShaderData::AddAllAttributes(const std::string& vertexShaderText)
{
	static const std::string ATTRIBUTE_KEY = "attribute";

	int currentAttribLocation = 0;
	size_t attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY);
	while(attributeLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = vertexShaderText.rfind(";", attributeLocation);
		
		if(lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = vertexShaderText.substr(lastLineEnd,attributeLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}
		
		if(!isCommented)
		{
			size_t begin = attributeLocation + ATTRIBUTE_KEY.length();
			size_t end = vertexShaderText.find(";", begin);
			
			std::string attributeLine = vertexShaderText.substr(begin + 1, end-begin - 1);
			
			begin = attributeLine.find(" ");
			std::string attributeName = attributeLine.substr(begin + 1);
			
			glBindAttribLocation(m_program, currentAttribLocation, attributeName.c_str());//SetAttribLocation(attributeName, currentAttribLocation);
			currentAttribLocation++;
		}
		attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY, attributeLocation + ATTRIBUTE_KEY.length());
	}
}

void ShaderData::AddShaderUniforms(const std::string& shaderText)
{
	static const std::string UNIFORM_KEY = "uniform";
		
	std::vector<UniformStruct> structs = FindUniformStructs(shaderText);

	size_t uniformLocation = shaderText.find(UNIFORM_KEY);
	while(uniformLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = shaderText.rfind(";", uniformLocation);
		
		if(lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = shaderText.substr(lastLineEnd,uniformLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}
		
		if(!isCommented)
		{
			size_t begin = uniformLocation + UNIFORM_KEY.length();
			size_t end = shaderText.find(";", begin);
			
			std::string uniformLine = shaderText.substr(begin + 1, end-begin - 1);
			
			begin = uniformLine.find(" ");
			std::string uniformName = uniformLine.substr(begin + 1);
			std::string uniformType = uniformLine.substr(0, begin);
			
			m_uniformNames.push_back(uniformName);
			m_uniformTypes.push_back(uniformType);
			AddUniform(uniformName, uniformType, structs);
		}
		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}

void ShaderData::AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs)
{
	bool addThis = true;

	for(unsigned int i = 0; i < structs.size(); i++)
	{
		if(structs[i].name.compare(uniformType) == 0)
		{
			addThis = false;
			for(unsigned int j = 0; j < structs[i].memberNames.size(); j++)
			{
				AddUniform(uniformName + "." + structs[i].memberNames[j].name, structs[i].memberNames[j].type, structs);
			}
		}
	}

	if(!addThis)
		return;

	unsigned int location = glGetUniformLocation(m_program, uniformName.c_str());

	assert(location != INVALID_VALUE);

	m_uniformMap.insert(std::pair<std::string, unsigned int>(uniformName, location));
}

void ShaderData::CompileShader()
{
    glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");
}

//--------------------------------------------------------------------------------
// Static Function Implementations
//--------------------------------------------------------------------------------
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
			
			if(line.find("#include") == std::string::npos)
				output.append(line + "\n");
			else
			{
				std::string includeFileName = Util::Split(line, ' ')[1];
				includeFileName = includeFileName.substr(1,includeFileName.length() - 2);

				std::string toAppend = LoadShader(includeFileName);
				output.append(toAppend + "\n");
			}
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
};

static std::vector<TypedData> FindUniformStructComponents(const std::string& openingBraceToClosingBrace)
{
	static const char charsToIgnore[] = {' ', '\n', '\t', '{'};
	static const size_t UNSIGNED_NEG_ONE = (size_t)-1;

	std::vector<TypedData> result;
	std::vector<std::string> structLines = Util::Split(openingBraceToClosingBrace, ';');

	for(unsigned int i = 0; i < structLines.size(); i++)
	{
		size_t nameBegin = UNSIGNED_NEG_ONE;
		size_t nameEnd = UNSIGNED_NEG_ONE;

		for(unsigned int j = 0; j < structLines[i].length(); j++)
		{
			bool isIgnoreableCharacter = false;

			for(unsigned int k = 0; k < sizeof(charsToIgnore)/sizeof(char); k++)
			{
				if(structLines[i][j] == charsToIgnore[k])
				{
					isIgnoreableCharacter = true;
					break;
				}
			}

			if(nameBegin == UNSIGNED_NEG_ONE && isIgnoreableCharacter == false)
			{
				nameBegin = j;
			}
			else if(nameBegin != UNSIGNED_NEG_ONE && isIgnoreableCharacter)
			{
				nameEnd = j;
				break;
			}
		}

		if(nameBegin == UNSIGNED_NEG_ONE || nameEnd == UNSIGNED_NEG_ONE)
			continue;

		TypedData newData;
		newData.type = structLines[i].substr(nameBegin, nameEnd - nameBegin);
		newData.name = structLines[i].substr(nameEnd + 1);

		result.push_back(newData);
	}

	return result;
}

static std::string FindUniformStructName(const std::string& structStartToOpeningBrace)
{
	return Util::Split(Util::Split(structStartToOpeningBrace, ' ')[0], '\n')[0];
}

static std::vector<UniformStruct> FindUniformStructs(const std::string& shaderText)
{
	static const std::string STRUCT_KEY = "struct";
	std::vector<UniformStruct> result;

	size_t structLocation = shaderText.find(STRUCT_KEY);
	while(structLocation != std::string::npos)
	{
		structLocation += STRUCT_KEY.length() + 1; //Ignore the struct keyword and space

		size_t braceOpening = shaderText.find("{", structLocation);
		size_t braceClosing = shaderText.find("}", braceOpening);

		UniformStruct newStruct;
		newStruct.name = FindUniformStructName(shaderText.substr(structLocation, braceOpening - structLocation));
		newStruct.memberNames = FindUniformStructComponents(shaderText.substr(braceOpening, braceClosing - braceOpening));

		result.push_back(newStruct);
		structLocation = shaderText.find(STRUCT_KEY, structLocation);
	}

	return result;
}
