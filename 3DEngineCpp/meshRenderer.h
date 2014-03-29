#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#include "gameComponent.h"
#include "mesh.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh* mesh, Material* material)
	{
		m_mesh = mesh;
		m_material = material;
	}
	
	virtual ~MeshRenderer()
	{
		if(m_mesh) delete m_mesh;
		if(m_material) delete m_material;
	}

	virtual void Render(Shader* shader, RenderingEngine* renderingEngine) 
	{
		shader->Bind();
		shader->UpdateUniforms(GetTransform(), *m_material, renderingEngine);
		m_mesh->Draw();
	}
protected:
private:
	Mesh* m_mesh;
	Material* m_material;
};

#endif // MESHRENDERER_H_INCLUDED
