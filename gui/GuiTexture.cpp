//
// Created by Wenlong Wang on 7/06/18.
//

#include "GuiTexture.h"

GuiTexture::GuiTexture(GLuint texture, const glm::vec2 &position, const glm::vec2 &scale) : texture(texture),
                                                                                            position(position),
                                                                                            scale(scale) {}

GLuint GuiTexture::getTexture() const {
    return texture;
}

const glm::vec2 &GuiTexture::getPosition() const {
    return position;
}

const glm::vec2 &GuiTexture::getScale() const {
    return scale;
}
