//
// Created by Wenlong Wang on 3/06/18.
//

#include "Entity.h"

Entity::Entity(const TexturedModel &texturedModel, const glm::vec3 &position, const glm::vec3 &rotation, float scale)
        : texturedModel(texturedModel), position(position), rotation(rotation), scale(scale) {}

void Entity::increasePosition(float dx, float dy, float dz) {
    position.x += dx;
    position.y += dy;
    position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz) {
    rotation.x += dx;
    rotation.y += dy;
    rotation.z += dz;
}

const TexturedModel &Entity::getTexturedModel() const {
    return texturedModel;
}

const glm::vec3 &Entity::getPosition() const {
    return position;
}

const glm::vec3 &Entity::getRotation() const {
    return rotation;
}

float Entity::getScale() const {
    return scale;
}


