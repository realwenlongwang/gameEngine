//
// Created by Wenlong Wang on 2/06/18.
//


#include "Renderer.h"

void Renderer::render(std::map<TexturedModel, std::vector<Entity>, TexturedModelCompare> entityMap) {
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

void Renderer::initProjectionMatrix() {
    // Calculate Perspective Projection
    projectionMatrix = glm::perspective(glm::radians(FIELD_OF_VIEW), 1.0f, NEAR_PLANE, FAR_PLANE);
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    // Set clear (background) colour to black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Clear Screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer::Renderer(StaticShader staticShader): shader(staticShader) {

    glEnable(GL_CULL_FACE);
    glEnable(GL_BACK);
    initProjectionMatrix();
    staticShader.start();
    //TODO: Projection matrix dose not work as expected, fix it
    staticShader.loadProjectionMatrix(projectionMatrix);
    staticShader.stop();
}

void Renderer::prepareTexturedModel(TexturedModel texturedModel) {
    RawModel rawModel = texturedModel.getRawModel();
    glBindVertexArray(rawModel.getVao());
    ModelTexture modelTexture = texturedModel.getModelTexture();
    shader.loadShineVaribles(modelTexture.getShineDamper(), modelTexture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.getModelTexture().getTextureID());
}

void Renderer::unbindTexturedModel() {
    glBindVertexArray(0);

}

void Renderer::prepareInstance(Entity entity) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(),              entity.getPosition()) *
                                  glm::rotate(   glm::mat4(), entity.getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f)) *
                                  glm::rotate(   glm::mat4(), entity.getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f)) *
                                  glm::rotate(   glm::mat4(), entity.getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f)) *
                                  glm::scale (   glm::mat4(), glm::vec3(entity.getScale()));

    shader.loadTransformationMatrix(translationMatrix);
}




