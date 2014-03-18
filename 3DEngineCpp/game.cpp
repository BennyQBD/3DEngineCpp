#include "game.h"
#include <iostream>

void Game::Input(float delta)
{
	m_root.Input(delta);
}

void Game::Update(float delta)
{
	m_root.Update(delta);
}
