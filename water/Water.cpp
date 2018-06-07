//
// Created by Wenlong Wang on 7/06/18.
//

#include "Water.h"

Water::Water(float height, float x, float z) : height(height), x(x), z(z) {}

float Water::getHeight() const {
    return height;
}

float Water::getX() const {
    return x;
}

float Water::getZ() const {
    return z;
}
