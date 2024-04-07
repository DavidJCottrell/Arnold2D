#ifndef ARNOLD_PROJECTILE_H
#define ARNOLD_PROJECTILE_H

#include "Entity.h"
#include "Enemy.h"

class Projectile : public Entity {
public:
    Projectile(float x, float y, Game *_game, float _directionX, float _directionY) : Entity(x, y, _game) {
        dimensions = {10, 10};
        directionX = _directionX;
        directionY = _directionY;
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

private:
    float directionX;
    float directionY;
};


#endif //ARNOLD_PROJECTILE_H
