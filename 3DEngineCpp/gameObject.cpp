#include "gameObject.h"

void GameObject::AddChild(GameObject& child)
{
	m_children.push_back(&child);
}

void GameObject::AddComponent(GameComponent* component)
{
	m_components.push_back(component);
}

void GameObject::Input(float delta)
{
	for(unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->Input(m_transform, delta);

	for(unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->Input(delta);
}

void GameObject::Update(float delta)
{
	for(unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->Update(m_transform, delta);

	for(unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->Update(delta);
}

void GameObject::Render(Shader* shader, RenderingEngine* renderingEngine)
{
	for(unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->Render(m_transform, shader, renderingEngine);

	for(unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->Render(shader, renderingEngine);
}
