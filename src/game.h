#ifndef MYGAME_H
#define MYGAME_H

#include "gameObject.h"
#include "coreEngine.h"

class Game
{
public:
	Game() {}
	virtual ~Game() {}

	virtual void Init() {}
	void Input(float delta);
	void Update(float delta);
	void Render(RenderingEngine* renderingEngine);
	
	inline GameObject& GetRoot() { return m_root; }
	
	inline void SetEngine(CoreEngine* engine) { m_root.SetEngine(engine); }
protected:
	void AddToScene(GameObject* child) { m_root.AddChild(child); }
private:
	Game(Game& game) {}
	void operator=(Game& game) {}
	
	GameObject m_root;
};

#endif
