#ifndef ARNOLD_PLAYER_H
#define ARNOLD_PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <map>
#include "../../Engine/Entity.h"
#include "../../Engine/Game.h"
#include "../../Engine/Utilities/Utils.h"
#include "../../Engine/MessageHandler.h"
#include "../../Engine/TextureManager.h"

class Projectile;

#include "Projectile.h"

using namespace Utils;

class Player : public Entity
{
public:
    Player(Geometry::Vector2D _coordinates, Game *_game) : Entity(_coordinates, _game)
    {
        dimensions = {15, 15};
        gunSound = Utils::Audio::loadMedia(("../assets/audio/laser.mp3"));
        playerTex = TextureManager::LoadTexture("../assets/sprites/characters/player.png", _game->getRenderer());
    }

    void registerMovementKey(SDL_Keycode key, bool isHeld);

    void handleEvents(SDL_Event sdlEvent);

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

    void takeDamage(double damage) const;

private:
    Projectile spawnProjectile(Geometry::Vector2D destination);

    double movementSpeed = 150.0;

    bool isCollidingWithWall(Geometry::Vector2D potentialCoordinates);

    double health = 100;

    std::vector<SDL_Keycode> currentHeldKeys;

    SDL_Texture *playerTex;

    Mix_Chunk *gunSound = nullptr;

    std::map<SDL_Keycode, bool> movementKeys = {
        {SDLK_w, false},
        {SDLK_a, false},
        {SDLK_s, false},
        {SDLK_d, false}};
};

#endif // ARNOLD_PLAYER_H
