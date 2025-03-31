#include "Sensor.h"
Sensor::Sensor()
{

}

Sensor::Sensor(std::vector<std::shared_ptr<Bound>>* _bounds, glm::vec2* _position,
    Shader* _dotShader, glm::mat4* _worldTransform, std::vector<std::shared_ptr<Entity>>* _entities)
{
    mapBounds = _bounds;
    dotStorage = std::make_shared<DotStorage>(_dotShader, _worldTransform);
    _entities->push_back(dotStorage);
    position = _position;
}

Sensor& Sensor::operator=(const Sensor& other) 
{
    if (this == &other) {
        return *this;
    }
    mapBounds = other.mapBounds;
    position = other.position;
    float tolerance = other.tolerance;
    dotStorage = other.dotStorage;
    return *this;
}

Sensor::Sensor(const Sensor& other)
{
    mapBounds = other.mapBounds;
    position = other.position;
    float tolerance = other.tolerance;
    dotStorage = other.dotStorage;
}

void Sensor::SetDotColor(glm::vec3 _color)
{
    dotStorage->ChangeDotColor(_color);
}

void Sensor::ShotAllDirections()
{
    Shot(glm::vec2(1.0f, 0.0f));
    Shot(glm::vec2(-1.0f, 0.0f));
    Shot(glm::vec2(0.0f, 1.0f));
    Shot(glm::vec2(0.0f, -1.0f));
    Shot(glm::vec2(1.0f, 1.0f));
    Shot(glm::vec2(-1.0f, 1.0f));
    Shot(glm::vec2(1.0f, -1.0f));
    Shot(glm::vec2(-1.0f, -1.0f));
}

void Sensor::Shot(glm::vec2 direction)
{
    float distance = FindBound(direction);
    if (distance != -1)
    {
        glm::vec2 dotPosition = glm::vec2(glm::vec2((*position).x + direction.x * distance, (*position).y + direction.y * distance));
        dotStorage->SpawnDot(dotPosition, dotStorage->dotsSize);
    }
}

float Sensor::FindBound(glm::vec2 direction)
{
    std::vector<std::shared_ptr<Bound>> intersectedBounds;
    std::vector<float> distances(0);
    for (int i = 0; i < (*mapBounds).size(); i++)
    {
        float intersectionDistance = -1;
        if (glm::intersectRayPlane
        (glm::vec3(position->x, position->y, 0.0f), glm::vec3(direction, 0.0f),
            glm::vec3((*mapBounds)[i]->center.x, (*mapBounds)[i]->center.y, 0.0f),
            (*mapBounds)[i]->normal, intersectionDistance))
        {
            float pointX = position->x + direction.x * intersectionDistance;
            float pointY = position->y + direction.y * intersectionDistance;
            if (isPointOnSegment((*mapBounds)[i]->begin.x, (*mapBounds)[i]->begin.y, (*mapBounds)[i]->end.x, (*mapBounds)[i]->end.y, pointX, pointY)
                && (dotStorage->dotsQuantity < dotStorage->maxDotsQuantity))
            {
                intersectedBounds.push_back((*mapBounds)[i]);
                distances.push_back(intersectionDistance);
            }
        }
    }
    if (distances.size() != 0)
    {
        auto min = std::min_element(distances.begin(), distances.end());
        return *min;
    }
    return -1;
}

void Sensor::MassiveShotInDirection(glm::vec2 _direction)
{
    Shot(_direction);
    Shot(RotateVector(_direction, glm::radians(30.0f)));
    for (float value = 2.0f; value <= 17.0f; value += 5.0f)
    {
        Shot(RotateVector(_direction, glm::radians(value)));
        Shot(RotateVector(_direction, glm::radians(-value)));
    }
}

glm::vec2 Sensor::RotateVector(glm::vec2 _vector, float angle)
{
    float rotatedX = _vector.x * cos(angle) - _vector.y * sin(angle);
    float rotatedY = _vector.x * sin(angle) + _vector.y * cos(angle);
    glm::vec2 rotatedDirection = glm::vec2(rotatedX, rotatedY);
    return rotatedDirection;
}

bool Sensor::isPointOnSegment(float x1, float y1, float x2, float y2, float pointX, float pointY)
{
    if (std::min(x1, x2) - tolerance <= pointX && pointX <= std::max(x1, x2) + tolerance &&
        std::min(y1, y2) - tolerance <= pointY && pointY <= std::max(y1, y2) + tolerance)
    {
        return true;
    }
    return false;
}
