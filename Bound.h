#pragma once

#include <glm/glm.hpp>

#include "Entity.h"
#include "Shader.h"

class Bound : public Entity
{
public:
	glm::vec2 begin;
	glm::vec2 end;
	glm::vec2 center;
	glm::vec3 normal;
	float thickness;

	Bound(glm::vec2 _begin, glm::vec2 _end, float _thickness, Shader* _shader, glm::mat4* _worldTransform);
	Bound& operator=(const Bound& other);
	Bound(const Bound& other);
	void InitBuffers() override;
	void Draw() override;
	void ChangeColor(glm::vec3 _color);
};