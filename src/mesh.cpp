#include "mesh.h"
#include <GL/glew.h>
#include <iostream>

#include <vector>
#include <cassert>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::map<std::string, MeshData*> Mesh::s_resourceMap;

MeshData::MeshData(int indexSize) : 
	ReferenceCounter(),
	m_size(indexSize)
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
}

MeshData::~MeshData() 
{ 
	if(m_vbo) glDeleteBuffers(1, &m_vbo);
	if(m_ibo) glDeleteBuffers(1, &m_ibo);
}


Mesh::Mesh(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals) :
	m_fileName("")
{
	InitMesh(vertices, vertSize, indices, indexSize, calcNormals);
}

Mesh::Mesh(const std::string& fileName) :
	m_fileName(fileName),
	m_meshData(0)
{
	std::map<std::string, MeshData*>::const_iterator it = s_resourceMap.find(fileName);
	if(it != s_resourceMap.end())
	{
		m_meshData = it->second;
		m_meshData->AddReference();
	}
	else
	{
		Assimp::Importer importer;
		
		const aiScene* scene = importer.ReadFile(("./res/models/" + fileName).c_str(), 
		                                         aiProcess_Triangulate |
		                                         aiProcess_GenSmoothNormals | 
		                                         aiProcess_FlipUVs |
		                                         aiProcess_CalcTangentSpace);
		
		if(!scene)
		{
			std::cout << "Mesh load failed!: " << fileName << std::endl;
			assert(0 == 0);
		}
		
		const aiMesh* model = scene->mMeshes[0];
		
		std::vector<Vertex> vertices;
		std::vector<int> indices;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for(unsigned int i = 0; i < model->mNumVertices; i++) 
		{
			const aiVector3D pos = model->mVertices[i];
			const aiVector3D normal = model->mNormals[i];
			const aiVector3D texCoord = model->HasTextureCoords(0) ? model->mTextureCoords[0][i] : aiZeroVector;
			const aiVector3D tangent = model->mTangents[i];

			Vertex vert(Vector3f(pos.x, pos.y, pos.z),
					    Vector2f(texCoord.x, texCoord.y),
					    Vector3f(normal.x, normal.y, normal.z),
					    Vector3f(tangent.x, tangent.y, tangent.z));
			
			vertices.push_back(vert);
		}

		for(unsigned int i = 0; i < model->mNumFaces; i++)
		{
			const aiFace& face = model->mFaces[i];
			assert(face.mNumIndices == 3);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}
		
		InitMesh(&vertices[0], vertices.size(), (int*)&indices[0], indices.size(), false);
		
		s_resourceMap.insert(std::pair<std::string, MeshData*>(fileName, m_meshData));
	}
}

Mesh::Mesh(const Mesh& mesh) :
	m_fileName(mesh.m_fileName),
	m_meshData(mesh.m_meshData)
{
	m_meshData->AddReference();
}

Mesh::~Mesh()
{
	if(m_meshData && m_meshData->RemoveReference())
	{
		if(m_fileName.length() > 0)
		{
			s_resourceMap.erase(m_fileName);
		}
			
		delete m_meshData;
	}
}

void Mesh::InitMesh(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals)
{
	m_meshData = new MeshData(indexSize);

	if(calcNormals)
	{
		CalcNormals(vertices, vertSize, indices, indexSize);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->GetVBO());
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshData->GetIBO());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(int), indices, GL_STATIC_DRAW);
}

void Mesh::Draw() const
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->GetVBO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3f));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f) + sizeof(Vector3f)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshData->GetIBO());
	glDrawElements(GL_TRIANGLES, m_meshData->GetSize(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void Mesh::CalcNormals(Vertex* vertices, int vertSize, int* indices, int indexSize) const
{
	for(int i = 0; i < indexSize; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];
			
		Vector3f v1 = vertices[i1].GetPos() - vertices[i0].GetPos();
		Vector3f v2 = vertices[i2].GetPos() - vertices[i0].GetPos();
		
		Vector3f normal = v1.Cross(v2).Normalized();
		
		vertices[i0].SetNormal(vertices[i0].GetNormal() + normal);
		vertices[i1].SetNormal(vertices[i1].GetNormal() + normal);
		vertices[i2].SetNormal(vertices[i2].GetNormal() + normal);
	}
	
	for(int i = 0; i < vertSize; i++)
		vertices[i].SetNormal(vertices[i].GetNormal().Normalized());
}
