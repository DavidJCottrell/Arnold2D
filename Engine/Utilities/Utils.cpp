#include "Utils.h"

using namespace Utils;

Geometry::Vector2D Utils::Geometry::normalise(Vector2D coordinates) {
    Vector2D normalisedCoordinates = coordinates;
    double vecMagnitude = sqrt(pow(coordinates.x, 2) + pow(coordinates.y, 2));
    if (vecMagnitude > 0) {
        normalisedCoordinates.x /= (float) vecMagnitude;
        normalisedCoordinates.y /= (float) vecMagnitude;
    }
    return normalisedCoordinates;
}

Geometry::Vector2D Utils::Geometry::getUnitVector(Vector2D origin, Vector2D destination) {
    float directionX = (float) destination.x - origin.x;
    float directionY = (float) destination.y - origin.y;
    auto distance = (float) sqrt(pow(directionX, 2) + pow(directionY, 2));

    directionX /= distance;
    directionY /= distance;

    return {directionX, directionY};
}

bool Geometry::isColliding(const Utils::Geometry::Vector2D &a, const Utils::Geometry::Vector2D &b, float tolerance) {
    return abs(a.x - b.x) < tolerance && abs(a.y - b.y) < tolerance;
}

Mix_Chunk *Audio::loadMedia(const char *path) {
    Mix_Chunk *audio = Mix_LoadWAV(path);
    if (audio == nullptr) {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return audio;
}

void Audio::playSound(Mix_Chunk *audio) {
    Mix_PlayChannel(-1, audio, 0);
}
