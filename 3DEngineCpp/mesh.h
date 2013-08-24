#ifndef MESH_H
#define MESH_H

#include "vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void addVertices(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals = true);
	void draw();

protected:
private:
	void calcNormals(Vertex* vertices, int vertSize, int* indices, int indexSize);

	unsigned int m_vbo;
	unsigned int m_ibo;
	int m_size;
};

#endif