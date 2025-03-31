#pragma once
#include "Entity.h"
#include "Dot.h"
#include <vector>
class DotStorage : public Entity
{
private:
	std::vector<Dot> dots;
	void InitBuffers() override;
public:
	float dotsSize = 0.1f; 
	int dotsQuantity = 0;
	int maxDotsQuantity = 2000;
	DotStorage();
	DotStorage(Shader* _dotShader, glm::mat4* _worldTransform);
	DotStorage& operator=(const DotStorage& other);
	DotStorage(const DotStorage& other);
	void SpawnDot(glm::vec2 position, float size);
	void PushDotsToShader();
	void ChangeDotColor(glm::vec3(_color));
	void Draw() override;

};

