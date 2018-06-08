//
// Created by Wenlong Wang on 7/06/18.
//

#include "GuiShader.h"

GuiShader::GuiShader() {
    try {
        ShaderProgram::loadProgram(VERTEX_FILE, NULL, NULL, NULL, FRAGMENT_FILE);
    } catch (std::invalid_argument & e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        exit(0);
    }
}

void GuiShader::loadTransformationMatrix(glm::mat4 transformationMatrix) {
    loadMatrix(location_transformationMatrix, transformationMatrix);
}

void GuiShader::getAllUniformLocation() {
    try {
        location_transformationMatrix = getUniformLocation("u_Transformation");
    } catch (std::invalid_argument& e) {
        std::cerr << __PRETTY_FUNCTION__ << ": Catch the exception" << std::endl;
        std::cerr << e.what() << std::endl;
        cleanUp();
        exit(0);
    }

}

void GuiShader::bindAttributes() {
    ShaderProgram::bindAttributes(0, "vert_Position");
}




