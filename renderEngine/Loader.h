//
// Created by Wenlong Wang on 2/06/18.
//

#ifndef WATERRENDERING_LOADER_H
#define WATERRENDERING_LOADER_H

// System Header
#include <vector>

// OpenGL Headers
#if defined(_WIN32)
#include <GL/glew.h>
	#if defined(GLEW_EGL)
		#include <GL/eglew.h>
	#elif defined(GLEW_OSMESA)
		#define GLAPI extern
		#include <GL/osmesa.h>
	#elif defined(_WIN32)
		#include <GL/wglew.h>
	#elif !defined(__APPLE__) && !defined(__HAIKU__) || defined(GLEW_APPLE_GLX)
		#include <GL/glxew.h>
	#endif

	// OpenGL Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Project Headers
#include "image.h"
#include "RawModel.h"


class Loader {
public:
    RawModel loadToVAO(std::vector<glm::ivec3> indices, std::vector<glm::vec4> vertices, std::vector<glm::vec4> uvs,
                           std::vector<glm::vec4> normals);
    GLuint loadTexture(const char* fileName);
    GLuint loadTerrainTexture(const char* fileName);
    GLuint loadCubeMap(const char* fileNames[6]);

    void cleanUp();
private:
    // ----------------------------------------
    // Vertex Array Object
    // ----------------------------------------
    // Vertex Array Objects (VAO)
    std::vector<GLuint> vaos;
    // Vertex Buffer Objects (VBO)
    std::vector<GLuint> vbos;
    // Element Buffer Objects (EBO)
    std::vector<GLuint> ebos;
    // Textures
    std::vector<GLuint> textures;

    GLuint initialiseVAO();
    void bindIndicesBuffer(std::vector<glm::ivec3> indices);
    void bindVerticesBuffer(std::vector<glm::vec4> vertices, GLuint attributeLocation);
    void unbindObjects();
};


#endif //WATERRENDERING_LOADER_H
