//
// Created by Wenlong Wang on 4/06/18.
//

#include "OBJLoader.h"

RawModel _OBJLoader::loadObjModel(const char *fileName, Loader loader) {

    std::ifstream objFileStream(fileName);
    if(!objFileStream.is_open()) {
        throw "File not found!";
    }

    std::string line;
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUVs;
    std::vector<glm::vec3> tempNormals;

    std::vector<int> vertexIndices, uvIndices, normalIndices;

    while( getline(objFileStream, line) ) {
        std::string token = line.substr(0, line.find(' '));
        std::string temp;

        if( token == "v" ) {
            std::istringstream iss(line);
            glm::vec3 vertex;
            if(!(iss >> temp >> vertex.x >> vertex.y >> vertex.z)) {
                std::cerr << "Cannot read string: " << line << std::endl;
            }
            tempVertices.push_back(vertex);
        }  else if ( token == "vt" ) {
            std::istringstream iss(line);
            glm::vec2 uv;
            if(!(iss >> temp >> uv.x >> uv.y )) {
                std::cerr << "Cannot read string: " << line << std::endl;
            }
            tempUVs.push_back(uv);
        } else if ( token == "vn" ) {
            std::istringstream iss(line);
            glm::vec3 normal;
            if(!(iss >> temp >> normal.x >> normal.y >> normal.z )) {
                std::cerr << "Cannot read string: " << line << std::endl;
            }
            tempNormals.push_back(normal);
            // At this stage, all the coordinates we need has been loaded
        } else if ( token == "f" ) {
            loadFaces(line, vertexIndices, uvIndices, normalIndices);
        }

    }

    // After finish all the lines in obj file
    uvs.resize(tempVertices.size());
    normals.resize(tempVertices.size());

    for (int i = 0; i < vertexIndices.size(); ++i) {
        // -1 because the object file is 1 indexing
        int vertexIndex = vertexIndices[i] - 1;
        int normalIndex = normalIndices[i] - 1;
        int uvIndex = uvIndices[i] - 1;

        uvs[vertexIndex] = glm::vec4(tempUVs[uvIndex], 0.0f, 0.0f);
        normals[vertexIndex] = glm::vec4(tempNormals[normalIndex], 0.0f);
    }

    for (auto &tempVertex: tempVertices) {
        glm::vec4 vertex(tempVertex, 1.0f);
        vertices.push_back(vertex);
    }

    for (int i = 0; i < vertexIndices.size(); i+=3) {
        glm::ivec3 index(vertexIndices[i] - 1, vertexIndices[i+1] - 1, vertexIndices[i+2] - 1);
        indices.push_back(index);
    }



    return loader.loadToVAO(indices, vertices, uvs, normals);
}

void _OBJLoader::loadFaces(std::string line, std::vector<int> &vertexIndices, std::vector<int> &uvIndices,
                           std::vector<int> &normalIndices) {
    std::string temp;
    int vertexIndex[4] = {-1, -1, -1, -1}, uvIndex[4] = {-1, -1, -1, -1}, normalIndex[4] = {-1, -1, -1, -1};
    // This is a triangle
    if(std::count(line.begin(), line.end(), ' ') == 3) {
        std::replace(line.begin(), line.end(), '/', ' ');
        std::istringstream iss(line);
        if( !(iss >> temp >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0]
                  >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1]
                  >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2] ) ){
            std::cerr << "Cannot read string: " << line << std::endl;
        }
        for (int i = 0; i < 3; ++i) {
            vertexIndices.push_back(vertexIndex[i]);
            uvIndices.push_back(uvIndex[i]);
            normalIndices.push_back(normalIndex[i]);
        }

        // This is a rectangle
    } else if (std::count(line.begin(), line.end(), ' ') == 4) {
        std::replace(line.begin(), line.end(), '/', ' ');
        std::istringstream iss(line);
        if( !(iss >> temp >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0]
                  >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1]
                  >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2]
                  >> vertexIndex[3] >> uvIndex[3] >> normalIndex[3]) ){
            std::cerr << "Cannot read string: " << line << std::endl;
        }

        // Triangle it
        for (int i = 0; i < 2; ++i) {
            vertexIndices.push_back(vertexIndex[0]);
            uvIndices.push_back(uvIndex[0]);
            normalIndices.push_back(normalIndex[0]);

            vertexIndices.push_back(vertexIndex[1+i]);
            uvIndices.push_back(uvIndex[1+i]);
            normalIndices.push_back(normalIndex[1+i]);

            vertexIndices.push_back(vertexIndex[2+i]);
            uvIndices.push_back(uvIndex[2+i]);
            normalIndices.push_back(normalIndex[2+i]);
        }
    }
}
