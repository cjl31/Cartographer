#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

class Entity
{
protected:
    float size = 1;
    glm::vec2 position = glm::vec2(0);
    glm::mat4* worldTransform;
    glm::mat4 localTransform = glm::mat4(1);
    glm::vec3 color = glm::vec3(0.9f,0.2f,0.9f);
    GLuint VAO, VBO, EBO;
    Shader* shader;
public:
    virtual void InitBuffers();
    virtual void Draw();
    virtual void Move(glm::vec2 value);
    
};

