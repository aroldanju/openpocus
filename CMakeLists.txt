cmake_minimum_required(VERSION 3.14.3)

project(OpenPocus VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
include_directories(dependencies/plog/include)

set(sources
        src/main.cpp
        src/openpocus.cpp
        src/stategame.cpp
        )

set(engine_sources
        src/engine/log.cpp
        src/engine/pocusengine.cpp
        src/engine/provider/provider.cpp
        src/engine/statemanager.cpp
        src/engine/data/data.cpp
        src/engine/data/fat.cpp
        src/engine/data/datafile.cpp
        src/engine/data/fatloader.cpp
        )

set(sdl_sources
        src/engine/sdl/sdlrenderer.cpp
        src/engine/sdl/sdleventhandler.cpp
        )

add_executable(OpenPocus ${sources} ${engine_sources} ${sdl_sources})

target_link_libraries(OpenPocus ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
