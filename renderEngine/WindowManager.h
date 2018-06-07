//
// Created by Wenlong Wang on 2/06/18.
//

#ifndef WATERRENDERING_WINDOWMANAGER_H
#define WATERRENDERING_WINDOWMANAGER_H

#include <vector>
#include "utils.h"

class WindowManager {
public:
    GLFWwindow* createWindow(int width, int height, const char *title, int major = 3, int minor = 2, GLFWmonitor *monitor = nullptr,
                      GLFWwindow *share = nullptr);

    void cleanUp();

private:
    int width;
    int height;
    std::vector<GLFWwindow*> windows;

    void prepare();

    void setUpCallbacks(GLFWwindow* window);

};

// --------------------------------------------------------------------------------
// GLFW Callbacks
// --------------------------------------------------------------------------------

void onError(int error, const char *description);

void onWindowClose(GLFWwindow *window);

void onFrameBufferSize(GLFWwindow *window, int width, int height);


#endif //WATERRENDERING_WINDOWMANAGER_H
