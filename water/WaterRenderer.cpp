//
// Created by Wenlong Wang on 7/06/18.
//

#include "WaterRenderer.h"


WaterRenderer::WaterRenderer(Loader loader, const WaterShader &waterShader, WaterFrameBuffers waterFrameBuffers)
        : waterShader(waterShader), waterFrameBuffers(waterFrameBuffers) {
    dudvTexture = loader.loadTerrainTexture(DUDV_MAP);
    normalTexture = loader.loadTerrainTexture(NORMAL_MAP);
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

void WaterRenderer::render(std::vector<Water> water, Camera *camera, Light light) {
    prepareRender(camera, light);
    for(Water waterTile: water) {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(), glm::vec3(waterTile.getX(), waterTile.getHeight(), waterTile.getZ())) *
                                      glm::scale (   glm::mat4(), glm::vec3(waterTile.TILE_SIZE));
        waterShader.loadModelMatrix(translationMatrix);
        glDrawElements(GL_TRIANGLES, quad.getVertexCount(), GL_UNSIGNED_INT, nullptr);
    }
    unbind();
}

void WaterRenderer::prepareRender(Camera *pCamera, Light light) {
    waterShader.start();
    waterShader.loadViewMatrix(pCamera);
    // TODO: sin function seems will cause the wave change direction periodically
    moveFactor += 0.0001f;
//    moveFactor = (sin(WAVE_SPEED * glfwGetTime()) + 1.0f) / 2.0f;
//    moveFactor += WAVE_SPEED * glfwGetTime(); //* 0.0005;
//    moveFactor += sin(WAVE_SPEED * glfwGetTime());
//    moveFactor = fmod(moveFactor, 1.0f);
//    std::cout << moveFactor << std::endl;
    waterShader.loadMoveFactor(moveFactor);
    waterShader.loadLight(light);
    glBindVertexArray(quad.getVao());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, waterFrameBuffers.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, waterFrameBuffers.getRefractionTexture());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, dudvTexture);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, normalTexture);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, waterFrameBuffers.getRefractionDepthTexture());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void WaterRenderer::unbind() {
    glDisable(GL_BLEND);
    glBindVertexArray(0);
    waterShader.stop();
}
