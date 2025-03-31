#include "DotStorage.h"

DotStorage::DotStorage()
{

}

DotStorage::DotStorage(Shader* _dotShader, glm::mat4* _worldTransform)
{
	shader = _dotShader;
	worldTransform = _worldTransform;
	InitBuffers();
}
DotStorage& DotStorage::operator=(const DotStorage& other)
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
	dots = other.dots;
	dotsSize = other.dotsSize;
	dotsQuantity = other.dotsQuantity;
	maxDotsQuantity = other.maxDotsQuantity;
	return *this;
}

DotStorage::DotStorage(const DotStorage& other)
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
	dots = other.dots;
	dotsSize = other.dotsSize;
	dotsQuantity = other.dotsQuantity;
	maxDotsQuantity = other.maxDotsQuantity;
}

void DotStorage::InitBuffers()
{
	float quadVertices[] =
	{
		-dotsSize,  dotsSize,
		 dotsSize, -dotsSize,
		-dotsSize, -dotsSize,

		-dotsSize,  dotsSize,
		 dotsSize, -dotsSize,
		 dotsSize,  dotsSize
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void DotStorage::SpawnDot(glm::vec2 position, float size)
{
	dots.push_back(Dot(position, size));
	dotsQuantity++;
	PushDotsToShader();
}

void DotStorage::ChangeDotColor(glm::vec3(_color))
{
	color = _color;
}

void DotStorage::Draw()
{
	shader->use();
	shader->setMatrix4F("WorldTransform", *worldTransform);
	shader->setMatrix4F("LocalTransform", localTransform);
	shader->setVec3("fragColor", color);
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, dotsQuantity);
}

void DotStorage::PushDotsToShader()
{
	shader->use();
	if (dotsQuantity <= maxDotsQuantity)
	{
		for (unsigned int i = 0; i < dotsQuantity; i++)
		{
			std::string index = std::to_string(i);
			shader->setVec2(("offsets[" + index + "]"), glm::vec2(dots[i].position.x, dots[i].position.y));
		}
	}
}