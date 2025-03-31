#include "Map.h"

Map::Map()
{

}
Map& Map::operator=(const Map& other) {
	if (this == &other) {
		return *this;
	}
	robot = other.robot;
	worldTransform = other.worldTransform;
	entities = other.entities;
	mapBounds = other.mapBounds;
	return *this;
}
Map::Map(const Map& other)
{
	robot = other.robot;
	worldTransform = other.worldTransform;
	entities = other.entities;
	mapBounds = other.mapBounds;
}
void Map::DrawEntities()
{
    for (std::shared_ptr<Entity> entity : entities)
    {
        entity->Draw();
    }
}

void Map::addRobot(glm::vec2 _position, float size, Shader* _robotShader, Shader* _dotShader)
{
    robot = std::make_shared<Robot>(_position, size, _robotShader, _dotShader, &worldTransform, &mapBounds, &entities);
    entities.push_back(robot);
}

void Map::addBound(Bound _bound)
{
    mapBounds.push_back(std::make_shared<Bound>(_bound));
    entities.push_back(mapBounds[mapBounds.size() - 1]);
}

std::vector<std::shared_ptr<Bound>>* Map::getMapBounds()
{
    return &mapBounds;
}