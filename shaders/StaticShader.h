//
// Created by Wenlong Wang on 4/06/18.
//

#ifndef WATERRENDERING_STATICSHADER_H
#define WATERRENDERING_STATICSHADER_H

#include <map>
#include "ShaderProgram.h"
#include "Light.h"
/**
 * Implementation of ShaderProgram class
 */
class StaticShader : public ShaderProgram{
protected:
    void bindAttributes() override;

    void getAllUniformLocation() override;

public:
    StaticShader();
    void loadTransformationMatrix(glm::mat4 translationMatrix);
    void loadProjectionMatrix(glm::mat4 projectionMatrix);
    void loadViewMatrix(glm::mat4 viewMatrix);
    void loadLight(Light light);
    void loadShineVariables(float damper, float reflectivity);
    void loadClipPlane(glm::vec4 plane);

private:
    const char* VERTEX_FILE = "shaders/entity.vert.glsl";
    const char* FRAGMENT_FILE = "shaders/entity.frag.glsl";
    std::map<const char*, GLint> uniformLocations;


};


#endif //WATERRENDERING_STATICSHADER_H
