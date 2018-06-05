//
// Created by Wenlong Wang on 3/06/18.
//

#ifndef WATERRENDERING_MODELTEXTURE_H
#define WATERRENDERING_MODELTEXTURE_H


#include <OpenGL/OpenGL.h>

class ModelTexture {

public:
    ModelTexture(GLuint textureID);

    GLuint getTextureID() const;

    float getShineDamper() const;

    void setShineDamper(float shineDamper);

    float getReflectivity() const;

    void setReflectivity(float reflectivity);

private:
    GLuint textureID;
    float shineDamper = 1.0f;
    float reflectivity = 0;

};


#endif //WATERRENDERING_MODELTEXTURE_H
