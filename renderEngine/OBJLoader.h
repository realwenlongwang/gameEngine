//
// Created by Wenlong Wang on 4/06/18.
//

#ifndef WATERRENDERING_OBJLOADER_H
#define WATERRENDERING_OBJLOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "RawModel.h"
#include "Loader.h"
#include "ShaderProgram.h"

class _OBJLoader {
public:
    RawModel loadObjModel(const char *fileName, Loader loader);

private:
    std::vector<glm::ivec3> indices;
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec4> uvs;
    std::vector<glm::vec4> normals;
    void loadFaces(std::string line,
                   std::vector<int> &vertexIndices,
                   std::vector<int> &uvIndices,
                   std::vector<int> &normalIndices);

};


#endif //WATERRENDERING_OBJLOADER_H
