#ifndef MYGAME_H
#define MYGAME_H

#include "gameObject.h"

class Game
{
public:
	Game() {}
	virtual ~Game() {}

	virtual void Init() {}
	void Input(float delta);
	void Update(float delta);
	
	inline GameObject& GetRoot() { return m_root; }
protected:
	void AddToScene(GameObject* child) { m_root.AddChild(child); }
private:
	Game(Game& game) {}
	void operator=(Game& game) {}
	
	GameObject m_root;
};

#endif
