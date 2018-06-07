//
// Created by Wenlong Wang on 3/06/18.
//

#ifndef WATERRENDERING_SHADERPROGRAM_H
#define WATERRENDERING_SHADERPROGRAM_H


// System Headers
#include <iostream>
#include <fstream>
#include <map>

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
#include <OpenGL/OpenGL.h>
#endif

// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Exception.h"

class ShaderProgram {

public:
    virtual ~ShaderProgram();

    void start();
    void stop();
    void cleanUp();
    GLint getAttributeLocation(const char *attributeName);
    GLint getUniformLocation(const char *uniformName);

protected:
    GLuint programID;

    virtual void getAllUniformLocation() = 0;
    virtual void bindAttributes()=0;
    void bindAttributes(GLuint attributeNum, const char *attributeName);
    // Load and compiler program from source files
    void loadProgram(const char *vert_file, const char *ctrl_file, const char *eval_file, const char *geom_file,
                     const char *frag_file);
    void loadFloat(GLint location, float value);
    void loadVec3(GLint location, glm::vec3 value);
    void loadVec4(GLint location, glm::vec4 value);
    void loadBoolean(GLint location, bool value);
    void loadMatrix(GLint location, glm::mat4 matrix);
private:
    std::map<const char*, GLuint> shaders;

// Read file contents
    char* readFile(const char *filename);

// Check the status of a shader
    GLuint checkShader(GLuint shader);

// Check the status of a program
    GLuint checkProgram(GLuint program);

// Load and compile shader from source file
    GLuint loadShader(GLuint type, const char *filename);

};


#endif //WATERRENDERING_SHADERPROGRAM_H
