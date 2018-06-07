//
// Created by Wenlong Wang on 6/06/18.
//

#include "SkyboxShader.h"

void SkyboxShader::bindAttributes() {
    ShaderProgram::bindAttributes(0, "vert_Position");
}

SkyboxShader::SkyboxShader() {
    try {
        ShaderProgram::loadProgram(VERTEX_FILE, NULL, NULL, NULL, FRAGMENT_FILE);
    } catch (std::invalid_argument & e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        exit(0);
    }
}

void SkyboxShader::getAllUniformLocation() {
    try {
        uniformLocations.emplace("view", getUniformLocation("u_View"));
        uniformLocations.emplace("projection", getUniformLocation("u_Projection"));
    } catch (std::invalid_argument& e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        cleanUp();
        exit(0);
    }

}

void SkyboxShader::loadProjectionMatrix(glm::mat4 projectionMatrix) {
    loadMatrix(uniformLocations["projection"], projectionMatrix);
}

void SkyboxShader::loadViewMatrix(glm::mat4 viewMatrix) {
    loadMatrix(uniformLocations["view"], viewMatrix);
}

