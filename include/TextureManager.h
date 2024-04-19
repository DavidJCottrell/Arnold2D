#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class TextureManager {
public:
    TextureManager();

    ~TextureManager();

    static SDL_Texture *LoadTexture(const char *fileName, SDL_Renderer *renderer);

    static void DrawTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect src, SDL_Rect dest);
};

#endif
