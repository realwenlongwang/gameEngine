//
// Created by Wenlong Wang on 6/06/18.
//

#ifndef WATERRENDERING_SKYBOXSHADER_H
#define WATERRENDERING_SKYBOXSHADER_H

#include "ShaderProgram.h"

class SkyboxShader: public ShaderProgram {
protected:
    void bindAttributes() override;

    void getAllUniformLocation() override;

public:
    SkyboxShader();

    void loadProjectionMatrix(glm::mat4 projectionMatrix);
    void loadViewMatrix(glm::mat4 viewMatrix);

private:
    constexpr static const char* VERTEX_FILE = "shaders/skybox.vert.glsl";
    constexpr static const char* FRAGMENT_FILE = "shaders/skybox.frag.glsl";
    std::map<const char*, GLint> uniformLocations;
};


#endif //WATERRENDERING_SKYBOXSHADER_H
