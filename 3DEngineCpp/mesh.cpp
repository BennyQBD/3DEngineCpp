#include "mesh.h"
#include <GL/glew.h>
#include <iostream>

#include <vector>
#include <cassert>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::map<std::string, MeshData*> Mesh::s_resourceMap;

MeshData::MeshData(int indexSize) : ReferenceCounter()
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
	m_size = indexSize;
}

MeshData::~MeshData() 
{ 
	if(m_vbo) glDeleteBuffers(1, &m_vbo);
	if(m_ibo) glDeleteBuffers(1, &m_ibo);
}


Mesh::Mesh(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals)
{
	m_fileName = "";
	InitMesh(vertices, vertSize, indices, indexSize, calcNormals);
}

Mesh::Mesh(const std::string& fileName)
{
	m_fileName = fileName;
	m_meshData = 0;
	
	std::map<std::string, MeshData*>::const_iterator it = s_resourceMap.find(fileName);
	if(it != s_resourceMap.end())
	{
		m_meshData = it->second;
		m_meshData->AddReference();
	}
	else
	{
		Assimp::Importer importer;
		
		const aiScene* scene = importer.ReadFile(fileName.c_str(), 
		                                         aiProcess_Triangulate |
		                                         aiProcess_GenSmoothNormals | 
		                                         aiProcess_FlipUVs);
		
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
			const aiVector3D* pPos = &(model->mVertices[i]);
			const aiVector3D* pNormal = &(model->mNormals[i]);
			const aiVector3D* pTexCoord = model->HasTextureCoords(0) ? &(model->mTextureCoords[0][i]) : &aiZeroVector;

			Vertex vert(Vector3f(pPos->x, pPos->y, pPos->z),
					    Vector2f(pTexCoord->x, pTexCoord->y),
					    Vector3f(pNormal->x, pNormal->y, pNormal->z));
			
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

Mesh::~Mesh()
{
	if(m_meshData && m_meshData->RemoveReference())
	{
		if(m_fileName.length() > 0)
			s_resourceMap.erase(m_fileName);
			
		delete m_meshData;
	}
}

void Mesh::InitMesh(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals)
{
	m_meshData = new MeshData(indexSize);

	if(calcNormals)
		this->CalcNormals(vertices, vertSize, indices, indexSize);

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

	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->GetVBO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3f));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshData->GetIBO());
	glDrawElements(GL_TRIANGLES, m_meshData->GetSize(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::CalcNormals(Vertex* vertices, int vertSize, int* indices, int indexSize)
{
	for(int i = 0; i < indexSize; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];
			
		Vector3f v1 = vertices[i1].pos - vertices[i0].pos;
		Vector3f v2 = vertices[i2].pos - vertices[i0].pos;
		
		Vector3f normal = v1.Cross(v2).Normalized();
		
		vertices[i0].normal += normal;
		vertices[i1].normal += normal;
		vertices[i2].normal += normal;
	}
	
	for(int i = 0; i < vertSize; i++)
		vertices[i].normal = vertices[i].normal.Normalized();
}
