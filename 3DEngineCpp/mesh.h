#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include <string>
#include <map>

class MeshData
{
public:
	MeshData(int indexSize);
	virtual ~MeshData();
	
	void AddReference();
	bool RemoveReference();
	
	inline unsigned int GetVBO() { return m_vbo; }
	inline unsigned int GetIBO() { return m_ibo; }
	inline int GetSize() { return m_size; }
protected:	
private:
	MeshData(MeshData& other) {}
	void operator=(MeshData& other) {}

	unsigned int m_vbo;
	unsigned int m_ibo;
	int m_size;
	unsigned int m_referenceCount;
};

class Mesh
{
public:
	Mesh(const std::string& fileName);
	Mesh(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals);
	virtual ~Mesh();

	void Draw() const;
protected:
private:
	static std::map<std::string, MeshData*> s_resourceMap;
	
	Mesh(Mesh& mesh) {}
	void operator=(Mesh& mesh) {}
	
	void CalcNormals(Vertex* vertices, int vertSize, int* indices, int indexSize);
	void InitMesh(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals = true);

	std::string m_fileName;
	MeshData* m_meshData;
};

#endif
