#include "phongShader.h"
#include "transform.h"

#include <iostream>
#include <sstream>
#include "util.h"

Vector3f PhongShader::s_ambientLight = Vector3f(0.1f,0.1f,0.1f);
DirectionalLight PhongShader::s_directionalLight = DirectionalLight(BaseLight(Vector3f(0,0,0), 0),Vector3f(0,0,0));
PointLight* PhongShader::s_pointLights = NULL;
SpotLight* PhongShader::s_spotLights = NULL;
int PhongShader::s_numPointLights = 0;
int PhongShader::s_numSpotLights = 0;

PhongShader::PhongShader()
{
	AddVertexShaderFromFile("phongVertex.vs");
	AddFragmentShaderFromFile("phongFragment.fs");
	
	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);
	
	CompileShader();

	AddUniform("transform");
	AddUniform("transformProjected");
	AddUniform("baseColor");
	AddUniform("ambientLight");
		
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
		
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");
	AddUniform("directionalLight.direction");

	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		std::ostringstream pointLightNameBuilder;
		pointLightNameBuilder << "pointLights[" << i << "]";
		std::string pointLightName = pointLightNameBuilder.str();
		//std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

		AddUniform(pointLightName + ".base.color");
		AddUniform(pointLightName + ".base.intensity");
		AddUniform(pointLightName + ".atten.constant");
		AddUniform(pointLightName + ".atten.linear");
		AddUniform(pointLightName + ".atten.exponent");
		AddUniform(pointLightName + ".position");
	}

	for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		std::ostringstream spotLightNameBuilder;
		spotLightNameBuilder << "spotLights[" << i << "]";
		std::string spotLightName = spotLightNameBuilder.str();
		//std::string spotLightName = "spotLights[" + std::to_string(i) + "]";

		AddUniform(spotLightName + ".pointLight.base.color");
		AddUniform(spotLightName + ".pointLight.base.intensity");
		AddUniform(spotLightName + ".pointLight.atten.constant");
		AddUniform(spotLightName + ".pointLight.atten.linear");
		AddUniform(spotLightName + ".pointLight.atten.exponent");
		AddUniform(spotLightName + ".pointLight.position");
		AddUniform(spotLightName + ".direction");
		AddUniform(spotLightName + ".cutoff");
	}
}

void PhongShader::UpdateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, const Material& material)
{
//	Matrix4f normalMat3 = Matrix3f(worldMatrix);
//	
//	normalMat3 = normalMat3.Transpose();
//	normalMat3 = normalMat3.Inverse();
//	
//	Matrix4f normalMatrix = Matrix4f().InitIdentity();
//	normalMatrix = Matrix4f(normalMat3);
	//Matrix4f normalMatrix = Matrix4f(Matrix3f(worldMatrix).Transpose().Inverse());
	//Matrix4f normalMatrix = Matrix4f(Matrix3f(Matrix3f(worldMatrix).Inverse()).Transpose());
	
//	Matrix3f worldRot3(worldMatrix);
//	worldRot3 = worldRot3.Transpose();
//	Matrix4f worldRot(worldRot3);
//	
//	Matrix4f worldPos = Matrix4f().InitTranslationTransform(Vector3f(-worldMatrix[3][0], -worldMatrix[3][1], -worldMatrix[3][2]));
//	
//	Matrix4f normalMatrix = worldRot * worldPos;

//	Matrix4f normalMatrix = worldMatrix;
	
	//normalMatrix = Matrix4f(normalMatrix.Transpose()).Inverse();
	//normalMatrix = normalMatrix.Inverse().Transpose();
	//normalMatrix = Matrix4f(normalMatrix.Transpose()).Inverse();

	material.texture->Bind();
	SetUniform("transformProjected", projectedMatrix);
	SetUniform("transform", worldMatrix);
	SetUniform("baseColor", material.color);
		
	SetUniform("ambientLight", s_ambientLight);
	SetUniform("directionalLight.direction", s_directionalLight.direction);
	SetUniform("directionalLight.base.color", s_directionalLight.base.color);
	SetUniformf("directionalLight.base.intensity", s_directionalLight.base.intensity);
		
	for(int i = 0; i < s_numPointLights; i++)
	{
		std::ostringstream pointLightNameBuilder;
		pointLightNameBuilder << "pointLights[" << i << "]";
		std::string pointLightName = pointLightNameBuilder.str();
		//std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

		SetUniform(pointLightName + ".base.color", s_pointLights[i].base.color);
		SetUniformf(pointLightName + ".base.intensity", s_pointLights[i].base.intensity);
		SetUniformf(pointLightName + ".atten.constant", s_pointLights[i].atten.constant);
		SetUniformf(pointLightName + ".atten.linear", s_pointLights[i].atten.linear);
		SetUniformf(pointLightName + ".atten.exponent", s_pointLights[i].atten.exponent);
		SetUniform(pointLightName + ".position", s_pointLights[i].position);
	}

	for(int i = 0; i < s_numSpotLights; i++)
	{
		std::ostringstream spotLightNameBuilder;
		spotLightNameBuilder << "spotLights[" << i << "]";
		std::string spotLightName = spotLightNameBuilder.str();
		//std::string spotLightName = "spotLights[" + std::to_string(i) + "]";

		SetUniform(spotLightName + ".pointLight.base.color", s_spotLights[i].pointLight.base.color);
		SetUniformf(spotLightName + ".pointLight.base.intensity", s_spotLights[i].pointLight.base.intensity);
		SetUniformf(spotLightName + ".pointLight.atten.constant", s_spotLights[i].pointLight.atten.constant);
		SetUniformf(spotLightName + ".pointLight.atten.linear", s_spotLights[i].pointLight.atten.linear);
		SetUniformf(spotLightName + ".pointLight.atten.exponent", s_spotLights[i].pointLight.atten.exponent);
		SetUniform(spotLightName + ".pointLight.position", s_spotLights[i].pointLight.position);
		SetUniform(spotLightName + ".direction", s_spotLights[i].direction);
		SetUniformf(spotLightName + ".cutoff", s_spotLights[i].cutoff);
	}

	SetUniformf("specularIntensity", material.specularIntensity);
	SetUniformf("specularPower", material.specularPower);
		
	SetUniform("eyePos", Transform::GetCamera().GetPos());
}

void PhongShader::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	PhongShader::s_directionalLight = directionalLight;
}

void PhongShader::SetPointLights(PointLight* pointLights, int arraySize)
{
	if(arraySize > MAX_POINT_LIGHTS)
	{
		std::cerr << "Error: Too many point lights" << std::endl;
	}
	else
	{
		PhongShader::s_numPointLights = arraySize;
		PhongShader::s_pointLights = pointLights;
	}
}

void PhongShader::SetSpotLights(SpotLight* spotLights, int arraySize)
{
	if(arraySize > MAX_SPOT_LIGHTS)
	{
		std::cerr << "Error: Too many spot lights" << std::endl;
	}
	else
	{
		PhongShader::s_numSpotLights = arraySize;
		PhongShader::s_spotLights = spotLights;
	}
}
