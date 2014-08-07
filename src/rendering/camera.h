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

#ifndef CAMERA_H
#define CAMERA_H

#include "../core/math3d.h"
#include "../core/entityComponent.h"

//Cameras represent a location, orientation, and projection from
//which the scene can be rendered.
class Camera
{
public:
	//Transform is passed in so the Camera doesn't need to be attached to a game object.
	//That's useful for places such as the rendering engine which can use cameras
	//without creating placeholder game objects.
	Camera(const Matrix4f& projection, Transform* transform) :
		m_projection(projection),
		m_transform(transform) {}
	
	inline Transform* GetTransform()             { return m_transform; }
	inline const Transform& GetTransform() const { return *m_transform; }
	
	//This is the primary function of the camera. Multiplying a point by the returned matrix
	//will transform the point into it's location on the screen, where -1 represents the bottom/left
	//of the screen, and 1 represents the top/right of the screen.
	Matrix4f GetViewProjection()           const;
	
	inline void SetProjection(const Matrix4f& projection) { m_projection = projection; }
	inline void SetTransform(Transform* transform)        { m_transform = transform; }
protected:
private:
	Matrix4f   m_projection; //The projection with which the camera sees the world (i.e. perspective, orthographic, identity, etc.)
	Transform* m_transform;  //The transform representing the position and orientation of the camera.
};

//CameraComponents are an easy way to use a camera as a component
//on a game object.
class CameraComponent : public EntityComponent
{
public:
	//The camera's transform is initialized to 0 (null) because
	//at construction, this isn't attached to a game object,
	//and therefore doesn't have access to a valid transform.
	CameraComponent(const Matrix4f& projection) :
		m_camera(projection, 0) {}
	
	virtual void AddToEngine(CoreEngine* engine) const;
	
	inline Matrix4f GetViewProjection() const { return m_camera.GetViewProjection(); }
	
	inline void SetProjection(const Matrix4f& projection) { m_camera.SetProjection(projection); }
	virtual void SetParent(Entity* parent);
protected:
private:
	Camera m_camera; //The camera that's being used like a component.
};

#endif
