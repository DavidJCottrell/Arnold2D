
#include "../include/TextureManager.h"

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() = default;

SDL_Texture *TextureManager::LoadTexture(const char *fileName, SDL_Renderer *renderer) {

    std::string fullPath;

    fullPath += SDL_GetBasePath();
    fullPath += "assets";
    fullPath += fileName;

    const char *cStrFullPath = fullPath.c_str();

    SDL_Surface *tempSurface = IMG_Load(cStrFullPath);
    if (tempSurface == nullptr) throw std::runtime_error("Could not open image file: " + fullPath);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

void
TextureManager::DrawTexture(SDL_Texture *texture, SDL_Renderer *renderer, const SDL_Rect src, const SDL_Rect dest) {
    SDL_RenderCopy(renderer, texture, &src, &dest);
}
