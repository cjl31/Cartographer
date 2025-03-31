#include "Robot.h"

Robot::Robot()
{

}

Robot::Robot(glm::vec2 _position, float _size, Shader* _robotShader, Shader* _dotShader, glm::mat4* _worldTransform, std::vector<std::shared_ptr<Bound>>* mapBounds, std::vector<std::shared_ptr<Entity>>* _entities)
{
    sensor = Sensor(mapBounds, &position, _dotShader, _worldTransform, _entities);
    position = glm::vec2(0);
    Move(_position);
    shader = _robotShader;
    worldTransform = _worldTransform;
    size = _size;
    InitBuffers();
}

Robot::Robot(const Robot& other)
{
    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;
    size = other.size;
    position = other.position;
    worldTransform = other.worldTransform;
    localTransform = other.localTransform;
    color = other.color;
    sensor = other.sensor;
}

Robot& Robot::operator=(const Robot& other)
{
    if (this == &other) {
        return *this;
    }
    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;
    size = other.size;
    position = other.position;
    movementSpeed = other.movementSpeed;
    worldTransform = other.worldTransform;
    localTransform = other.localTransform;
    color = other.color;
    sensor = other.sensor;
    return *this;
}
