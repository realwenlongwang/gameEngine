//
// Created by Wenlong Wang on 6/06/18.
//

#ifndef WATERRENDERING_SKYBOX_H
#define WATERRENDERING_SKYBOX_H

#include <glm/glm.hpp>
#include <vector>
#include "RawModel.h"
#include "Loader.h"
class Skybox {

public:
    Skybox(Loader loader);

    const RawModel &getRawModel() const;

    GLuint getSkyboxTexture() const;

private:
    RawModel rawModel = RawModel(0, 0);
    GLuint skyboxTexture;
    constexpr static const char* VERTEX_FILE = "shaders/skybox.vert.glsl";
    constexpr static const char* FRAGMENT_FILE = "shaders/skybox.frag.glsl";
    RawModel generateSkybox(Loader loader);

    constexpr static const char* RIGHT = "res/skybox/right.png";
    constexpr static const char* LEFT = "res/skybox/left.png";
    constexpr static const char* TOP = "res/skybox/top.png";
    constexpr static const char* BOTTOM = "res/skybox/bottom.png";
    constexpr static const char* BACK = "res/skybox/back.png";
    constexpr static const char* FRONT = "res/skybox/front.png";

    const char* filenames[6] = {
            RIGHT,
            LEFT,
            BOTTOM,
            TOP,
            BACK,
            FRONT
    };

};


#endif //WATERRENDERING_SKYBOX_H
