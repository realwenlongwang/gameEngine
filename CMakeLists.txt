cmake_minimum_required(VERSION 3.10)
project(gameEngine)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

set(CMAKE_CXX_STANDARD 11)

include_directories(helperLibs)
include_directories(renderEngine)
include_directories(models)
include_directories(textures)
include_directories(shaders)
include_directories(entities)
include_directories(terrains)
include_directories(skybox)
include_directories(water)
include_directories(gui)
include_directories(${GLFW_INCLUDE_DIRS})

set(
        HELPER_LIBS
        helperLibs/stb_image.h
        helperLibs/image.cpp helperLibs/image.h
        helperLibs/utils.cpp helperLibs/utils.h
        helperLibs/camera.cpp helperLibs/camera.h

        helperLibs/Exception.h)

set(
        RENDER_ENGINE
        renderEngine/Loader.cpp renderEngine/Loader.h
        renderEngine/EntityRenderer.cpp renderEngine/EntityRenderer.h
        renderEngine/WindowManager.cpp renderEngine/WindowManager.h
        renderEngine/OBJLoader.cpp renderEngine/OBJLoader.h renderEngine/MasterRenderer.cpp renderEngine/MasterRenderer.h terrains/TerrainRenderer.cpp terrains/TerrainRenderer.h)

set(
        MODELS

        models/RawModel.cpp models/RawModel.h models/TexturedModel.cpp models/TexturedModel.h)

set(
        TEXTURES
        textures/ModelTexture.cpp textures/ModelTexture.h
)

set(
        SHADERS
        shaders/ShaderProgram.cpp shaders/ShaderProgram.h shaders/StaticShader.cpp shaders/StaticShader.h terrains/TerrainShader.cpp terrains/TerrainShader.h)

set(
        ENTITIES
        entities/Entity.cpp entities/Entity.h
        entities/Light.cpp entities/Light.h)
set(
        TERRAIN

        terrains/Terrain.cpp terrains/Terrain.h)
set(
        SKYBOX
        skybox/SkyboxShader.cpp skybox/SkyboxShader.h skybox/SkyboxRenderer.cpp skybox/SkyboxRenderer.h skybox/Skybox.cpp skybox/Skybox.h)

set(
        WATER

        water/WaterFrameBuffers.cpp water/WaterFrameBuffers.h water/Water.cpp water/Water.h water/WaterShader.cpp water/WaterShader.h water/WaterRenderer.cpp water/WaterRenderer.h)

set(
        GUI

        gui/GuiTexture.cpp gui/GuiTexture.h gui/GuiRenderer.cpp gui/GuiRenderer.h gui/GuiShader.cpp gui/GuiShader.h)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

add_executable(gameEngine main.cpp ${RENDER_ENGINE} ${HELPER_LIBS} ${MODELS} ${TEXTURES} ${SHADERS} ${ENTITIES} ${TERRAIN} ${SKYBOX} ${WATER} ${GUI})

target_link_libraries(gameEngine ${GLFW_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})