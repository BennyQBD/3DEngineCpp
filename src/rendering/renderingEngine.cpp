/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "renderingEngine.h"
#include "window.h"
#include "mesh.h"
#include "shader.h"

#include "../core/entity.h"

#include <GL/glew.h>
#include <cassert>

const Matrix4f RenderingEngine::BIAS_MATRIX = Matrix4f().InitScale(Vector3f(0.5, 0.5, 0.5)) * Matrix4f().InitTranslation(Vector3f(1.0, 1.0, 1.0));
//Should construct a Matrix like this:
//     x   y   z   w
//x [ 0.5 0.0 0.0 0.5 ]
//y [ 0.0 0.5 0.0 0.5 ]
//z [ 0.0 0.0 0.5 0.5 ]
//w [ 0.0 0.0 0.0 1.0 ]
//
//Note the 'w' column in this representation should be
//the translation column!
//
//This matrix will convert 3D coordinates from the range (-1, 1) to the range (0, 1).

RenderingEngine::RenderingEngine(const Window& window) :
	m_plane(Mesh("plane.obj")),
	m_window(&window),
	m_tempTarget(window.GetWidth(), window.GetHeight(), 0, GL_TEXTURE_2D, GL_NEAREST, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0),
	m_planeMaterial("renderingEngine_filterPlane", m_tempTarget, 1, 8),
	m_defaultShader("forward-ambient"),
	m_shadowMapShader("shadowMapGenerator"),
	m_nullFilter("filter-null"),
	m_gausBlurFilter("filter-gausBlur7x1"),
	m_fxaaFilter("filter-fxaa"),
	m_altCameraTransform(Vector3f(0,0,0), Quaternion(Vector3f(0,1,0),ToRadians(180.0f))),
	m_altCamera(Matrix4f().InitIdentity(), &m_altCameraTransform)
{
	SetSamplerSlot("diffuse",   0);
	SetSamplerSlot("normalMap", 1);
	SetSamplerSlot("dispMap",   2);
	SetSamplerSlot("shadowMap", 3);
	
	SetSamplerSlot("filterTexture", 0);
	
	SetVector3f("ambient", Vector3f(0.2f, 0.2f, 0.2f));
	
	SetFloat("fxaaSpanMax", 8.0f);
	SetFloat("fxaaReduceMin", 1.0f/128.0f);
	SetFloat("fxaaReduceMul", 1.0f/8.0f);
	SetFloat("fxaaAspectDistortion", 150.0f);

	SetTexture("displayTexture", Texture(m_window->GetWidth(), m_window->GetHeight(), 0, GL_TEXTURE_2D, GL_LINEAR, GL_RGBA, GL_RGBA, true, GL_COLOR_ATTACHMENT0));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_FRAMEBUFFER_SRGB);
	                  
	//m_planeMaterial("renderingEngine_filterPlane", m_tempTarget, 1, 8);
	m_planeTransform.SetScale(1.0f);
	m_planeTransform.Rotate(Quaternion(Vector3f(1,0,0), ToRadians(90.0f)));
	m_planeTransform.Rotate(Quaternion(Vector3f(0,0,1), ToRadians(180.0f)));
	
	for(int i = 0; i < NUM_SHADOW_MAPS; i++)
	{
		int shadowMapSize = 1 << (i + 1);
		m_shadowMaps[i] = Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
		m_shadowMapTempTargets[i] = Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
	}
	
	m_lightMatrix = Matrix4f().InitScale(Vector3f(0,0,0));	
}

void RenderingEngine::BlurShadowMap(int shadowMapIndex, float blurAmount)
{
	SetVector3f("blurScale", Vector3f(blurAmount/(m_shadowMaps[shadowMapIndex].GetWidth()), 0.0f, 0.0f));
	ApplyFilter(m_gausBlurFilter, m_shadowMaps[shadowMapIndex], &m_shadowMapTempTargets[shadowMapIndex]);
	
	SetVector3f("blurScale", Vector3f(0.0f, blurAmount/(m_shadowMaps[shadowMapIndex].GetHeight()), 0.0f));
	ApplyFilter(m_gausBlurFilter, m_shadowMapTempTargets[shadowMapIndex], &m_shadowMaps[shadowMapIndex]); 

//	SetVector3f("inverseFilterTextureSize", Vector3f(blurAmount/m_shadowMaps[shadowMapIndex].GetWidth(), blurAmount/m_shadowMaps[shadowMapIndex].GetHeight(), 0.0f));
//	ApplyFilter(m_fxaaFilter, m_shadowMaps[shadowMapIndex], &m_shadowMapTempTargets[shadowMapIndex]);
//	
//	ApplyFilter(m_nullFilter, m_shadowMapTempTargets[shadowMapIndex], &m_shadowMaps[shadowMapIndex]);
}

