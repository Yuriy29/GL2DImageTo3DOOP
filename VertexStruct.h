#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class VertexStruct
{
public:
	glm::vec3 *pos;
	glm::vec3 *normal;
	glm::vec2 *tex;
	VertexStruct(int u, int v);
	~VertexStruct(void);
};

