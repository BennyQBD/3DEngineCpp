#include "game.h"
#include "input.h"
#include "util.h"
#include <iostream>

#include "window.h"
#include "basicShader.h"
#include "phongShader.h"

void Game::Init()
{
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
	if(m_mesh) delete m_mesh;
	if(m_meshRenderer) delete m_meshRenderer;
}

void Game::Input()
{
	m_root.Input();
}

void Game::Update()
{
	m_root.GetTransform().SetPos(Vector3f(0, -1, 5));
	m_root.GetTransform().SetScale(4.0f);
	m_root.Update();
}
