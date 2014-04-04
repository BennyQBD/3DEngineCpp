#include "shader.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <cstdlib>

#include "util.h"

static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);

Shader::Shader(const std::string& fileName)
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

void Shader::CompileShader()
{
    glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");
}

void Shader::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{

}

void Shader::SetUniformi(const std::string& name, int value)
{
	glUniform1i(m_uniforms.at(name).Location, value);
}

void Shader::SetUniformf(const std::string& name, float value)
{
	glUniform1f(m_uniforms.at(name).Location, value);
}

void Shader::SetUniform(const std::string& name, const Vector3f& value)
{
	glUniform3f(m_uniforms.at(name).Location, value.GetX(), value.GetY(), value.GetZ());
}

void Shader::SetUniform(const std::string& name, const Matrix4f& value)
{
	glUniformMatrix4fv(m_uniforms.at(name).Location, 1, GL_FALSE, &(value[0][0]));
}

void Shader::SetAttribLocation(const std::string& attributeName, int location)
{
	glBindAttribLocation(m_program, location, attributeName.c_str());
}

void Shader::AddAllAttributes(const std::string& vertexShaderText)
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
			
			SetAttribLocation(attributeName, currentAttribLocation);
			currentAttribLocation++;
		}
		attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY, attributeLocation + ATTRIBUTE_KEY.length());
	}
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

void Shader::AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs)
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

	m_uniforms.insert(std::pair<std::string, UniformData>(uniformName, UniformData(location, uniformType)));
	//result.push_back(UniformData(location, uniformType, uniformName));
}

void Shader::AddShaderUniforms(const std::string& shaderText)
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
			
			AddUniform(uniformName, uniformType, structs);
		}
		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}
