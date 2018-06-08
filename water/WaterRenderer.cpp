//
// Created by Wenlong Wang on 7/06/18.
//

#include "WaterRenderer.h"


WaterRenderer::WaterRenderer(Loader loader, const WaterShader &waterShader, WaterFrameBuffers waterFrameBuffers)
        : waterShader(waterShader), waterFrameBuffers(waterFrameBuffers) {
    dudvTexture = loader.loadTexture(DUDV_MAP);
    setUpVAO(std::move(loader));
}

void WaterRenderer::setUpVAO(Loader loader) {
    // Only has x, z coordinates, y set to 0 in shader
    std::vector<glm::vec4> vertices{glm::vec4(-1, 0, -1, 1), glm::vec4(-1, 0, 1, 1), glm::vec4(1, 0, -1, 1), glm::vec4(1, 0, 1, 1)};
    std::vector<glm::ivec3> indices{glm::ivec3(0, 1, 2), glm::ivec3(2, 1, 3)};
    quad = loader.loadToVAO(indices, vertices);

}

void WaterRenderer::setProjectionMatrix(const glm::mat4 &projectionMatrix) {
    WaterRenderer::projectionMatrix = projectionMatrix;
    waterShader.start();
    waterShader.connectTextureUnits();
    waterShader.loadProjectionMatrix(projectionMatrix);
    waterShader.stop();
}

void WaterRenderer::render(std::vector<Water> water, Camera *camera) {
    prepareRender(camera);
    for(Water waterTile: water) {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(), glm::vec3(waterTile.getX(), waterTile.getHeight(), waterTile.getZ())) *
                                      glm::scale (   glm::mat4(), glm::vec3(waterTile.TILE_SIZE));
        waterShader.loadModelMatrix(translationMatrix);
        glDrawElements(GL_TRIANGLES, quad.getVertexCount(), GL_UNSIGNED_INT, nullptr);
    }
    unbind();
}

void WaterRenderer::prepareRender(Camera *pCamera) {
    waterShader.start();
    waterShader.loadViewMatrix(pCamera);
    moveFactor = sin(WAVE_SPEED * glfwGetTime());
//    std::cout << moveFactor << std::endl;
//    if(moveFactor > 1.0f) moveFactor = 0.0f;
    // TODO: move factor doesn't work properly
    waterShader.loadMoveFactor(moveFactor);
    glBindVertexArray(quad.getVao());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, waterFrameBuffers.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, waterFrameBuffers.getRefractionTexture());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, dudvTexture);
}

void WaterRenderer::unbind() {
    glBindVertexArray(0);
    waterShader.stop();
}
