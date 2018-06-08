//
// Created by Wenlong Wang on 7/06/18.
//

#ifndef WATERRENDERING_GUITEXTURE_H
#define WATERRENDERING_GUITEXTURE_H


#include <OpenGL/OpenGL.h>
#include <glm/glm.hpp>

class GuiTexture {

public:
    GuiTexture(GLuint texture, const glm::vec2 &position, const glm::vec2 &scale);

    GLuint getTexture() const;

    const glm::vec2 &getPosition() const;

    const glm::vec2 &getScale() const;

private:
    GLuint texture;
    // The center of 2D texture
    glm::vec2 position;
    // The width and height of texture, in relation with the size of the screen
    glm::vec2 scale;

};


#endif //WATERRENDERING_GUITEXTURE_H
