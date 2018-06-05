//
// Created by Wenlong Wang on 4/06/18.
//

#ifndef WATERRENDERING_LIGHT_H
#define WATERRENDERING_LIGHT_H


#include <glm/vec3.hpp>

class Light {

public:
    Light(const glm::vec3 &position, const glm::vec3 &colour);

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getColour() const;

    void setColour(const glm::vec3 &colour);

private:
    glm::vec3 position;
    glm::vec3 colour;

};


#endif //WATERRENDERING_LIGHT_H
