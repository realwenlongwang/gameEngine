//
// Created by Wenlong Wang on 2/06/18.
//

#include "Loader.h"


RawModel
Loader::loadToVAO(std::vector<glm::ivec3> indices, std::vector<glm::vec4> vertices, std::vector<glm::vec4> uvs,
                  std::vector<glm::vec4> normals) {
    GLuint vao = initialiseVAO();
    bindIndicesBuffer(indices);
    bindVerticesBuffer(vertices, 0);
    bindVerticesBuffer(uvs, 1);
    bindVerticesBuffer(normals, 2);
    unbindObjects();
    return {vao, indices.size() * 3};
}

GLuint Loader::initialiseVAO() {
    GLuint vao = 0;
    // Create VAO
    glGenVertexArrays(1, &vao);
    // Store the VAO
    vaos.push_back(vao);
    // Bind VAO
    glBindVertexArray(vao);

    return vao;
}

void Loader::bindIndicesBuffer(std::vector<glm::ivec3> indices) {
    GLuint ebo = 0;
    // Create EBO
    glGenBuffers(1, &ebo);
    // Store the EBO
    ebos.push_back(ebo);
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // Load Element Data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::ivec3), indices.data(), GL_STATIC_DRAW);
}

void Loader::bindVerticesBuffer(std::vector<glm::vec4> vertices, GLuint attributeLocation) {
    GLuint vbo = 0;
    // Create VBO
    glGenBuffers(1, &vbo);
    // Store the VBO
    vbos.push_back(vbo);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Load vertex data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), vertices.data(), GL_STATIC_DRAW);
    // Set vertex attribute pointers
    glVertexAttribPointer(attributeLocation, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    // Enable vertex attribute arrays
    glEnableVertexAttribArray(attributeLocation);

}

void Loader::unbindObjects() {
    glBindVertexArray(0);
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Loader::cleanUp() {
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
    glDeleteBuffers(ebos.size(), ebos.data());
    glDeleteTextures(textures.size(), textures.data());
}

GLuint Loader::loadTexture(const char *fileName) {
    int width, height, channel;
    GLuint texture = 0;
    texture = image::loadTexture2D(fileName, width, height, channel);
    textures.push_back(texture);
    return texture;
}

GLuint Loader::loadCubeMap(const char **fileNames) {
    int width, height, channel;
    GLuint cubeMap = 0;
    cubeMap = image::loadTextureCubeMap(fileNames, width, height, channel);
    textures.push_back(cubeMap);
    return cubeMap;
}





