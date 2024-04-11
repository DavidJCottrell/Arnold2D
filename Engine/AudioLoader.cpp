#include "AudioLoader.h"

AudioLoader::AudioLoader() = default;

AudioLoader::~AudioLoader() = default;

Mix_Chunk *AudioLoader::loadMedia(const char *path) {
    Mix_Chunk *audio = Mix_LoadWAV(path);
    if (audio == nullptr) {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return nullptr;
    }
    return audio;
}

void AudioLoader::playSound(Mix_Chunk *audio) {
    Mix_PlayChannel(-1, audio, 0);
}


bool AudioLoader::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

