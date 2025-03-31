#pragma once

#include <glm/glm.hpp>

class Dot
{
public:
	glm::vec2 position;
	float size;
	Dot(glm::vec2 _position, float _size)
	{
		position = _position;
		size = _size;
	}
};

