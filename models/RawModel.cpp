//
// Created by Wenlong Wang on 3/06/18.
//

#include "RawModel.h"

RawModel::RawModel(GLuint vao, unsigned long vertexCount) : vao(vao), vertexCount(vertexCount) {}

GLuint RawModel::getVao() const {
    return vao;
}

unsigned long RawModel::getVertexCount() const {
    return vertexCount;
}
