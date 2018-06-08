//
// Created by Wenlong Wang on 2/06/18.
//


#include "EntityRenderer.h"
#include "MasterRenderer.h"

void EntityRenderer::render(std::map<TexturedModel, std::vector<Entity>, TexturedModelCompare> entityMap) {
    for(auto pair: entityMap){
        prepareTexturedModel(pair.first);
        std::vector<Entity> batch = pair.second;
        for(Entity entity: batch) {
            prepareInstance(entity);
            // Final render
            glDrawElements(GL_TRIANGLES, pair.first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, NULL);
        }
        unbindTexturedModel();
    }
}

EntityRenderer::EntityRenderer(StaticShader staticShader) : shader(staticShader){}



void EntityRenderer::prepareTexturedModel(TexturedModel texturedModel) {
    RawModel rawModel = texturedModel.getRawModel();
    glBindVertexArray(rawModel.getVao());
    ModelTexture modelTexture = texturedModel.getModelTexture();
    shader.loadShineVariables(modelTexture.getShineDamper(), modelTexture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.getModelTexture().getTextureID());
}

void EntityRenderer::unbindTexturedModel() {
    glBindVertexArray(0);

}

void EntityRenderer::prepareInstance(Entity entity) {
    glm::mat4 transformationMatrix = glm::translate(glm::mat4(),              entity.getPosition()) *
                                  glm::rotate(   glm::mat4(), entity.getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f)) *
                                  glm::rotate(   glm::mat4(), entity.getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f)) *
                                  glm::rotate(   glm::mat4(), entity.getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f)) *
                                  glm::scale (   glm::mat4(), glm::vec3(entity.getScale()));

    shader.loadTransformationMatrix(transformationMatrix);
}

void EntityRenderer::setProjectionMatrix(const glm::mat4 &projectionMatrix) {
    EntityRenderer::projectionMatrix = projectionMatrix;
    shader.start();
    //TODO: Projection matrix dose not work as expected, fix it
    shader.loadProjectionMatrix(projectionMatrix);
    shader.stop();
}




