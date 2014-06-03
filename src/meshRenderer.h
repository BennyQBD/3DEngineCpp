#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#include "gameComponent.h"
#include "mesh.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(const Mesh& mesh, const Material& material) :
		m_mesh(mesh),
		m_material(material) {}

	virtual void Render(const Shader& shader, const RenderingEngine& renderingEngine) const
	{
		shader.Bind();
		shader.UpdateUniforms(GetTransform(), m_material, renderingEngine);
		m_mesh.Draw();
	}
protected:
private:
	Mesh m_mesh;
	Material m_material;
};

#endif // MESHRENDERER_H_INCLUDED
