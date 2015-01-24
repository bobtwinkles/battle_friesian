cmake_minimum_required(VERSION 2.8)

project(friesian)

include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
list(APPEND CMAKE_CXX_DEBUG_FLAGS "-g -Wall -Wextra -Werror -v")

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image >= 2.0.0)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(Fontconfig REQUIRED)
find_package(Box2D REQUIRED)

set(SRC Main.cpp
        construct/LevelParser.cpp
        construct/Parser.cpp
        flow/GameFlow.cpp
        systems/GameContext.cpp
        systems/Registry.cpp
        systems/animation/Animation.cpp
        systems/animation/AnimationSystem.cpp
        systems/entity/EntitySystem.cpp
        systems/entity/entities/EasyHorse.cpp
        systems/entity/entities/Platform.cpp
        systems/physics/PhysicsSystem.cpp
        systems/render/RenderSystem.cpp
        systems/render/renderables/MobileTexturedRender.cpp
        metric/GPUMetric.cpp
        util/Util.cpp
        util/ImageLoad.cpp
        ogl/Shader.cpp
        ogl/Texture.cpp
        ogl/TexturedVertexBuffer.cpp
        ogl/ui/UI.cpp
        ogl/ui/Graph.cpp
        ogl/ui/Text.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(SYSTEM ${FONTCONFIG_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR_freetype2} ${GLM_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/ogl
                    ${CMAKE_SOURCE_DIR}/ogl/ui
                    ${CMAKE_SOURCE_DIR}/metric
                    ${CMAKE_SOURCE_DIR}/systems
                    ${CMAKE_SOURCE_DIR}/systems/animation
                    ${CMAKE_SOURCE_DIR}/systems/entity
                    ${CMAKE_SOURCE_DIR}/systems/physics
                    ${CMAKE_SOURCE_DIR}/systems/render
                    ${CMAKE_SOURCE_DIR}/util)

add_executable(friesian ${SRC})

target_link_libraries(friesian ${BOX2D_LIBRARY} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${FONTCONFIG_LIBRARIES} ${FREETYPE_LIBRARIES})

install(DIRECTORY resources DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
