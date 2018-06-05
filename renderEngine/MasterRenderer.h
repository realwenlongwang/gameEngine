//
// Created by Wenlong Wang on 5/06/18.
//

#ifndef WATERRENDERING_MASTERRENDERER_H
#define WATERRENDERING_MASTERRENDERER_H

#include <map>
#include <vector>

#include "StaticShader.h"
#include "Renderer.h"
#include "Entity.h"
#include "TexturedModel.h"
#include "Light.h"
#include "camera.h"


class MasterRenderer {
public:
    void cleanUp();
    void render(Light light, Camera* camera);
    void processEntity(Entity entity);

private:
    StaticShader shader;
    Renderer renderer = Renderer(shader);
    std::map<TexturedModel, std::vector<Entity>, TexturedModelCompare> entityMap;
};


#endif //WATERRENDERING_MASTERRENDERER_H
