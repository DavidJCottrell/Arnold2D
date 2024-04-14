#ifndef MAP_H
#define MAP_H

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"

class Map {
public:
    explicit Map(SDL_Renderer *renderer);

    ~Map();

    void LoadMap(int mapArr[20][25]);

    void DrawMap(SDL_Renderer *renderer);

private:
    SDL_Rect src{}, dest{};

    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;

    int map[20][25]{};
};

#endif
