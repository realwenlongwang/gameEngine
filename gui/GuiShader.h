//
// Created by Wenlong Wang on 7/06/18.
//

#ifndef WATERRENDERING_GUISHADER_H
#define WATERRENDERING_GUISHADER_H

#include "ShaderProgram.h"

class GuiShader: public ShaderProgram {
public:
    GuiShader();
    void loadTransformationMatrix(glm::mat4 transformationMatrix);

protected:
    void getAllUniformLocation() override;

    void bindAttributes() override;

private:
    const char* VERTEX_FILE = "shaders/gui.vert.glsl";
    const char* FRAGMENT_FILE = "shaders/gui.frag.glsl";

    GLint location_transformationMatrix;


};


#endif //WATERRENDERING_GUISHADER_H
