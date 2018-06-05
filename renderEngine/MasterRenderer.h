//
// Created by Wenlong Wang on 5/06/18.
//

#ifndef WATERRENDERING_MASTERRENDERER_H
#define WATERRENDERING_MASTERRENDERER_H

#include <map>
#include <vector>

#include "StaticShader.h"
#include "EntityRenderer.h"
#include "Entity.h"
#include "TexturedModel.h"
#include "Light.h"
#include "camera.h"
#include "TerrainRenderer.h"


class MasterRenderer {
public:
    void cleanUp();
    void render(Light light, Camera* camera);
    void processEntity(Entity entity);
    void processTerrain(Terrain terrain);

    MasterRenderer();

private:
    float FIELD_OF_VIEW = 67.0f;
    float NEAR_PLANE = 0.2f;
    float FAR_PLANE = 50.0f;
    glm::mat4 projectionMatrix;

    StaticShader staticShader;
    TerrainShader terrainShader;
    EntityRenderer entityRenderer;
    TerrainRenderer terrainRenderer;
    std::map<TexturedModel, std::vector<Entity>, TexturedModelCompare> entityMap;
    std::vector<Terrain> terrains;
    void initProjectionMatrix();
    void prepare();
};


#endif //WATERRENDERING_MASTERRENDERER_H
