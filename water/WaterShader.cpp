//
// Created by Wenlong Wang on 7/06/18.
//

#include "WaterShader.h"

WaterShader::WaterShader(){
    try {
        ShaderProgram::loadProgram(VERTEX_FILE, NULL, NULL, NULL, FRAGMENT_FILE);
    } catch (std::invalid_argument & e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        exit(0);
    }
}

void WaterShader::getAllUniformLocation() {
    try {
        uniformLocations.emplace("view", getUniformLocation("u_View"));
        uniformLocations.emplace("projection", getUniformLocation("u_Projection"));
        uniformLocations.emplace("transformation", getUniformLocation("u_Transformation"));
        uniformLocations.emplace("reflection", getUniformLocation("u_ReflectionTexture"));
        uniformLocations.emplace("refraction", getUniformLocation("u_RefractionTexture"));
        uniformLocations.emplace("dudvMap", getUniformLocation("u_DudvMap"));
        uniformLocations.emplace("moveFactor", getUniformLocation("u_MoveFactor"));
        uniformLocations.emplace("cameraPosition", getUniformLocation("u_CameraPosition"));
        uniformLocations.emplace("normalMap", getUniformLocation("u_NormalMap"));
        uniformLocations.emplace("lightColour", getUniformLocation("u_LightColour"));
        uniformLocations.emplace("lightPosition", getUniformLocation("u_LightPosition"));
        uniformLocations.emplace("depthMap", getUniformLocation("u_DepthMap"));
//        uniformLocations.emplace("nearPlane", getUniformLocation("u_NearPlane"));
//        uniformLocations.emplace("farPlane", getUniformLocation("u_FarPlane"));
    } catch (std::invalid_argument& e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        cleanUp();
        exit(0);
    }
}

void WaterShader::bindAttributes() {
    ShaderProgram::bindAttributes(0, "vert_Position");
}

void WaterShader::loadProjectionMatrix(glm::mat4 projectionMatrix) {
    loadMatrix(uniformLocations["projection"], projectionMatrix);
}

void WaterShader::loadViewMatrix(Camera *camera) {
    loadMatrix(uniformLocations["view"], camera->getViewMatrix());
    loadVec3(uniformLocations["cameraPosition"], camera->getPosition());
}

void WaterShader::loadModelMatrix(glm::mat4 modelMatrix) {
    loadMatrix(uniformLocations["transformation"], modelMatrix);
}

void WaterShader::connectTextureUnits() {
    loadint(uniformLocations["reflection"], 0);
    loadint(uniformLocations["refraction"], 1);
    loadint(uniformLocations["dudvMap"], 2);
    loadint(uniformLocations["normalMap"], 3);
    loadint(uniformLocations["depthMap"], 4);
}

void WaterShader::loadMoveFactor(float moveFactor) {
    loadFloat(uniformLocations["moveFactor"], moveFactor);
}

void WaterShader::loadLight(Light light) {
    loadVec3(uniformLocations["lightColour"], light.getColour());
    loadVec3(uniformLocations["lightPosition"], light.getPosition());
}

void WaterShader::loadProjectParams(float nearPlane, float farPlane) {
    loadFloat(uniformLocations["nearPlane"], nearPlane);
    loadFloat(uniformLocations["farPlane"], farPlane);
}





