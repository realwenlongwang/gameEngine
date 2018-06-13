//
// Created by Wenlong Wang on 5/06/18.
//

#include "Terrain.h"
#include <utility>

Terrain::Terrain(float gridX, float gridZ, Loader loader, const ModelTexture &texture)
        : texture(texture) {
    x = gridX * SIZE;
    z = gridZ * SIZE;
    rawModel = generateTerrain(std::move(loader));
}

RawModel Terrain::generateTerrain(Loader loader) {

    std::vector<glm::vec4> vertices, normals, uvs;

    std::vector<glm::ivec3> indices;

    int vertexPointer = 0;
    for(int i=0;i<VERTEX_COUNT;i++){
        for(int j=0;j<VERTEX_COUNT;j++){
            glm::vec4 vertex((float)j/((float)VERTEX_COUNT - 1) * SIZE, 0, (float)i/((float)VERTEX_COUNT - 1) * SIZE, 1);
            vertices.push_back(vertex);
            glm::vec4 normal(0, 1, 0, 0);
            normals.push_back(normal);
            glm::vec4 uv((float)j/((float)VERTEX_COUNT - 1), (float)i/((float)VERTEX_COUNT - 1), 0, 0);
            uvs.push_back(uv);
            vertexPointer++;
        }
    }

    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            int bottomRight = bottomLeft + 1;
            glm::ivec3 firstTriangle(topLeft, bottomLeft, topRight);
            indices.push_back(firstTriangle);
            glm::ivec3 secondTriangle(topRight, bottomLeft, bottomRight);
            indices.push_back(secondTriangle);
        }
    }
    return loader.loadToVAO(indices, vertices, uvs, normals);
}

float Terrain::getX() const {
    return x;
}

float Terrain::getZ() const {
    return z;
}

const RawModel &Terrain::getRawModel() const {
    return rawModel;
}

const ModelTexture &Terrain::getTexture() const {
    return texture;
}
