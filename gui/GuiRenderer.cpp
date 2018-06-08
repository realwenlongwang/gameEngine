//
// Created by Wenlong Wang on 7/06/18.
//

#include "GuiRenderer.h"

void GuiRenderer::setUpVAO(Loader loader) {
    std::vector<glm::vec4> vertices{glm::vec4(-1, -1, 0, 1), glm::vec4(-1, 1, 0, 1), glm::vec4(1, -1, 0, 1), glm::vec4(1, 1, 0, 1)};
    std::vector<glm::ivec3> indices{glm::ivec3(0, 2, 1), glm::ivec3(2, 3, 1)};
    quad = loader.loadToVAO(indices, vertices);

}

GuiRenderer::GuiRenderer(Loader loader) {
    setUpVAO(loader);
}

void GuiRenderer::render(std::vector<GuiTexture> guiTextures) {
    guiShader.start();
    glBindVertexArray(quad.getVao());
    // For the alpha channel of image to work
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // To avoid if any overlapping GUI
    glDisable(GL_DEPTH_TEST);
    for(GuiTexture guiTexture: guiTextures ){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, guiTexture.getTexture());

        glm::mat4 transformationMatrix = glm::translate(glm::mat4(), glm::vec3(guiTexture.getPosition(), 0.0f)) *
                                         glm::scale (   glm::mat4(), glm::vec3(guiTexture.getScale(), 0.0f));
        guiShader.loadTransformationMatrix(transformationMatrix);

        glDrawElements(GL_TRIANGLES, quad.getVertexCount(), GL_UNSIGNED_INT, nullptr);
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glBindVertexArray(0);
    guiShader.stop();
}

void GuiRenderer::cleanUp() {
    guiShader.cleanUp();

}
