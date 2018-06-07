//
// Created by Wenlong Wang on 6/06/18.
//


#include "Skybox.h"

RawModel Skybox::generateSkybox(Loader loader) {

    std::vector<glm::vec4> vertices;
    std::vector<glm::ivec3> indices;

    // Vertices
    vertices.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f)); // Left  - Top    - Back  - 0
    vertices.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f)); // Right - Top    - Back  - 1
    vertices.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f)); // Left  - Top    - Front - 2
    vertices.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f)); // Right - Top    - Front - 3
    vertices.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f)); // Left  - Bottom - Back  - 4
    vertices.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f)); // Right - Bottom - Back  - 5
    vertices.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f)); // Left  - Bottom - Front - 6
    vertices.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f)); // Right - Bottom - Front - 7

    // Indexes
    indices.push_back(glm::ivec3(0, 3, 2)); // Top
    indices.push_back(glm::ivec3(0, 1, 3));
    indices.push_back(glm::ivec3(4, 7, 5)); // Bottom
    indices.push_back(glm::ivec3(4, 6, 7));
    indices.push_back(glm::ivec3(0, 2, 6)); // Left
    indices.push_back(glm::ivec3(0, 6, 4));
    indices.push_back(glm::ivec3(3, 1, 5)); // Right
    indices.push_back(glm::ivec3(3, 5, 7));
    indices.push_back(glm::ivec3(2, 3, 7)); // Front
    indices.push_back(glm::ivec3(2, 7, 6));
    indices.push_back(glm::ivec3(1, 0, 4)); // Back
    indices.push_back(glm::ivec3(1, 4, 5));

    return loader.loadToVAO(indices, vertices);
}

Skybox::Skybox(Loader loader) {
    skyboxTexture = loader.loadCubeMap(filenames);
    rawModel = generateSkybox(loader);
}

const RawModel &Skybox::getRawModel() const {
    return rawModel;
}

GLuint Skybox::getSkyboxTexture() const {
    return skyboxTexture;
}
