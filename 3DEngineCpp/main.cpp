#include "3DEngine.h"

class TestGame : public Game
{
public:
	TestGame() {}
	
	virtual void Init();
protected:
private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}
};

void TestGame::Init()
{
	GameObject* planeObject = new GameObject();
	GameObject* pointLightObject = new GameObject();

	planeObject->AddComponent(new MeshRenderer(new Mesh("./res/models/plane3.obj"), new Material(new Texture("test.png"), Vector3f(1,1,1), 1, 8)));
	planeObject->GetTransform().SetPos(Vector3f(0, -1, 5));
	planeObject->GetTransform().SetScale(4.0f);
	
	pointLightObject->AddComponent(new PointLight(Vector3f(0,1,0),0.4f,Attenuation(0,0,1)));
	pointLightObject->GetTransform().SetPos(Vector3f(7,0,7));
	
	AddToScene(planeObject);
	AddToScene(pointLightObject);
	AddToScene((new GameObject())->AddComponent(new DirectionalLight(Vector3f(1,1,1), 0.8f, Vector3f(1,1,1))));
	AddToScene((new GameObject())->AddComponent(new SpotLight(Vector3f(0,1,1),0.4f,Attenuation(0,0,0.1f),Vector3f(1,0,0),0.7f)));
}

int main()
{
	TestGame game;
	CoreEngine engine(800, 600, 60, &game);
	engine.CreateWindow("3D Game Engine!");
	engine.Start();
	
	return 0;
}
