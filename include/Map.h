#ifndef MAP_H
#define MAP_H

#pragma once

#include <fstream>

using namespace Utils::Geometry;

enum TileType { dirt = 0, water = 1, grass = 2 };

struct Tile
{
    TileType tileType;
    Vector2D dimensions;
    Vector2D coordinates;
};

class Map
{
public:
    explicit Map(SDL_Renderer* renderer);

    ~Map();

    void LoadMap();

    void DrawMap(SDL_Renderer* renderer) const;

    typedef Tile (*pointer_to_arrays)[25];
    pointer_to_arrays getMap() { return map; }

private:
    SDL_Rect src{};

    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;

    Tile map[20][25]{};
};

#endif
