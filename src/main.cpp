#include "3DEngine.h"
#include "freeLook.h"
#include "freeMove.h"

class TestGame : public Game
{
public:
	TestGame() {}
	
	virtual void Init(const Window& window);
protected:
private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}
};

void TestGame::Init(const Window& window)
{
	Material bricks("bricks", Texture("bricks.jpg"), 0.5f, 4, Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);
	Material bricks2("bricks2", Texture("bricks2.jpg"), 1, 8, Texture("bricks2_normal.png"), Texture("bricks2_disp.jpg"), 0.04f, -1.0f);

	IndexedModel square;
	{
		square.AddVertex(1.0f, -1.0f, 0.0f);  square.AddTexCoord(Vector2f(1.0f, 1.0f));
		square.AddVertex(1.0f, 1.0f, 0.0f);   square.AddTexCoord(Vector2f(1.0f, 0.0f));
		square.AddVertex(-1.0f, -1.0f, 0.0f); square.AddTexCoord(Vector2f(0.0f, 1.0f));
		square.AddVertex(-1.0f, 1.0f, 0.0f);  square.AddTexCoord(Vector2f(0.0f, 0.0f));
		square.AddFace(0, 1, 2); square.AddFace(2, 1, 3);
	}
	Mesh customMesh("square", square.Finalize());
	
	AddToScene((new GameObject(Vector3f(0, -1, 5), Quaternion(), 32.0f))
		->AddComponent(new MeshRenderer(Mesh("terrain02.obj"), Material("bricks"))));
		
	AddToScene((new GameObject(Vector3f(7,0,7)))
		->AddComponent(new PointLight(Vector3f(0,1,0), 0.4f, Attenuation(0,0,1))));
	
	AddToScene((new GameObject(Vector3f(20,-11.0f,5), Quaternion(Vector3f(1,0,0), ToRadians(-60.0f)) * Quaternion(Vector3f(0,1,0), ToRadians(90.0f))))
		->AddComponent(new SpotLight(Vector3f(0,1,1), 0.4f, Attenuation(0,0,0.02f), ToRadians(91.1f), 7, 1.0f, 0.5f)));
	
	AddToScene((new GameObject(Vector3f(), Quaternion(Vector3f(1,0,0), ToRadians(-45))))
		->AddComponent(new DirectionalLight(Vector3f(1,1,1), 0.4f, 10, 80.0f, 1.0f)));
	
	AddToScene((new GameObject(Vector3f(0, 2, 0), Quaternion(Vector3f(0,1,0), 0.4f), 1.0f))
		->AddComponent(new MeshRenderer(Mesh("plane3.obj"), Material("bricks2")))
		->AddChild((new GameObject(Vector3f(0, 0, 25)))
			->AddComponent(new MeshRenderer(Mesh("plane3.obj"), Material("bricks2")))
			->AddChild((new GameObject())
				->AddComponent(new CameraComponent(Matrix4f().InitPerspective(ToRadians(70.0f), window.GetAspect(), 0.1f, 1000.0f)))
				->AddComponent(new FreeLook(window.GetCenter()))
				->AddComponent(new FreeMove()))));
	
	AddToScene((new GameObject(Vector3f(24,-12,5), Quaternion(Vector3f(0,1,0), ToRadians(30.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
		
	AddToScene((new GameObject(Vector3f(0,0,7), Quaternion(), 1.0f))
		->AddComponent(new MeshRenderer(Mesh("square"), Material("bricks2"))));
}

int main()
{
	TestGame game;
	CoreEngine engine(800, 600, 60, &game);
	engine.CreateWindow("3D Game Engine");
	engine.Start();

//	Window window(800, 600, "My Window");
//	RenderingEngine engine(window);
//	
//	Material bricks2("bricks2", Texture("bricks2.jpg"), 1, 8, Texture("bricks2_normal.png"), Texture("bricks2_disp.jpg"), 0.04f, -1.0f);
//	GameObject root;
//	Transform cameraTransform;
//	Camera camera(Matrix4f().InitPerspective(ToRadians(70.0f), window.GetAspect(), 0.1f, 1000.0f), &cameraTransform);
//	
//	root.AddChild((new GameObject(Vector3f(0, 2, 0), Quaternion(Vector3f(0,1,0), 0.4f), 1.0f))
//		->AddComponent(new MeshRenderer(Mesh("plane3.obj"), Material("bricks2")))
//		->AddChild((new GameObject(Vector3f(0, 0, 25)))
//			->AddComponent(new MeshRenderer(Mesh("plane3.obj"), Material("bricks2")))
//			//->AddChild((new GameObject())
//				->AddComponent(new FreeLook(window.GetCenter()))
//				->AddComponent(new FreeMove())));
//	
//	while(!window.IsCloseRequested())
//	{
//		window.Update();
//		root.ProcessInputAll(window.GetInput(), 0.01f);
//		root.UpdateAll(0.01f);
//		engine.Render(root, camera);
//		window.SwapBuffers();
//	}
	
	return 0;
}
