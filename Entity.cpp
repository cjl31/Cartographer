#include "Entity.h"
void Entity::InitBuffers()
{
    float vertices[] = {
    size,	size,	0.0f,  // top right
    size,	-size,	0.0f,  // bottom right
    -size,	-size,	0.0f,  // bottom left
    -size,	size,	0.0f   // top left
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Entity::Draw()
{
    if (this != nullptr) {
        shader->use();
        shader->setMatrix4F("WorldTransform", *worldTransform);
        shader->setMatrix4F("LocalTransform", localTransform);
        shader->setVec3("fragColor", color);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Entity::Move(glm::vec2 value)
{
    position += value;
    localTransform = glm::translate(localTransform, glm::vec3(value, 0.0f));
}
