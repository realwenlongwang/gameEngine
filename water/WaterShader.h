//
// Created by Wenlong Wang on 7/06/18.
//

#ifndef WATERRENDERING_WATERSHADER_H
#define WATERRENDERING_WATERSHADER_H

#include "ShaderProgram.h"
#include "camera.h"
#include "Light.h"
class WaterShader: public ShaderProgram {
public:
    WaterShader();
    void loadProjectionMatrix(glm::mat4 projectionMatrix);
    void loadViewMatrix(Camera *camera);
    void loadModelMatrix(glm::mat4 modelMatrix);
    void connectTextureUnits();
    void loadMoveFactor(float moveFactor);
    void loadLight(Light light);
    void loadProjectParams(float nearPlane, float farPlane);

protected:
    void getAllUniformLocation() override;

    void bindAttributes() override;

private:
    const char* VERTEX_FILE = "shaders/water.vert.glsl";
    const char* FRAGMENT_FILE = "shaders/water.frag.glsl";

    std::map<const char*, GLint> uniformLocations;
};


#endif //WATERRENDERING_WATERSHADER_H
