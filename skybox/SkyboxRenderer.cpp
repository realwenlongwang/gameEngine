//
// Created by Wenlong Wang on 6/06/18.
//

#include "SkyboxRenderer.h"

void SkyboxRenderer::setProjectMatrix(const glm::mat4 &projectMatrix) {
    SkyboxRenderer::projectMatrix = projectMatrix;
    skyboxShader.start();
    skyboxShader.loadProjectionMatrix(projectMatrix);
    skyboxShader.stop();
}

void SkyboxRenderer::render(Skybox skybox) {
    prepareRawModel(skybox);
    glDrawElements(GL_TRIANGLES, skybox.getRawModel().getVertexCount(), GL_UNSIGNED_INT, NULL);
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(0);
}

void SkyboxRenderer::prepareRawModel(Skybox skybox) {
    RawModel rawModel = skybox.getRawModel();
    glBindVertexArray(rawModel.getVao());
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getSkyboxTexture());
}

SkyboxRenderer::SkyboxRenderer(const SkyboxShader &skyboxShader) : skyboxShader(skyboxShader) {
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

