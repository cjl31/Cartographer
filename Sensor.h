#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <vector>

#include "Shader.h"
#include "Bound.h"
#include "DotStorage.h"


class Sensor {

public:
    Sensor();
    Sensor(std::vector<std::shared_ptr<Bound>>* _bounds, glm::vec2* _position,
        Shader* _dotShader, glm::mat4* _worldTransform, std::vector<std::shared_ptr<Entity>>* _entities);
    Sensor(const Sensor& other);
    Sensor& operator=(const Sensor& other);
    void SetDotColor(glm::vec3 _color);
    void MassiveShotInDirection(glm::vec2 _direction);
    void ShotAllDirections();
    void Shot(glm::vec2 direction); 
private:
    std::vector<std::shared_ptr<Bound>>* mapBounds;
    glm::vec2* position;
    float tolerance = 0.00001f;
    std::shared_ptr<DotStorage> dotStorage;
    float FindBound(glm::vec2 direction);
    bool isPointOnSegment(float x1, float y1, float x2, float y2, float pointX, float pointY);
    glm::vec2 RotateVector(glm::vec2 _vector, float angle);
};

