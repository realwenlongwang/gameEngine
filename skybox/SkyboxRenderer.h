//
// Created by Wenlong Wang on 6/06/18.
//

#ifndef WATERRENDERING_SKYBOXRENDERER_H
#define WATERRENDERING_SKYBOXRENDERER_H

#include "SkyboxShader.h"
#include "Skybox.h"
#include "camera.h"

class SkyboxRenderer {
public:
    SkyboxRenderer(const SkyboxShader &skyboxShader);

    void setProjectMatrix(const glm::mat4 &projectMatrix);
    void render(Skybox);

private:
    SkyboxShader skyboxShader;
    glm::mat4 projectMatrix;

    void prepareRawModel(Skybox skybox);

};


#endif //WATERRENDERING_SKYBOXRENDERER_H
