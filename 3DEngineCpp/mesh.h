#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include <string>

class Mesh
{
public:
	Mesh(const std::string& fileName);
	Mesh();
	virtual ~Mesh();

	void AddVertices(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals = true);
	void Draw() const;
protected:
private:
	Mesh(Mesh& mesh) {}
	void operator=(Mesh& mesh) {}
	void CalcNormals(Vertex* vertices, int vertSize, int* indices, int indexSize);

	unsigned int m_vbo;
	unsigned int m_ibo;
	int m_size;
};

#endif
