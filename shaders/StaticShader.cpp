//
// Created by Wenlong Wang on 4/06/18.
//

#include "StaticShader.h"




void StaticShader::bindAttributes() {
    ShaderProgram::bindAttributes(0, "vert_Position");
    ShaderProgram::bindAttributes(1, "vert_UV");
    ShaderProgram::bindAttributes(2, "vert_Normal");
}

StaticShader::StaticShader() {
    try {
        ShaderProgram::loadProgram(VERTEX_FILE, NULL, NULL, NULL, FRAGMENT_FILE);
    } catch (std::invalid_argument & e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        exit(0);
    }
}

void StaticShader::getAllUniformLocation() {
    try {
        uniformLocations.emplace("translation", getUniformLocation("u_Translation"));
        uniformLocations.emplace("view", getUniformLocation("u_View"));
        uniformLocations.emplace("projection", getUniformLocation("u_Projection"));
        uniformLocations.emplace("lightPosition", getUniformLocation("u_lightPosition"));
        uniformLocations.emplace("lightColour", getUniformLocation("lightColour"));
        uniformLocations.emplace("shineDamper", getUniformLocation("shineDamper"));
        uniformLocations.emplace("reflectivity", getUniformLocation("reflectivity"));
        uniformLocations.emplace("plane", getUniformLocation("u_plane"));
    } catch (std::invalid_argument& e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        cleanUp();
        exit(0);
    }

}

void StaticShader::loadTransformationMatrix(glm::mat4 translationMatrix) {
    loadMatrix(uniformLocations["translation"], translationMatrix);

}

void StaticShader::loadProjectionMatrix(glm::mat4 projectionMatrix) {
    loadMatrix(uniformLocations["projection"], projectionMatrix);
}

void StaticShader::loadViewMatrix(glm::mat4 viewMatrix) {
    loadMatrix(uniformLocations["view"], viewMatrix);
}

void StaticShader::loadLight(Light light) {
    ShaderProgram::loadVec3(uniformLocations["lightPosition"], light.getPosition());
    ShaderProgram::loadVec3(uniformLocations["lightColour"], light.getColour());
}

void StaticShader::loadShineVariables(float damper, float reflectivity) {
    ShaderProgram::loadFloat(uniformLocations["shineDamper"], damper);
    ShaderProgram::loadFloat(uniformLocations["reflectivity"], reflectivity);

}

void StaticShader::loadClipPlane(glm::vec4 plane) {
    ShaderProgram::loadVec4(uniformLocations["plane"], plane);

}
