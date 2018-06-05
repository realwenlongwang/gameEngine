//
// Created by Wenlong Wang on 5/06/18.
//

#include <TexturedModel.h>
#include <Entity.h>
#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(const TerrainShader &terrainShader) : terrainShader(terrainShader) {}

void TerrainRenderer::setProjectionMatrix(const glm::mat4 &projectionMatrix) {
    TerrainRenderer::projectionMatrix = projectionMatrix;
    terrainShader.start();
    terrainShader.loadProjectionMatrix(projectionMatrix);
    terrainShader.stop();
}

void TerrainRenderer::render(std::vector<Terrain> terrains) {
    for(Terrain terrain: terrains) {
        prepareTexturedModel(terrain);
        loadTranslationMatrix(terrain);
        
        glDrawElements(GL_TRIANGLES, terrain.getRawModel().getVertexCount(), GL_UNSIGNED_INT, NULL);
        unbindTexturedModel();
    }

}

void TerrainRenderer::prepareTexturedModel(Terrain terrain) {
    RawModel rawModel = terrain.getRawModel();
    glBindVertexArray(rawModel.getVao());
    ModelTexture modelTexture = terrain.getTexture();
    terrainShader.loadShineVariables(modelTexture.getShineDamper(), modelTexture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, modelTexture.getTextureID());
}

void TerrainRenderer::unbindTexturedModel() {
    glBindVertexArray(0);

}

void TerrainRenderer::loadTranslationMatrix(Terrain terrain) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(), glm::vec3(terrain.getX(), 0, terrain.getZ()));
    terrainShader.loadTransformationMatrix(translationMatrix);
}
