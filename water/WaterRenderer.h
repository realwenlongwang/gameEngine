//
// Created by Wenlong Wang on 7/06/18.
//

#ifndef WATERRENDERING_WATERENDERER_H
#define WATERRENDERING_WATERENDERER_H

#include <utility>
#include "Loader.h"
#include "RawModel.h"
#include "WaterShader.h"
#include "Water.h"
#include "WaterFrameBuffers.h"
// TODO: Consider move it to the master renderer later
class WaterRenderer {

public:
    WaterRenderer(Loader loader, const WaterShader &waterShader, WaterFrameBuffers waterFrameBuffers);

    void setProjectionMatrix(const glm::mat4 &projectionMatrix);
    void render(std::vector<Water> water, Camera *camera);
private:
    const char* DUDV_MAP = "res/waterDUDV.png";
    const float WAVE_SPEED = 0.03f;

    float moveFactor = 0.0f;

    GLuint dudvTexture;
    RawModel quad = RawModel(0, 0);
    WaterShader waterShader;
    glm::mat4 projectionMatrix;
    WaterFrameBuffers waterFrameBuffers;

    void setUpVAO(Loader loader);

    void prepareRender(Camera *pCamera);

    void unbind();
};


#endif //WATERRENDERING_WATERRN_H
