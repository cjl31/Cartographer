#include "Bound.h"

Bound::Bound(glm::vec2 _begin, glm::vec2 _end, float _thickness, Shader* _shader, glm::mat4* _worldTransform)
{
	begin = _begin;
	end = _end;
	thickness = _thickness;
	center.x = (begin.x + end.x) / 2;
	center.y = (begin.y + end.y) / 2;

	worldTransform = _worldTransform;
	shader = _shader;

	normal = glm::normalize(glm::vec3(-(end.y - begin.y), end.x - begin.x, 0));
	InitBuffers();
}

Bound& Bound::operator=(const Bound& other)
{
	if (this == &other) {
		return *this;
	}
	size = other.size;
	position = other.position;
	VAO = other.VAO;
	VBO = other.VBO;
	EBO = other.EBO;
	worldTransform = other.worldTransform;
	localTransform = other.localTransform;
	color = other.color;
	shader = other.shader;
	begin = other.begin;
	end = other.end;
	center = other.center;
	normal = other.normal;
	thickness = other.thickness;
	return *this;
}

Bound::Bound(const Bound& other)
{
	size = other.size;
	position = other.position;
	VAO = other.VAO;
	VBO = other.VBO;
	EBO = other.EBO;
	worldTransform = other.worldTransform;
	localTransform = other.localTransform;
	color = other.color;
	shader = other.shader;
	begin = other.begin;
	end = other.end;
	center = other.center;
	normal = other.normal;
	thickness = other.thickness;
}

void Bound::InitBuffers()
{
	float halfThickness = thickness / 2.0f;
	float boundVertices[] = {
		begin.x + normal.x * halfThickness,		begin.y + normal.y * halfThickness,		0.0f,
		  end.x - normal.x * halfThickness, 	  end.y - normal.y * halfThickness,		0.0f,
		begin.x - normal.x * halfThickness,		begin.y - normal.y * halfThickness,		0.0f,
		  end.x + normal.x * halfThickness ,	  end.y + normal.y * halfThickness,		0.0f
	};
	unsigned int indices[] =
	{
	0, 1, 2,
	0, 1, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boundVertices), boundVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Bound::ChangeColor(glm::vec3 _color)
{
	color = _color;
}

void Bound::Draw() 
{
	shader->use();
	shader->setMatrix4F("WorldTransform", *worldTransform);
	shader->setMatrix4F("LocalTransform", localTransform);
	shader->setVec3("fragColor", color);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
