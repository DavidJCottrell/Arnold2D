#ifndef ARNOLD_PLAYER_H
#define ARNOLD_PLAYER_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <map>
#include "Entity.h"
#include "../Game.h"


class Projectile;

#include "Projectile.h"
#include "../MessageHandler.h"


class Player : public Entity {
public:
    Player(float _x, float _y, Game *_game) : Entity(_x, _y, _game) {
        dimensions = {20, 20};
    }

    void registerMovementKey(SDL_Keycode key, bool isHeld);

    void handleEvents(SDL_Event sdlEvent);

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

    double health = 100;

private:
    Projectile spawnProjectile(int destinationX, int destinationY);

    double movementSpeed = 150.0;

    std::vector<SDL_Keycode> currentHeldKeys;

    std::map<SDL_Keycode, bool> movementKeys = {
            {SDLK_w, false},
            {SDLK_a, false},
            {SDLK_s, false},
            {SDLK_d, false}
    };
};


#endif //ARNOLD_PLAYER_H
