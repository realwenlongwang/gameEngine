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
#include "WaterFrameBuffers.h"
#include "WaterRenderer.h"
#include "GuiRenderer.h"


// Camera
Camera *camera, *invertedPitchCamera;
// --------------------------------------------------------------------------------
// Mouse Input
// --------------------------------------------------------------------------------
void onMouseButton(GLFWwindow *window, int button, int action, int mods) {
    // Update Camera
    camera->onMouseButton(window, button, action, mods);
    invertedPitchCamera->onMouseButton(window, button, action, mods);
}

void onCursorPosition(GLFWwindow *window, double x, double y) {
    // Update Camera
    camera->onCursorPosition(window, x, y);
    invertedPitchCamera->onCursorPosition(window, x, y);
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
    invertedPitchCamera = new GimbalFreeLookCamera(window);
    invertedPitchCamera->setInvertPitch(true);
    // ----------------------------------------
    // Initialise OpenGL
    // ----------------------------------------
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // ----------------------------------------
    // Create object
    // ----------------------------------------
    RawModel rawModel = objLoader.loadObjModel("res/dragon.obj", loader);
    ModelTexture modelTexture(loader.loadTexture("res/brick_diff.tga"));
    modelTexture.setReflectivity(1);
    modelTexture.setShineDamper(10);
    TexturedModel texturedModel(rawModel, modelTexture);
    Entity entity(texturedModel, glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), 1);
    Terrain terrain(-0.1f, -0.1f, loader, ModelTexture(loader.loadTerrainTexture("res/grass.jpg")));
    WaterShader waterShader;
    Water waterTile(1, 0, -5);



    // Container
    std::vector<Entity> entities;
    std::vector<Terrain> terrains;
    std::vector<Water> water;

    entities.push_back(entity);
    terrains.push_back(terrain);
    water.push_back(waterTile);

    WaterFrameBuffers waterFrameBuffers;

    Light sun(glm::vec3(-50, 50, -50), glm::vec3(1));

    // ----------------------------------------
    // Create GUI
    // ----------------------------------------
    std::vector<GuiTexture> guiTextures;
    GuiTexture gui0(waterFrameBuffers.getReflectionTexture(), glm::vec2(-0.5f, 0.5f), glm::vec2(0.25f, 0.25f));
    GuiTexture gui1(waterFrameBuffers.getRefractionTexture(), glm::vec2(0.5f, 0.5f), glm::vec2(0.25f, 0.25f));
    guiTextures.push_back(gui0);
    guiTextures.push_back(gui1);

    MasterRenderer masterRenderer(loader);
    GuiRenderer guiRenderer(loader);
    WaterRenderer waterRenderer(loader, waterShader, waterFrameBuffers);
    waterRenderer.setProjectionMatrix(masterRenderer.getProjectionMatrix());

    float time = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        // Make the context of the given window current on the calling thread
        glfwMakeContextCurrent(window);
        // Update Time
        float current_time = glfwGetTime();
        float dt = current_time - time;
        time = current_time;

        // Enable the clip planes
        glEnable(GL_CLIP_DISTANCE0);

//        entity.increaseRotation(0, dt, 0);

        waterFrameBuffers.bindReflectionFrameBuffer();
        //TODO: Two cameras are used here, can we make it one.
        glm::vec3 originalPosition = camera->getPosition();
        float distance = 2 * (originalPosition.y - waterTile.getHeight());
        invertedPitchCamera->setPosition(glm::vec3(originalPosition.x, originalPosition.y - distance, originalPosition.z));
        masterRenderer.renderScene(entities, terrains, sun, invertedPitchCamera, glm::vec4(0, 1, 0, -waterTile.getHeight()));


        waterFrameBuffers.bindRefractionFrameBuffer();
        masterRenderer.renderScene(entities, terrains, sun, camera, glm::vec4(0, -1, 0, waterTile.getHeight()));
        waterFrameBuffers.unbindCurrentFrameBuffer();
        glDisable(GL_CLIP_DISTANCE0);

        invertedPitchCamera->update(dt);
        camera->update(dt);
        masterRenderer.renderScene(entities, terrains, sun, camera, glm::vec4(0, -1, 0, 1000));
        waterRenderer.render(water, camera, sun);

        guiRenderer.render(guiTextures);
        // Swap the back and front buffers
        glfwSwapBuffers(window);

        // Poll window events
        glfwPollEvents();

    }
    guiRenderer.cleanUp();
    waterShader.cleanUp();
    waterFrameBuffers.cleanUp();
    masterRenderer.cleanUp();
    loader.cleanUp();
    windowManager.cleanUp();
    // Terminate GLFW
    glfwTerminate();
}