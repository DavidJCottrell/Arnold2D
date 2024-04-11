#include "Utils.h"

Coordinates Utils::normalise(Coordinates coordinates) {
    Coordinates normalisedCoordinates = coordinates;
    double vecMagnitude = sqrt(pow(coordinates.x, 2) + pow(coordinates.y, 2));
    if (vecMagnitude > 0) {
        normalisedCoordinates.x /= (float) vecMagnitude;
        normalisedCoordinates.y /= (float) vecMagnitude;
    }
    return normalisedCoordinates;
}

Mix_Chunk *Utils::Audio::loadMedia(const char *path) {
    Mix_Chunk *audio = Mix_LoadWAV(path);
    if (audio == nullptr) {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return audio;
}

void Utils::Audio::playSound(Mix_Chunk *audio) {
    Mix_PlayChannel(-1, audio, 0);
}
