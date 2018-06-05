//
// Created by Wenlong Wang on 5/06/18.
//

#ifndef WATERRENDERING_TERRAIN_H
#define WATERRENDERING_TERRAIN_H

#include "Loader.h"
#include "RawModel.h"
#include "ModelTexture.h"
class Terrain {
public:
    Terrain(float gridX, float gridZ, Loader loader, const ModelTexture &texture);

    float getX() const;

    float getZ() const;

    const RawModel &getRawModel() const;

    const ModelTexture &getTexture() const;

private:
    constexpr static float SIZE = 800;
    constexpr static int VERTEX_COUNT = 128;

    float x;
    float z;

    RawModel rawModel = RawModel(0, 0);
    ModelTexture texture;


    RawModel generateTerrain(Loader loader);
};


#endif //WATERRENDERING_TERRAIN_H
