#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Entity.h"
#include "Bound.h"
#include "Robot.h"
#include <memory>

class Map
{

public:
    std::shared_ptr<Robot> robot;
    glm::mat4 worldTransform = glm::mat4(1);
    Map();
    Map& operator=(const Map& other);
    Map(const Map& other);
    void DrawEntities();
    void addRobot(glm::vec2 _position, float size, Shader* _robotShader, Shader* _dotShader);
    void addBound(Bound _bound);
    std::vector<std::shared_ptr<Bound>>* getMapBounds();
private:
    std::vector<std::shared_ptr<Entity>> entities = std::vector<std::shared_ptr<Entity>>(0);
    std::vector<std::shared_ptr<Bound>> mapBounds;
};

