#include "../include/Map.h"


Map::Map(SDL_Renderer* renderer)
{
    // dirt = TextureManager::LoadTexture("../assets/map/dirt.png", renderer);
    grass = TextureManager::LoadTexture("../assets/map/grass.png", renderer);
    water = TextureManager::LoadTexture("../assets/map/water.png", renderer);

    LoadMap();

    src.x = src.y = 0;
    src.w = 32;
    src.h = 32;
}

Map::~Map() = default;

void Map::LoadMap()
{
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            map[row][column] = Tile();
            // Perimeter of water
            if (row == 0 || row == 19 || column == 0 || column == 24) map[row][column].tileType = TileType::water;
            else map[row][column].tileType = TileType::dirt;
            map[row][column].coordinates = {static_cast<float>(column * 32), static_cast<float>(row * 32)};
            map[row][column].dimensions = {32, 32};
        }
    }
}

void Map::DrawMap(SDL_Renderer* renderer) const
{
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            SDL_Rect dest{
                static_cast<int>(map[row][column].coordinates.x),
                static_cast<int>(map[row][column].coordinates.y),
                static_cast<int>(map[row][column].dimensions.x),
                static_cast<int>(map[row][column].dimensions.y)
            };
            switch (map[row][column].tileType)
            {
            case TileType::dirt:
                // TextureManager::DrawTexture(dirt, renderer, src, dest);
                break;
            case TileType::grass:
                TextureManager::DrawTexture(grass, renderer, src, dest);
                break;
            case TileType::water:
                TextureManager::DrawTexture(water, renderer, src, dest);
                break;
            default:
                break;
            }
        }
    }
}
