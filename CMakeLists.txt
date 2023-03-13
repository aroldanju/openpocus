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
        src/apogeesplash.cpp
        src/introsplash.cpp
        src/mainmenu.cpp
        )

set(data_sources
        src/engine/data/datamanager.cpp
        src/engine/data/data.cpp
        src/engine/data/fat.cpp
        src/engine/data/datafile.cpp
        src/engine/data/fatloader.cpp
        src/engine/data/asset/image.cpp
        src/engine/data/asset/palette.cpp
        src/engine/data/asset/pcx.cpp
        src/engine/data/asset/voc.cpp
        src/engine/data/asset/midi.cpp
        src/engine/data/asset/font.cpp
        src/engine/data/asset/level.cpp
        src/engine/data/asset/leveltime.cpp
        src/engine/data/asset/leveltileset.cpp
        src/engine/data/asset/levelbackground.cpp
        )

set(engine_sources
        src/engine/log.cpp
        src/engine/pocusengine.cpp
        src/engine/provider/provider.cpp
        src/engine/statemanager.cpp
        src/engine/fade.cpp
        src/engine/sound.h
        src/engine/texture.h
        src/engine/renderer.h
        src/engine/audio.h
        src/engine/musicplayer.cpp
        src/engine/menu.cpp
        src/engine/particles.cpp
        src/engine/animation.cpp
        src/engine/map.cpp
        src/engine/point.cpp
        src/engine/config.cpp
        src/engine/player.cpp
        )

set(sdl_sources
        src/engine/sdl/sdlrenderer.cpp
        src/engine/sdl/sdleventhandler.cpp
        src/engine/sdl/sdltexture.cpp
        src/engine/sdl/sdlsound.cpp
        src/engine/sdl/sdlaudio.cpp
        )

add_executable(OpenPocus ${sources} ${data_sources} ${engine_sources} ${sdl_sources})

target_link_libraries(OpenPocus ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} -ltinyxml2)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/shareware.fat
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})