//
// Created by Wenlong Wang on 5/06/18.
//

#include "TerrainShader.h"

void TerrainShader::bindAttributes() {
    ShaderProgram::bindAttributes(0, "vert_Position");
    ShaderProgram::bindAttributes(1, "vert_UV");
    ShaderProgram::bindAttributes(2, "vert_Normal");
}

TerrainShader::TerrainShader() {
    try {
        ShaderProgram::loadProgram(VERTEX_FILE, NULL, NULL, NULL, FRAGMENT_FILE);
    } catch (std::invalid_argument & e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        exit(0);
    }
}

void TerrainShader::getAllUniformLocation() {
    try {
        uniformLocations.emplace("translation", getUniformLocation("u_Translation"));
        uniformLocations.emplace("view", getUniformLocation("u_View"));
        uniformLocations.emplace("projection", getUniformLocation("u_Projection"));
        uniformLocations.emplace("lightPosition", getUniformLocation("u_lightPosition"));
        uniformLocations.emplace("lightColour", getUniformLocation("lightColour"));
        uniformLocations.emplace("shineDamper", getUniformLocation("shineDamper"));
        uniformLocations.emplace("reflectivity", getUniformLocation("reflectivity"));
    } catch (std::invalid_argument& e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        cleanUp();
        exit(0);
    }

}

void TerrainShader::loadTransformationMatrix(glm::mat4 translationMatrix) {
    loadMatrix(uniformLocations["translation"], translationMatrix);

}

void TerrainShader::loadProjectionMatrix(glm::mat4 projectionMatrix) {
    loadMatrix(uniformLocations["projection"], projectionMatrix);
}

void TerrainShader::loadViewMatrix(glm::mat4 viewMatrix) {
    loadMatrix(uniformLocations["view"], viewMatrix);
}

void TerrainShader::loadLight(Light light) {
    ShaderProgram::loadVec3(uniformLocations["lightPosition"], light.getPosition());
    ShaderProgram::loadVec3(uniformLocations["lightColour"], light.getColour());
}

void TerrainShader::loadShineVariables(float damper, float reflectivity) {
    ShaderProgram::loadFloat(uniformLocations["shineDamper"], damper);
    ShaderProgram::loadFloat(uniformLocations["reflectivity"], reflectivity);

}