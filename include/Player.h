#ifndef ARNOLD_PLAYER_H
#define ARNOLD_PLAYER_H

#pragma once

#include <map>
#include <thread>
#include <vector>

using namespace Utils::Geometry;

enum WeaponType {
    rifle, shotgun, uzi
};

class Player final : public Entity {
public:
    Player(const Vector2D coordinates, Game *game) : Entity(coordinates, game, 40) {
        dimensions = {20, 20};
        laserRifleSound = Audio::loadMedia(("../assets/audio/laser.mp3"));
        shotgunSound = Audio::loadMedia(("../assets/audio/shotgun.mp3"));
        uziSound = Audio::loadMedia(("../assets/audio/uzi.wav"));
        playerTex = TextureManager::LoadTexture("../assets/sprites/characters/player.png", game->getRenderer());
    }

    void registerMovementKey(SDL_Keycode key, bool isHeld);

    void handleEvents(const SDL_Event &sdlEvent);

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

    void takeDamage(int damageAmount) const;

    void heal(int healAmount);

    WeaponType weaponType = rifle;

private:
    const int healthCapacity = 40;

    const float movementSpeed = 150.0f;

    bool isCollidingWithWall(Vector2D potentialCoordinates) const;

    std::vector<SDL_Keycode> currentHeldKeys;

    SDL_Texture *playerTex;

    Mix_Chunk *laserRifleSound = nullptr;
    Mix_Chunk *shotgunSound = nullptr;
    Mix_Chunk *uziSound = nullptr;

    std::thread uziThread;

    Vector2D mouseCoords{};

    bool mouseHeld = false;
    std::map<SDL_Keycode, bool> movementKeys = {
            {SDLK_w, false},
            {SDLK_a, false},
            {SDLK_s, false},
            {SDLK_d, false}
    };
};

#endif // ARNOLD_PLAYER_H
