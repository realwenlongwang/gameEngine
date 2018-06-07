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
}

void WaterShader::loadModelMatrix(glm::mat4 modelMatrix) {
    loadMatrix(uniformLocations["transformation"], modelMatrix);
}


