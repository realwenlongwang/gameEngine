//
// Created by Wenlong Wang on 2/06/18.
//

#include "WindowManager.h"

void WindowManager::prepare() {
    // Set Error Callback
    glfwSetErrorCallback(onError);

    // Set GLFW Window Hint - Full-Screen Antialiasing 16x
    glfwWindowHint(GLFW_SAMPLES, 16);

}

GLFWwindow* WindowManager::createWindow(int width, int height, const char *title, int major, int minor, GLFWmonitor *monitor,
                                        GLFWwindow *share) {
    prepare();
    GLFWwindow *window = utils::createWindow(width, height, title, major, minor, monitor, share);
    if(window == nullptr) {
        throw "create window or context failed!";
    }
    windows.push_back(window);
    // Anti aliasing
    glEnable(GL_MULTISAMPLE);

    setUpCallbacks(window);

    return window;
}

// Called on Error Event
void onError(int error, const char *description) {
    // Throw Error message
    throw description;
}

// Called on Window Close Event
void onWindowClose(GLFWwindow *window) {
    // Nothing to do right now
    // Do not call glfwDestroyWindow from here
}

// Called on Window Size Event
void onFrameBufferSize(GLFWwindow *window, int width, int height) {
    // Set-up the window/screen coordinates
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(nullptr);
}


void WindowManager::setUpCallbacks(GLFWwindow* window) {
    // Set window callback functions
    glfwSetFramebufferSizeCallback(window, onFrameBufferSize);
    glfwSetWindowCloseCallback(window, onWindowClose);
}

void WindowManager::cleanUp() {
    for(GLFWwindow* window: windows) {
        // Stop receiving events for the window and free resources; this must be
        // called from the main thread and should not be invoked from a callback
        glfwDestroyWindow(window);
    }

}

