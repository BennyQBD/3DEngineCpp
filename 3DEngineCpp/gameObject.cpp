#include "gameObject.h"
#include "gameComponent.h"

GameObject::~GameObject()
{
	for(unsigned int i = 0; i < m_components.size(); i++)
		if(m_components[i])
			delete m_components[i];
	
	for(unsigned int i = 0; i < m_children.size(); i++)
		if(m_children[i])
			delete m_children[i];
}

GameObject* GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child); 
	child->GetTransform().SetParent(&m_transform);
	return this;
}

GameObject* GameObject::AddComponent(GameComponent* component)
{
	m_components.push_back(component);
	component->SetParent(this);
	return this;
}

void GameObject::Input(float delta)
{
	m_transform.Update();

	for(unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->Input(delta);

	for(unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->Input(delta);
}

void GameObject::Update(float delta)
{
	for(unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->Update(delta);

	for(unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->Update(delta);
}

void GameObject::Render(Shader* shader, RenderingEngine* renderingEngine)
{
	for(unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->Render(shader, renderingEngine);

	for(unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->Render(shader, renderingEngine);
}

void GameObject::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
	for(unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->AddToRenderingEngine(renderingEngine);

	for(unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->AddToRenderingEngine(renderingEngine);
}
