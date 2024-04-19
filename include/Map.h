#ifndef MAP_H
#define MAP_H

#pragma once

#include <fstream>

using namespace Utils::Geometry;

enum TileType {
    ground, wall
};

struct Tile {
    TileType tileType;
    Vector2D dimensions;
    Vector2D coordinates;
};

class Map {
public:
    explicit Map(SDL_Renderer *renderer);

    ~Map();

    void LoadMap();

    void DrawMap(SDL_Renderer *renderer) const;

    typedef Tile (*pointer_to_arrays)[25];

    pointer_to_arrays getMap() { return map; }

private:
    SDL_Rect src{};

    SDL_Texture *floorTex;
    SDL_Texture *wallTex;

    Tile map[20][25]{};
};

#endif
