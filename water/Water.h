//
// Created by Wenlong Wang on 7/06/18.
//

#ifndef WATERRENDERING_WATER_H
#define WATERRENDERING_WATER_H


class Water {
public:
    const float TILE_SIZE = 30.0f;

    Water(float height, float x, float z);

    float getHeight() const;

    float getX() const;

    float getZ() const;

private:
    float height, x, z;



};


#endif //WATERRENDERING_WATER_H
