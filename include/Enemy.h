#ifndef ARNOLD_ENEMY_H
#define ARNOLD_ENEMY_H

#pragma once

using namespace Utils::Geometry;

class Enemy final : public Entity {
public:
    Enemy(const Vector2D coordinates, Game *game) : Entity(coordinates, game, 40) {
        dimensions = {20, 20};
    }

    void takeDamage() const;

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

private:
    const int healthCapacity = 40;
};


#endif //ARNOLD_ENEMY_H
