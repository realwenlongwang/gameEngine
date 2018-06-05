//
// Created by Wenlong Wang on 2/06/18.
//

#ifndef WATERRENDERING_RENDERER_H
#define WATERRENDERING_RENDERER_H

#include <map>
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
#include "RawModel.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"

class Renderer {
public:
    void render(std::map<TexturedModel, std::vector<Entity>, TexturedModelCompare> entityMap);
    void prepare();
    Renderer(StaticShader staticShader);
private:
    float FIELD_OF_VIEW = 67.0f;
    float NEAR_PLANE = 0.2f;
    float FAR_PLANE = 50.0f;
    glm::mat4 projectionMatrix;
    StaticShader shader;

    void initProjectionMatrix();
    void prepareTexturedModel(TexturedModel texturedModel);
    void unbindTexturedModel();
    void prepareInstance(Entity entity);
};


#endif //WATERRENDERING_RENDERER_H
