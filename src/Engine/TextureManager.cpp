#include "../include/TextureManager.h"

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() = default;

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

void TextureManager::DrawTexture(SDL_Texture* texture, SDL_Renderer* renderer, const SDL_Rect src, const SDL_Rect dest)
{
    SDL_RenderCopy(renderer, texture, &src, &dest);
}
