//
// Created by Wenlong Wang on 6/06/18.
//

#ifndef WATERRENDERING_WATERFRAMEBUFFERS_H
#define WATERRENDERING_WATERFRAMEBUFFERS_H


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

class WaterFrameBuffers {

public:
    WaterFrameBuffers();
    void cleanUp();
    GLuint getReflectionTexture() const;

    GLuint getRefractionTexture() const;

    GLuint getRefractionDepthTexture() const;

    void bindReflectionFrameBuffer();
    void bindRefractionFrameBuffer();
    void unbindCurrentFrameBuffer();
protected:
    const int REFLECTION_WIDTH = 320;
    const int REFRACTION_WIDTH = 1280;

private:
    const int REFLECTION_HEIGHT = 180;
    const int REFRACTION_HEIGHT = 720;

    GLuint reflectionFrameBuffer;
    GLuint reflectionTexture;
    GLuint reflectionDepthBuffer;

    GLuint refractionFrameBuffer;
    GLuint refractionTexture;
    GLuint refractionDepthTexture;

    void initialiseReflectionFrameBuffer();

    void initialiseRefractionFrameBuffer();

    GLuint createFrameBuffer();

    GLuint createTextureAttachment(const int width, const int height);

    GLuint createDepthBufferAttachment(const int width, const int height);

    GLuint createDepthTextureAttachment(const int width, const int height);

    void bindFrameBuffer(GLuint frameBuffer, int width, int height);
};


#endif //WATERRENDERING_WATERFRAMEBUFFERS_H
