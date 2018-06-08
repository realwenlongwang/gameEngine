//
// Created by Wenlong Wang on 7/06/18.
//

#ifndef WATERRENDERING_GUIRENDERER_H
#define WATERRENDERING_GUIRENDERER_H

#include "RawModel.h"
#include "Loader.h"
#include "GuiTexture.h"
#include "GuiShader.h"
class GuiRenderer {

public:
    GuiRenderer(Loader loader);
    void render(std::vector<GuiTexture> guiTextures);
    void cleanUp();

private:

    RawModel quad = RawModel(0, 0);
    GuiShader guiShader;
    void setUpVAO(Loader loader);
};


#endif //WATERRENDERING_GUIRENDERER_H
