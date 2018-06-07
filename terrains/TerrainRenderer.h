//
// Created by Wenlong Wang on 5/06/18.
//

#ifndef WATERRENDERING_TERRAINRENDERER_H
#define WATERRENDERING_TERRAINRENDERER_H

#include "TerrainShader.h"
#include "Terrain.h"

class TerrainRenderer {
public:
    TerrainRenderer(const TerrainShader &terrainShader);

    void setProjectionMatrix(const glm::mat4 &projectionMatrix);
    void render(std::vector<Terrain> terrains);
private:
    TerrainShader terrainShader;
    glm::mat4 projectionMatrix;

    void prepareTexturedModel(Terrain terrain);

    void unbindTexturedModel();

    void loadTranslationMatrix(Terrain terrain);
};


#endif //WATERRENDERING_TERRAINRENDERER_H
