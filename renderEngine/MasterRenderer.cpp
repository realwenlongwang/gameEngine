//
// Created by Wenlong Wang on 5/06/18.
//

#include "EntityRenderer.h"
#include "MasterRenderer.h"

void MasterRenderer::cleanUp() {
    staticShader.cleanUp();
    terrainShader.cleanUp();
}

void MasterRenderer::render(Light light, Camera *camera) {
    prepare();
    staticShader.start();
    staticShader.loadLight(light);
    staticShader.loadViewMatrix(camera->getViewMatrix());
    entityRenderer.render(entityMap);
    staticShader.stop();
    entityMap.clear();
    terrainShader.start();
    terrainShader.loadLight(light);
    terrainShader.loadViewMatrix(camera->getViewMatrix());
    terrainRenderer.render(terrains);
    terrainShader.stop();
    terrains.clear();
}

void MasterRenderer::processEntity(Entity entity) {
    const TexturedModel texturedEntity = entity.getTexturedModel();
    std::vector<Entity> batch = entityMap[texturedEntity];
    if(!batch.empty()) {
        batch.push_back(entity);
    } else {
        std::vector<Entity> newBatch;
        entityMap.emplace(texturedEntity, newBatch);
        entityMap[texturedEntity].push_back(entity);
    }
}

void MasterRenderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    // Set clear (background) colour to black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Clear Screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::initProjectionMatrix() {
    // Calculate Perspective Projection
    projectionMatrix = glm::perspective(glm::radians(FIELD_OF_VIEW), 1.0f, NEAR_PLANE, FAR_PLANE);
}

MasterRenderer::MasterRenderer(): entityRenderer(staticShader), terrainRenderer(terrainShader) {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BACK);
    initProjectionMatrix();
    entityRenderer.setProjectionMatrix(projectionMatrix);
    terrainRenderer.setProjectionMatrix(projectionMatrix);
}

void MasterRenderer::processTerrain(Terrain terrain) {
    terrains.push_back(terrain);
}
