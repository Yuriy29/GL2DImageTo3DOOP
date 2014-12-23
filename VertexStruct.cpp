#include "VertexStruct.h"

VertexStruct::VertexStruct(int u, int v)
{
	pos = new glm::vec3[u*v];
	normal = new glm::vec3[u*v];
	tex = new glm::vec2[u*v];
}


VertexStruct::~VertexStruct(void)
{
}
