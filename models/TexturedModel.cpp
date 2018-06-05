//
// Created by Wenlong Wang on 3/06/18.
//

#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel &rawModel, const ModelTexture &modelTexture) : rawModel(rawModel),
                                                                                           modelTexture(modelTexture) {}

const RawModel &TexturedModel::getRawModel() const {
    return rawModel;
}

const ModelTexture &TexturedModel::getModelTexture() const {
    return modelTexture;
}
