#include <Arnold.h>

using namespace Utils;

Vector2D Geometry::normalise(const Vector2D coordinates)
{
    Vector2D normalisedCoordinates = coordinates;
    double const vecMagnitude = sqrt(pow(coordinates.x, 2) + pow(coordinates.y, 2));
    if (vecMagnitude > 0)
    {
        normalisedCoordinates.x /= static_cast<float>(vecMagnitude);
        normalisedCoordinates.y /= static_cast<float>(vecMagnitude);
    }
    return normalisedCoordinates;
}

Vector2D Geometry::getUnitVector(Vector2D origin, const Vector2D destination)
{
    float directionX = destination.x - origin.x;
    float directionY = destination.y - origin.y;
    auto const distance = static_cast<float>(sqrt(pow(directionX, 2) + pow(directionY, 2)));

    directionX /= distance;
    directionY /= distance;

    return {directionX, directionY};
}

bool Geometry::isColliding(const Vector2D& aCords, const Vector2D& aDim, const Vector2D& bCords, Vector2D bDim)
{
    return std::max(aCords.x, bCords.x) < std::min(aCords.x + aDim.x, bCords.x + bDim.x) &&
        std::max(aCords.y, bCords.y) < std::min(aCords.y + aDim.y, bCords.y + bDim.y);
}

Mix_Chunk* Audio::loadMedia(const char* path)
{
    Mix_Chunk* audio = Mix_LoadWAV(path);
    if (audio == nullptr)
    {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return audio;
}

void Audio::playSound(Mix_Chunk* audio)
{
    Mix_PlayChannel(-1, audio, 0);
}
