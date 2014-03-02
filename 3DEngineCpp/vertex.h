#ifndef VERTEX_H
#define VERTEX_H

#include "math3d.h"

struct Vertex
{
	Vector3f pos;
	Vector2f texCoord;
	Vector3f normal;

	Vertex(Vector3f pos, Vector2f texCoord = Vector2f(0,0), Vector3f normal = Vector3f(0,0,0)) :
		pos(pos),
		texCoord(texCoord),
		normal(normal) {}
};

#endif
