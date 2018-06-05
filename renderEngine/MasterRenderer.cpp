//
// Created by Wenlong Wang on 5/06/18.
//

#include "MasterRenderer.h"

void MasterRenderer::cleanUp() {
    shader.cleanUp();
}

void MasterRenderer::render(Light light, Camera *camera) {
    renderer.prepare();
    shader.start();
    shader.loadLight(light);
    shader.loadViewMatrix(camera->getViewMatrix());
    renderer.render(entityMap);
    shader.stop();
    entityMap.clear();
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
