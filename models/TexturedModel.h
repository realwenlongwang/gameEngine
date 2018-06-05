//
// Created by Wenlong Wang on 3/06/18.
//

#ifndef WATERRENDERING_TEXTUREDMODEL_H
#define WATERRENDERING_TEXTUREDMODEL_H


#include "ModelTexture.h"
#include "RawModel.h"



class TexturedModel {

private:
    RawModel rawModel;
    ModelTexture modelTexture;
public:
    const RawModel &getRawModel() const;
    const ModelTexture &getModelTexture() const;
    TexturedModel(const RawModel &rawModel, const ModelTexture &modelTexture);
};

struct TexturedModelCompare  // Needed for an user-defined class as map key
{
    bool operator() (const TexturedModel& lhs, const TexturedModel& rhs) const
    {
        return lhs.getRawModel().getVertexCount() < rhs.getRawModel().getVertexCount();
    }
};


#endif //WATERRENDERING_TEXTUREDMODEL_H
