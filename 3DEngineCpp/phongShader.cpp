#include "phongShader.h"
#include "transform.h"

#include <iostream>
#include "util.h"

Vector3f PhongShader::m_ambientLight = Vector3f(0.1f,0.1f,0.1f);
DirectionalLight PhongShader::m_directionalLight = DirectionalLight(BaseLight(Vector3f(0,0,0), 0),Vector3f(0,0,0));
PointLight* PhongShader::m_pointLights = NULL;
SpotLight* PhongShader::m_spotLights = NULL;
int PhongShader::m_numPointLights = 0;
int PhongShader::m_numSpotLights = 0;

PhongShader::PhongShader()
{
	addVertexShaderFromFile("phongVertex.vs");
	addFragmentShaderFromFile("phongFragment.fs");
	compileShader();

	addUniform("transform");
	addUniform("transformProjected");
	addUniform("baseColor");
	addUniform("ambientLight");
		
	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePos");
		
	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");

	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

		addUniform(pointLightName + ".base.color");
		addUniform(pointLightName + ".base.intensity");
		addUniform(pointLightName + ".atten.constant");
		addUniform(pointLightName + ".atten.linear");
		addUniform(pointLightName + ".atten.exponent");
		addUniform(pointLightName + ".position");
		addUniform(pointLightName + ".range");
	}

	for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		std::string spotLightName = "spotLights[" + std::to_string(i) + "]";

		addUniform(spotLightName + ".pointLight.base.color");
		addUniform(spotLightName + ".pointLight.base.intensity");
		addUniform(spotLightName + ".pointLight.atten.constant");
		addUniform(spotLightName + ".pointLight.atten.linear");
		addUniform(spotLightName + ".pointLight.atten.exponent");
		addUniform(spotLightName + ".pointLight.position");
		addUniform(spotLightName + ".pointLight.range");
		addUniform(spotLightName + ".direction");
		addUniform(spotLightName + ".cutoff");
	}
}

PhongShader::~PhongShader()
{

}

void PhongShader::updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Material& material)
{
	material.texture->bind();
	setUniform("transformProjected", projectedMatrix);
	setUniform("transform", worldMatrix);
	setUniform("baseColor", material.color);
		
	setUniform("ambientLight", m_ambientLight);
	setUniform("directionalLight.direction", m_directionalLight.direction);
	setUniform("directionalLight.base.color", m_directionalLight.base.color);
	setUniformf("directionalLight.base.intensity", m_directionalLight.base.intensity);
		
	for(int i = 0; i < m_numPointLights; i++)
	{
		std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

		setUniform(pointLightName + ".base.color", m_pointLights[i].base.color);
		setUniformf(pointLightName + ".base.intensity", m_pointLights[i].base.intensity);
		setUniformf(pointLightName + ".atten.constant", m_pointLights[i].atten.constant);
		setUniformf(pointLightName + ".atten.linear", m_pointLights[i].atten.linear);
		setUniformf(pointLightName + ".atten.exponent", m_pointLights[i].atten.exponent);
		setUniform(pointLightName + ".position", m_pointLights[i].position);
		setUniformf(pointLightName + ".range", m_pointLights[i].range);
	}

	for(int i = 0; i < m_numSpotLights; i++)
	{
		std::string spotLightName = "spotLights[" + std::to_string(i) + "]";

		setUniform(spotLightName + ".pointLight.base.color", m_spotLights[i].pointLight.base.color);
		setUniformf(spotLightName + ".pointLight.base.intensity", m_spotLights[i].pointLight.base.intensity);
		setUniformf(spotLightName + ".pointLight.atten.constant", m_spotLights[i].pointLight.atten.constant);
		setUniformf(spotLightName + ".pointLight.atten.linear", m_spotLights[i].pointLight.atten.linear);
		setUniformf(spotLightName + ".pointLight.atten.exponent", m_spotLights[i].pointLight.atten.exponent);
		setUniform(spotLightName + ".pointLight.position", m_spotLights[i].pointLight.position);
		setUniformf(spotLightName + ".pointLight.range", m_spotLights[i].pointLight.range);
		setUniform(spotLightName + ".direction", m_spotLights[i].direction);
		setUniformf(spotLightName + ".cutoff", m_spotLights[i].cutoff);
	}

	setUniformf("specularIntensity", material.specularIntensity);
	setUniformf("specularPower", material.specularPower);
		
	setUniform("eyePos", Transform::getCamera().getPos());
}

Vector3f& PhongShader::getAmbientLight()
{
	return m_ambientLight;
}

DirectionalLight& PhongShader::getDirectionalLight()
{
	return m_directionalLight;
}

void PhongShader::setAmbientLight(const Vector3f& ambientLight)
{
	PhongShader::m_ambientLight = ambientLight;
}

void PhongShader::setDirectionalLight(const DirectionalLight& directionalLight)
{
	PhongShader::m_directionalLight = directionalLight;
}

void PhongShader::setPointLights(PointLight* pointLights, int arraySize)
{
	if(arraySize > MAX_POINT_LIGHTS)
	{
		std::cerr << "Error: Too many point lights" << std::endl;
	}
	else
	{
		PhongShader::m_numPointLights = arraySize;
		PhongShader::m_pointLights = pointLights;
	}
}

void PhongShader::setSpotLights(SpotLight* spotLights, int arraySize)
{
	if(arraySize > MAX_SPOT_LIGHTS)
	{
		std::cerr << "Error: Too many spot lights" << std::endl;
	}
	else
	{
		PhongShader::m_numSpotLights = arraySize;
		PhongShader::m_spotLights = spotLights;
	}
}
