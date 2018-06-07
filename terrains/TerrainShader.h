//
// Created by Wenlong Wang on 5/06/18.
//

#ifndef WATERRENDERING_TERRAINSHADER_H
#define WATERRENDERING_TERRAINSHADER_H

#include "ShaderProgram.h"
#include "Light.h"

class TerrainShader: public ShaderProgram {
protected:
    void bindAttributes() override;

    void getAllUniformLocation() override;

public:
    TerrainShader();
    void loadTransformationMatrix(glm::mat4 translationMatrix);
    void loadProjectionMatrix(glm::mat4 projectionMatrix);
    void loadViewMatrix(glm::mat4 viewMatrix);
    void loadLight(Light light);
    void loadShineVariables(float damper, float reflectivity);

private:
    constexpr static const char* VERTEX_FILE = "shaders/terrain.vert.glsl";
    constexpr static const char* FRAGMENT_FILE = "shaders/terrain.frag.glsl";
    std::map<const char*, GLint> uniformLocations;
};


#endif //WATERRENDERING_TERRAINSHADER_H
