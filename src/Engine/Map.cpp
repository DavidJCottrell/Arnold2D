#include <Arnold.h>

Map::Map(SDL_Renderer *renderer) {
    floorTex = TextureManager::LoadTexture("/map/ground.png", renderer);
    wallTex = TextureManager::LoadTexture("/map/wall.png", renderer);
    LoadMap();

    src.x = src.y = 0;
    src.w = src.h = 32;
}

Map::~Map() = default;

void Map::LoadMap() {
    std::ifstream levelFile("../assets/map/level_1.csv");

    if (!levelFile.is_open()) throw std::runtime_error("Could not open level file");
    if (!levelFile.good()) throw std::runtime_error("Error when using level file");

    std::string line, tile;

    int rowCount = 0;
    while (std::getline(levelFile, line)) {
        std::stringstream ss(line);
        int columnCount = 0;

        while (getline(ss, tile, ',')) {
            map[rowCount][columnCount] = Tile();
            map[rowCount][columnCount].tileType = static_cast<TileType>(stoi(tile));
            map[rowCount][columnCount].dimensions = {32, 32};
            map[rowCount][columnCount].coordinates = {
                    static_cast<float>(columnCount * 32), static_cast<float>(rowCount * 32)
            };
            columnCount++;
        }
        rowCount++;
    }
    levelFile.close();
}

void Map::DrawMap(SDL_Renderer *renderer) const {
    for (const auto &row: map) {
        for (const auto &column: row) {
            const SDL_Rect dest{
                    static_cast<int>(column.coordinates.x),
                    static_cast<int>(column.coordinates.y),
                    static_cast<int>(column.dimensions.x),
                    static_cast<int>(column.dimensions.y)
            };
            switch (column.tileType) {
                case TileType::ground:
                    TextureManager::DrawTexture(floorTex, renderer, src, dest);
                    break;
                case TileType::wall:
                    TextureManager::DrawTexture(wallTex, renderer, src, dest);
                    break;
                default:
                    break;
            }
        }
    }
}
