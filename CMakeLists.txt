cmake_minimum_required(VERSION 3.21)
project(FlyingShark C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_gfx REQUIRED)

include_directories(include ${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${SDL_GFX_INCLUDE_DIR})

set(CMAKE_C_STANDARD 23)

add_executable(
        FlyingShark
        src/main.c
        src/state/game/game_state.c
        src/state/game/state/endgame/endgame.c
        src/state/game/state/game/component/explosion.c
        src/state/game/state/game/component/interface.c
        src/state/game/state/game/component/level.c
        src/state/game/state/game/component/missile.c
        src/state/game/state/game/component/opponent/boat.c
        src/state/game/state/game/component/opponent/bomber.c
        src/state/game/state/game/component/opponent/fighter.c
        src/state/game/state/game/component/opponent/fireball.c
        src/state/game/state/game/component/opponent/tank.c
        src/state/game/state/game/component/opponent.c
        src/state/game/state/game/component/player.c
        src/state/game/state/game/component/powerup.c
        src/state/game/state/game/game.c
        src/state/game/state/gameover/gameover.c
        src/state/game/state/pause/pause.c
        src/state/input/input.c
        src/state/intro/intro.c
        src/state/menu/menu.c
        src/state/score/score.c
        src/state.c
        src/tool/file.c
        src/tool/tool.c
    )

target_link_libraries(FlyingShark ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARIES} ${SDL_TTF_LIBRARIES} ${SDL_GFX_LIBRARY})