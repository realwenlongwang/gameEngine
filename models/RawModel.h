//
// Created by Wenlong Wang on 3/06/18.
//

#ifndef WATERRENDERING_RAWMODEL_H
#define WATERRENDERING_RAWMODEL_H


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

class RawModel {
public:
    RawModel(GLuint vao, unsigned long vertexCount);

    GLuint getVao() const;

    GLsizei getVertexCount() const;

private:
    GLuint vao;
    GLsizei vertexCount;
};


#endif //WATERRENDERING_RAWMODEL_H
