// System Headers
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
#include "WindowManager.h"
#include "Loader.h"
#include "RawModel.h"
#include "TexturedModel.h"
#include "ModelTexture.h"
#include "Entity.h"
#include "camera.h"
#include "OBJLoader.h"
#include "Light.h"
#include "MasterRenderer.h"

// Camera
Camera *camera;
// --------------------------------------------------------------------------------
// Mouse Input
// --------------------------------------------------------------------------------
void onMouseButton(GLFWwindow *window, int button, int action, int mods) {
    // Update Camera
    camera->onMouseButton(window, button, action, mods);
}

void onCursorPosition(GLFWwindow *window, double x, double y) {
    // Update Camera
    camera->onCursorPosition(window, x, y);
}

int main() {
    // Initialise GLFW
    if (!glfwInit()) {
        // Return Error
        std::cerr << "GLFW cannot be initialised!" << std::endl;
        return -1;
    }

    WindowManager windowManager;
    GLFWwindow *window = windowManager.createWindow(600, 600, "Water rendering", 3, 2);

    // Set mouse input callback functions
    glfwSetMouseButtonCallback(window, onMouseButton);
    glfwSetCursorPosCallback(window, onCursorPosition);


    Loader loader;
    _OBJLoader objLoader;

    camera = new GimbalFreeLookCamera(window);
    // ----------------------------------------
    // Initialise OpenGL
    // ----------------------------------------
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);


    // ----------------------------------------
    // Create object
    // ----------------------------------------
    std::vector<glm::vec4> positionBuffer;
    std::vector<glm::vec4> texturedBuffer;
    std::vector<glm::ivec3> indices;


    RawModel rawModel = objLoader.loadObjModel("res/dragon.obj", loader);
    ModelTexture modelTexture(loader.loadTexture("res/brick_diff.tga"));
    modelTexture.setReflectivity(1);
    modelTexture.setShineDamper(10);
    TexturedModel texturedModel(rawModel, modelTexture);
    Entity entity(texturedModel, glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), 1);
    Light light(glm::vec3(0, 0, 20), glm::vec3(1));

    MasterRenderer masterRenderer;

    float time = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        // Make the context of the given window current on the calling thread
        glfwMakeContextCurrent(window);

        // Update Time
        float current_time = glfwGetTime();
        float dt = current_time - time;
        time = current_time;

//        entity.increaseRotation(0, dt, 0);

        camera->update(dt);

        masterRenderer.processEntity(entity);
        masterRenderer.render(light, camera);

        // Swap the back and front buffers
        glfwSwapBuffers(window);

        // Poll window events
        glfwPollEvents();
    }

    masterRenderer.cleanUp();
    loader.cleanUp();
    windowManager.cleanUp();
    // Terminate GLFW
    glfwTerminate();
}