//
// Created by Wenlong Wang on 4/06/18.
//

#include "Light.h"

Light::Light(const glm::vec3 &position, const glm::vec3 &colour) : position(position), colour(colour) {}

const glm::vec3 &Light::getPosition() const {
    return position;
}

void Light::setPosition(const glm::vec3 &position) {
    Light::position = position;
}

const glm::vec3 &Light::getColour() const {
    return colour;
}

void Light::setColour(const glm::vec3 &colour) {
    Light::colour = colour;
}
