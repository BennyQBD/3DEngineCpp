#ifndef MYGAME_H
#define MYGAME_H

#include "mesh.h"
#include "shader.h"
#include "basicShader.h"
#include "transform.h"
#include "camera.h"
#include "lighting.h"
#include "gameObject.h"
#include "meshRenderer.h"

class Game
{
public:
	Game() {}
	virtual ~Game();

	void Init();
	void Input();
	void Update();
	void Render();
protected:
private:
	Game(Game& game) {}
	void operator=(Game& game) {}
	
	GameObject m_root;

	Mesh* m_mesh;
//	Shader* m_shader;
//	Vector3f m_color;
//	Transform m_transform;
	Camera m_camera;
	Material m_material;
	Texture* m_texture;
	MeshRenderer* m_meshRenderer;
//	PointLight* m_pLights;
//	SpotLight* m_sLights;
};

#endif
