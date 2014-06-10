#include "game.h"
#include "renderingEngine.h"
#include <iostream>

void Game::ProcessInput(const Input& input, float delta)
{
	m_root.ProcessInputAll(input, delta);
}

void Game::Update(float delta)
{
	m_root.UpdateAll(delta);
}

void Game::Render(RenderingEngine* renderingEngine, const Camera& camera)
{
	renderingEngine->Render(m_root, camera);
}
