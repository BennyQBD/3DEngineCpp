#include "game.h"
#include "input.h"
#include "util.h"
#include <iostream>

#include "window.h"
#include "basicShader.h"
#include "phongShader.h"

void Game::Init()
{
	//Vertex data[3] = {Vertex(Vector3f(-1,-1,0)),
	//				 Vertex(Vector3f(0,1,0)),
	//				 Vertex(Vector3f(1,-1,0))};

	//mesh.addVertices(data, ARRAY_SIZE(data));

	//Vertex data[] = {Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
	//				 Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
	//				 Vertex(Vector3f(1.0f, -1.0f, 0.5773f), Vector2f(1.0f, 0.0f)),
	//				 Vertex(Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.5f, 1.0f))};

	//int indices[] = { 0, 3, 1,
	//				  1, 3, 2,
	//				  2, 3, 0,
	//				  1, 2, 0};

//	float fieldDepth = 10.0f;
//	float fieldWidth = 10.0f;
//		
//	Vertex data[] = { 	Vertex( Vector3f(-fieldWidth, 0.0f, -fieldDepth), Vector2f(0.0f, 0.0f)),
//						Vertex(Vector3f(-fieldWidth, 0.0f, fieldDepth * 3), Vector2f(0.0f, 1.0f)),
//						Vertex(Vector3f(fieldWidth * 3, 0.0f, -fieldDepth), Vector2f(1.0f, 0.0f)),
//						Vertex(Vector3f(fieldWidth * 3, 0.0f, fieldDepth * 3),Vector2f(1.0f, 1.0f))};
//		
//	int indices[] = { 0, 1, 2,
//					  2, 1, 3};
//
//	//m_mesh.AddVertices(data, ARRAY_SIZE_IN_ELEMENTS(data), indices, ARRAY_SIZE_IN_ELEMENTS(indices));
//	m_mesh = new Mesh("./res/models/plane3.obj");
//	//m_mesh = new Mesh("./res/models/levelTest.obj");
//	//m_mesh = new Mesh();
//	//m_mesh->AddVertices(data, ARRAY_SIZE_IN_ELEMENTS(data), indices, ARRAY_SIZE_IN_ELEMENTS(indices));
//	m_color.Set(1,1,1);
//
//	m_texture = new Texture("test.png");
//	//m_texture = new Texture("bricks.jpg");
//	m_material = Material(m_texture, m_color, 1, 8);
//
//	m_shader = PhongShader::GetInstance();
//	//PhongShader::SetAmbientLight(Vector3f(0.0f,0.0f,0.0f));
//	PhongShader::SetDirectionalLight(DirectionalLight(BaseLight(Vector3f(1,1,1),0.1f),Vector3f(1,1,1)));
//
//	m_pLights = new PointLight[2];
//	m_pLights[0] = PointLight(BaseLight(Vector3f(1,0.5f,0), 0.8f), Attenuation(0,0,1), Vector3f(-2,0,5), 10);
//	m_pLights[1] = PointLight(BaseLight(Vector3f(0,0.5f,1), 0.8f), Attenuation(0,0,1), Vector3f(2,0,7), 10);
//
//	m_sLights = new SpotLight[1];
//	m_sLights[0] = SpotLight(PointLight(BaseLight(Vector3f(0,1,1), 0.8f), Attenuation(0,0,0.1f), Vector3f(-2,0,5), 30),Vector3f(1,1,1).Normalized(),0.8f);
//
//	PhongShader::SetPointLights(m_pLights, 2);
//	PhongShader::SetSpotLights(m_sLights, 1);
//
	m_camera = Camera();
//
	Transform::SetProjection(70.0f, (float)Window::GetWidth(), (float)Window::GetHeight(), 0.1f, 1000.0f);
	Transform::SetCamera(m_camera);

	m_root = GameObject();
	m_mesh = new Mesh("./res/models/plane3.obj");
	m_texture = new Texture("test.png");
	m_material = Material(m_texture, Vector3f(1,1,1), 1, 8);
	
	m_meshRenderer = new MeshRenderer(*m_mesh, m_material);
	m_root.AddComponent(m_meshRenderer);
}

Game::~Game()
{
	if(m_texture) delete m_texture;
//	if(m_pLights) delete[] m_pLights;
//	if(m_sLights) delete[] m_sLights;
	if(m_mesh) delete m_mesh;
	if(m_meshRenderer) delete m_meshRenderer;
}

void Game::Input()
{
	m_camera.Input();
//	if(Input::GetKeyDown(KEY::KEY_1))
//		Window::SetFullScreen(false);
//	if(Input::GetKeyDown(KEY::KEY_2))
//		Window::SetFullScreen(true);
	m_root.Input();
}

//double temp = 0.0f;
//#include "time.h"
//#include <math.h>

void Game::Update()
{
//	temp += Time::GetDelta();
//
//	m_transform.SetPos(Vector3f(0,-1.0f,5));
//	m_transform.SetScale(4.0f);
//
//	m_pLights[0].position = (Vector3f(3,0,8.0f * (float)(sin(temp) + 1.0/2.0) + 10));
//	m_pLights[1].position = (Vector3f(7,0,8.0f * (float)(cos(temp) + 1.0/2.0) + 10));
//	m_sLights[0].pointLight.position = m_camera.GetPos();
//	m_sLights[0].direction = m_camera.GetForward();
	m_root.GetTransform().SetPos(Vector3f(0, -1, 5));
	m_root.GetTransform().SetScale(4.0f);
	m_root.Update();
}

void Game::Render()
{
//	m_shader->Bind();
//	m_shader->UpdateUniforms(m_transform.GetTransformation(), m_transform.GetProjectedTransformation(), m_material);
//
//	m_mesh->Draw();
	m_root.Render();
}
