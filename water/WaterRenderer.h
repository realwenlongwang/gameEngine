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
// TODO: Consider move it to the master renderer later
class WaterRenderer {

public:
    WaterRenderer(Loader loader, const WaterShader &waterShader);

    void setProjectionMatrix(const glm::mat4 &projectionMatrix);
    void render(std::vector<Water> water, Camera *camera);
private:
    RawModel quad = RawModel(0, 0);
    WaterShader waterShader;
    glm::mat4 projectionMatrix;

    void setUpVAO(Loader loader);

    void prepareRender(Camera *pCamera);

    void unbind();
};


#endif //WATERRENDERING_WATERRN_H
