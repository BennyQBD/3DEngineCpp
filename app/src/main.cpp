/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
	Material bricks("bricks", Texture("bricks.jpg"), 0.0f, 0, Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);
	Material bricks2("bricks2", Texture("bricks2.jpg"), 0.0f, 0, Texture("bricks2_normal.png"), Texture("bricks2_disp.jpg"), 0.04f, -1.0f);
	
	//Material skin("humanFace", Texture("human.jpg"), 0.0f, 0, Texture("human_normal_inv.jpg"));
	//Material skin("humanFace", Texture("human.jpg"), 0.08f, 8, Texture("human_normal_inv.jpg"));

	IndexedModel square;
	{
		square.AddVertex(1.0f, -1.0f, 0.0f);  square.AddTexCoord(Vector2f(1.0f, 1.0f));
		square.AddVertex(1.0f, 1.0f, 0.0f);   square.AddTexCoord(Vector2f(1.0f, 0.0f));
		square.AddVertex(-1.0f, -1.0f, 0.0f); square.AddTexCoord(Vector2f(0.0f, 1.0f));
		square.AddVertex(-1.0f, 1.0f, 0.0f);  square.AddTexCoord(Vector2f(0.0f, 0.0f));
		square.AddFace(0, 1, 2); square.AddFace(2, 1, 3);
	}
	Mesh customMesh("square", square.Finalize());
	
	AddToScene((new Entity(Vector3f(0, -1, 5), Quaternion(), 32.0f))
		->AddComponent(new MeshRenderer(Mesh("terrain02.obj"), Material("bricks"))));
		
	AddToScene((new Entity(Vector3f(7,0,7)))
		->AddComponent(new PointLight(Vector3f(0,1,0), 0.4f, Attenuation(0,0,1))));
	
	AddToScene((new Entity(Vector3f(20,-11.0f,5), Quaternion(Vector3f(1,0,0), ToRadians(-60.0f)) * Quaternion(Vector3f(0,1,0), ToRadians(90.0f))))
		->AddComponent(new SpotLight(Vector3f(0,1,1), 0.4f, Attenuation(0,0,0.02f), ToRadians(91.1f), 7, 1.0f, 0.5f)));
	
	AddToScene((new Entity(Vector3f(), Quaternion(Vector3f(1,0,0), ToRadians(-45))))
		->AddComponent(new DirectionalLight(Vector3f(1,1,1), 0.4f, 10, 80.0f, 1.0f)));
	
	AddToScene((new Entity(Vector3f(0, 2, 0), Quaternion(Vector3f(0,1,0), 0.4f), 1.0f))
		->AddComponent(new MeshRenderer(Mesh("plane3.obj"), Material("bricks2")))
		->AddChild((new Entity(Vector3f(0, 0, 25)))
			->AddComponent(new MeshRenderer(Mesh("plane3.obj"), Material("bricks2")))
			->AddChild((new Entity())
				->AddComponent(new CameraComponent(Matrix4f().InitPerspective(ToRadians(70.0f), window.GetAspect(), 0.1f, 1000.0f)))
				->AddComponent(new FreeLook(window.GetCenter()))
				->AddComponent(new FreeMove(10.0f)))));
	
	AddToScene((new Entity(Vector3f(24,-12,5), Quaternion(Vector3f(0,1,0), ToRadians(30.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
		
	AddToScene((new Entity(Vector3f(0,0,7), Quaternion(), 1.0f))
		->AddComponent(new MeshRenderer(Mesh("square"), Material("bricks2"))));
}

#include "boundingSphere.h"
#include "aabb.h"
#include "plane.h"
#include <iostream>

int main()
{
	BoundingSphere sphere1(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	BoundingSphere sphere2(Vector3f(0.0f, 3.0f, 0.0f), 1.0f);
	BoundingSphere sphere3(Vector3f(0.0f, 0.0f, 2.0f), 1.0f);
	BoundingSphere sphere4(Vector3f(1.0f, 0.0f, 0.0f), 1.0f);
	
	IntersectData sphere1IntersectSphere2 = sphere1.IntersectBoundingSphere(sphere2);
	IntersectData sphere1IntersectSphere3 = sphere1.IntersectBoundingSphere(sphere3);
	IntersectData sphere1IntersectSphere4 = sphere1.IntersectBoundingSphere(sphere4);
	
	std::cout << "Sphere1 intersect Sphere2: " << sphere1IntersectSphere2.GetDoesIntersect() 
	          << ", Distance: "                << sphere1IntersectSphere2.GetDistance() << std::endl;
	std::cout << "Sphere1 intersect Sphere3: " << sphere1IntersectSphere3.GetDoesIntersect() 
	          << ", Distance: "                << sphere1IntersectSphere3.GetDistance() << std::endl;
	std::cout << "Sphere1 intersect Sphere4: " << sphere1IntersectSphere4.GetDoesIntersect() 
	          << ", Distance: "                << sphere1IntersectSphere4.GetDistance() << std::endl;

	std::cout << std::endl;

	AABB aabb1(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
	AABB aabb2(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(2.0f, 2.0f, 2.0f));
	AABB aabb3(Vector3f(1.0f, 0.0f, 0.0f), Vector3f(2.0f, 1.0f, 1.0f));
	AABB aabb4(Vector3f(0.0f, 0.0f, -2.0f), Vector3f(1.0f, 1.0f, -1.0f));
	AABB aabb5(Vector3f(0.0f, 0.5f, 0.0f), Vector3f(1.0f, 1.5f, 1.0f));

	IntersectData aabb1Intersectaabb2 = aabb1.IntersectAABB(aabb2);
	IntersectData aabb1Intersectaabb3 = aabb1.IntersectAABB(aabb3);
	IntersectData aabb1Intersectaabb4 = aabb1.IntersectAABB(aabb4);
	IntersectData aabb1Intersectaabb5 = aabb1.IntersectAABB(aabb5);

	std::cout << "AABB1 intersect AABB2: " << aabb1Intersectaabb2.GetDoesIntersect() 
	          << ", Distance: "            << aabb1Intersectaabb2.GetDistance() << std::endl;

	std::cout << "AABB1 intersect AABB3: " << aabb1Intersectaabb3.GetDoesIntersect() 
	          << ", Distance: "            << aabb1Intersectaabb3.GetDistance() << std::endl;

	std::cout << "AABB1 intersect AABB4: " << aabb1Intersectaabb4.GetDoesIntersect() 
	          << ", Distance: "            << aabb1Intersectaabb4.GetDistance() << std::endl;

	std::cout << "AABB1 intersect AABB5: " << aabb1Intersectaabb5.GetDoesIntersect() 
	          << ", Distance: "            << aabb1Intersectaabb5.GetDistance() << std::endl;


	std::cout << std::endl;

	Plane plane1(Vector3f(0.0f, 1.0f, 0.0f), 0.0f);
	
	IntersectData plane1IntersectSphere1 = plane1.IntersectSphere(sphere1);
	IntersectData plane1IntersectSphere2 = plane1.IntersectSphere(sphere2);
	IntersectData plane1IntersectSphere3 = plane1.IntersectSphere(sphere3);
	IntersectData plane1IntersectSphere4 = plane1.IntersectSphere(sphere4);

	std::cout << "Plane1 intersect Sphere1: " << plane1IntersectSphere1.GetDoesIntersect() 
	          << ", Distance: "               << plane1IntersectSphere1.GetDistance() << std::endl;
	
	std::cout << "Plane1 intersect Sphere2: " << plane1IntersectSphere2.GetDoesIntersect() 
	          << ", Distance: "               << plane1IntersectSphere2.GetDistance() << std::endl;
	
	std::cout << "Plane1 intersect Sphere3: " << plane1IntersectSphere3.GetDoesIntersect() 
	          << ", Distance: "               << plane1IntersectSphere3.GetDistance() << std::endl;
	
	std::cout << "Plane1 intersect Sphere4: " << plane1IntersectSphere4.GetDoesIntersect() 
	          << ", Distance: "               << plane1IntersectSphere4.GetDistance() << std::endl;

//	TestGame game;
//	Window window(800, 600, "3D Game Engine");
//	RenderingEngine renderer(window);
//	
//	//window.SetFullScreen(true);
//	
//	CoreEngine engine(60, &window, &renderer, &game);
//	engine.Start();
	
	//window.SetFullScreen(false);

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
