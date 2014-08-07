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

#ifndef MESH_H
#define MESH_H

#include "../core/math3d.h"
#include "../core/referenceCounter.h"

#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>

class IndexedModel
{
public:
	IndexedModel() {}
	IndexedModel(const std::vector<unsigned int> indices, const std::vector<Vector3f>& positions, const std::vector<Vector2f>& texCoords,
		const std::vector<Vector3f>& normals = std::vector<Vector3f>(), const std::vector<Vector3f>& tangents = std::vector<Vector3f>()) :
			m_indices(indices),
			m_positions(positions),
			m_texCoords(texCoords),
			m_normals(normals),
			m_tangents(tangents) {}

	bool IsValid() const;
	void CalcNormals();
	void CalcTangents();

	IndexedModel Finalize();

	void AddVertex(const Vector3f& vert);
	inline void AddVertex(float x, float y, float z) { AddVertex(Vector3f(x, y, z)); }
	
	void AddTexCoord(const Vector2f& texCoord);
	inline void AddTexCoord(float x, float y) { AddTexCoord(Vector2f(x, y)); }
	
	void AddNormal(const Vector3f& normal);
	inline void AddNormal(float x, float y, float z) { AddNormal(Vector3f(x, y, z)); }
	
	void AddTangent(const Vector3f& tangent);
	inline void AddTangent(float x, float y, float z) { AddTangent(Vector3f(x, y, z)); }
	
	void AddFace(unsigned int vertIndex0, unsigned int vertIndex1, unsigned int vertIndex2);

	inline const std::vector<unsigned int>& GetIndices() const { return m_indices; }
	inline const std::vector<Vector3f>& GetPositions()   const { return m_positions; }
	inline const std::vector<Vector2f>& GetTexCoords()   const { return m_texCoords; }
	inline const std::vector<Vector3f>& GetNormals()     const { return m_normals; }
	inline const std::vector<Vector3f>& GetTangents()    const { return m_tangents; }
private:
	std::vector<unsigned int> m_indices;
    std::vector<Vector3f> m_positions;
    std::vector<Vector2f> m_texCoords;
    std::vector<Vector3f> m_normals;
    std::vector<Vector3f> m_tangents;  
};

class MeshData : public ReferenceCounter
{
public:
	MeshData(const IndexedModel& model);
	virtual ~MeshData();
	
	void Draw() const;
protected:	
private:
	MeshData(MeshData& other) {}
	void operator=(MeshData& other) {}

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		TANGENT_VB,
		
		INDEX_VB,
		
		NUM_BUFFERS
	};
	
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	int m_drawCount;
};

class Mesh
{
public:
	Mesh(const std::string& fileName = "cube.obj");
	Mesh(const std::string& meshName, const IndexedModel& model);
	Mesh(const Mesh& mesh);
	virtual ~Mesh();

	void Draw() const;
protected:
private:
	static std::map<std::string, MeshData*> s_resourceMap;

	std::string m_fileName;
	MeshData* m_meshData;
	
	void operator=(Mesh& mesh) {}
};

//class MeshBuilder
//{
//public:
//	MeshBuilder() {}
//	
//	void AddVertex(const Vector3f& vert);
////	inline void AddVertex(float x, float y, float z) { AddVertex(Vector3f(x, y, z)); }
//	
//	void AddTexCoord(const Vector2f& texCoord);
////	inline void AddTexCoord(float x, float y) { AddTexCoord(Vector2f(x, y)); }
//	
//	void AddFace(unsigned int vertIndex0, unsigned int vertIndex1, unsigned int vertIndex2);
//	
//	Mesh FinalizeMesh(const std::string& meshName);
//	
//	inline IndexedModel* GetModel() { return &m_model; }
//protected:
//private:
//	IndexedModel m_model;
//};

#endif
