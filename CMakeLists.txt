cmake_minimum_required(VERSION 3.10)
project(waterRendering)

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
        renderEngine/OBJLoader.cpp renderEngine/OBJLoader.h renderEngine/MasterRenderer.cpp renderEngine/MasterRenderer.h renderEngine/TerrainRenderer.cpp renderEngine/TerrainRenderer.h)

set(
        MODELS

        models/RawModel.cpp models/RawModel.h models/TexturedModel.cpp models/TexturedModel.h)

set(
        TEXTURES
        textures/ModelTexture.cpp textures/ModelTexture.h
)

set(
        SHADERS
        shaders/ShaderProgram.cpp shaders/ShaderProgram.h shaders/StaticShader.cpp shaders/StaticShader.h shaders/TerrainShader.cpp shaders/TerrainShader.h)

set(
        ENTITIES
        entities/Entity.cpp entities/Entity.h
        entities/Light.cpp entities/Light.h)
set(
        TERRAIN

        terrains/Terrain.cpp terrains/Terrain.h)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

add_executable(waterRendering main.cpp ${RENDER_ENGINE} ${HELPER_LIBS} ${MODELS} ${TEXTURES} ${SHADERS} ${ENTITIES} ${TERRAIN})

target_link_libraries(waterRendering ${GLFW_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})