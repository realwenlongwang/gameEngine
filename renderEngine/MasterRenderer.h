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
#include "SkyboxRenderer.h"


class MasterRenderer {
public:
    void cleanUp();
    void renderScene(std::vector<Entity> entities, std::vector<Terrain> terrains, Light light,
                     Camera *camera, glm::vec4 clipPlane);
    void render(Light light, Camera *camera, glm::vec4 clipPlane);
    void processEntity(Entity entity);
    void processTerrain(Terrain terrain);

    const glm::mat4 &getProjectionMatrix() const;

    MasterRenderer(const Loader &loader);

private:
    float FIELD_OF_VIEW = 67.0f;
    float NEAR_PLANE = 0.2f;
    float FAR_PLANE = 100.0f;
    glm::mat4 projectionMatrix;

    StaticShader staticShader;
    TerrainShader terrainShader;
    SkyboxShader skyboxShader;
    EntityRenderer entityRenderer;
    TerrainRenderer terrainRenderer;
    SkyboxRenderer skyboxRenderer;

    std::map<TexturedModel, std::vector<Entity>, TexturedModelCompare> entityMap;
    std::vector<Terrain> terrains;
    Skybox skybox;
    void initProjectionMatrix();
    void prepare();
};


#endif //WATERRENDERING_MASTERRENDERER_H
