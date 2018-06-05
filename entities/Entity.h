//
// Created by Wenlong Wang on 3/06/18.
//

#ifndef WATERRENDERING_ENTITY_H
#define WATERRENDERING_ENTITY_H


#include <glm/vec3.hpp>
#include "TexturedModel.h"

class Entity {
public:
    Entity(const TexturedModel &texturedModel, const glm::vec3 &position, const glm::vec3 &rotation, float scale);
    void increasePosition(float dx, float dy, float dz);
    void increaseRotation(float dx, float dy, float dz);

    const TexturedModel &getTexturedModel() const;

    const glm::vec3 &getPosition() const;

    const glm::vec3 &getRotation() const;

    float getScale() const;

private:
    TexturedModel texturedModel;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;
};


#endif //WATERRENDERING_ENTITY_H