void RenderingEngine::ApplyFilter(const Shader& filter, const Texture& source, const Texture* dest)
{
	assert(&source != dest);
	if(dest == 0)
	{
		m_window->BindAsRenderTarget();
	}
	else
	{
		dest->BindAsRenderTarget();
	}
	
	SetTexture("filterTexture", source);
	
	m_altCamera.SetProjection(Matrix4f().InitIdentity());
	m_altCamera.GetTransform()->SetPos(Vector3f(0,0,0));
	m_altCamera.GetTransform()->SetRot(Quaternion(Vector3f(0,1,0),ToRadians(180.0f)));
	
//	const Camera* temp = m_mainCamera;
//	m_mainCamera = m_altCamera;

	glClear(GL_DEPTH_BUFFER_BIT);
	filter.Bind();
	filter.UpdateUniforms(m_planeTransform, m_planeMaterial, *this, m_altCamera);
	m_plane.Draw();
	
//	m_mainCamera = temp;
	SetTexture("filterTexture", 0);
}

void RenderingEngine::Render(const Entity& object)
{
	m_renderProfileTimer.StartInvocation();
	GetTexture("displayTexture").BindAsRenderTarget();
	//m_window->BindAsRenderTarget();
	//m_tempTarget->BindAsRenderTarget();

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object.RenderAll(m_defaultShader, *this, *m_mainCamera);
	
	for(unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		ShadowInfo shadowInfo = m_activeLight->GetShadowInfo();
		
		int shadowMapIndex = 0;
		if(shadowInfo.GetShadowMapSizeAsPowerOf2() != 0)
			shadowMapIndex = shadowInfo.GetShadowMapSizeAsPowerOf2() - 1;
		
		assert(shadowMapIndex >= 0 && shadowMapIndex < NUM_SHADOW_MAPS);
		
		SetTexture("shadowMap", m_shadowMaps[shadowMapIndex]);
		m_shadowMaps[shadowMapIndex].BindAsRenderTarget();
		glClearColor(1.0f,1.0f,0.0f,0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		if(shadowInfo.GetShadowMapSizeAsPowerOf2() != 0)
		{
			m_altCamera.SetProjection(shadowInfo.GetProjection());
			ShadowCameraTransform shadowCameraTransform = m_activeLight->CalcShadowCameraTransform(m_mainCamera->GetTransform().GetTransformedPos(), 
				m_mainCamera->GetTransform().GetTransformedRot());
			m_altCamera.GetTransform()->SetPos(shadowCameraTransform.GetPos());
			m_altCamera.GetTransform()->SetRot(shadowCameraTransform.GetRot());
			
			m_lightMatrix = BIAS_MATRIX * m_altCamera.GetViewProjection();
			
			SetFloat("shadowVarianceMin", shadowInfo.GetMinVariance());
			SetFloat("shadowLightBleedingReduction", shadowInfo.GetLightBleedReductionAmount());
			bool flipFaces = shadowInfo.GetFlipFaces();
			
//			const Camera* temp = m_mainCamera;
//			m_mainCamera = m_altCamera;
			
			if(flipFaces)
			{
				glCullFace(GL_FRONT);
			}
			
			glEnable(GL_DEPTH_CLAMP);
			object.RenderAll(m_shadowMapShader, *this, m_altCamera);
			glDisable(GL_DEPTH_CLAMP);
			
			if(flipFaces) 
			{
				glCullFace(GL_BACK);
			}
			
//			m_mainCamera = temp;
			
			float shadowSoftness = shadowInfo.GetShadowSoftness();
			if(shadowSoftness != 0)
			{
				BlurShadowMap(shadowMapIndex, shadowSoftness);
			}
		}
		else
		{
			m_lightMatrix = Matrix4f().InitScale(Vector3f(0,0,0));
			SetFloat("shadowVarianceMin", 0.00002f);
			SetFloat("shadowLightBleedingReduction", 0.0f);
		}
	
		GetTexture("displayTexture").BindAsRenderTarget();
		//m_window->BindAsRenderTarget();
		
//		glEnable(GL_SCISSOR_TEST);
//		TODO: Make use of scissor test to limit light area
//		glScissor(0, 0, 100, 100);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		object.RenderAll(m_activeLight->GetShader(), *this, *m_mainCamera);
		
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
		
//		glDisable(GL_SCISSOR_TEST);
	}
	
	float displayTextureAspect = (float)GetTexture("displayTexture").GetWidth()/(float)GetTexture("displayTexture").GetHeight();
	float displayTextureHeightAdditive = displayTextureAspect * GetFloat("fxaaAspectDistortion");
	SetVector3f("inverseFilterTextureSize", Vector3f(1.0f/(float)GetTexture("displayTexture").GetWidth(), 
	                                                 1.0f/((float)GetTexture("displayTexture").GetHeight() + displayTextureHeightAdditive), 0.0f));
	m_renderProfileTimer.StopInvocation();
	
	m_windowSyncProfileTimer.StartInvocation();
	ApplyFilter(m_fxaaFilter, GetTexture("displayTexture"), 0);
	m_windowSyncProfileTimer.StopInvocation();
}
