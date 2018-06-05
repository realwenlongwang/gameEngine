//
// Created by Wenlong Wang on 3/06/18.
//

#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint textureID) : textureID(textureID) {}

GLuint ModelTexture::getTextureID() const {
    return textureID;
}

float ModelTexture::getShineDamper() const {
    return shineDamper;
}

void ModelTexture::setShineDamper(float shineDamper) {
    ModelTexture::shineDamper = shineDamper;
}

float ModelTexture::getReflectivity() const {
    return reflectivity;
}

void ModelTexture::setReflectivity(float reflectivity) {
    ModelTexture::reflectivity = reflectivity;
}
