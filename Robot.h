#pragma once
#include "Entity.h"
#include "Sensor.h"

class Robot : public Entity {
private:

public:
    Sensor sensor;
    float movementSpeed = 0.003f;
    glm::vec2 viewDirection = glm::vec2(1);
    Robot();
    Robot& operator=(const Robot& other);
    Robot(glm::vec2 _position, float _size, Shader* _robotShader, Shader* _dotShader, glm::mat4* _worldTransform,
        std::vector<std::shared_ptr<Bound>>* mapBounds, std::vector<std::shared_ptr<Entity>>* _entities);
    Robot(const Robot& other);
};