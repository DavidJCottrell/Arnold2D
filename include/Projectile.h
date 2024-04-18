#ifndef ARNOLD_PROJECTILE_H
#define ARNOLD_PROJECTILE_H

#pragma once

using namespace Utils::Geometry;

class Projectile : public Entity
{
public:
    Projectile(const Vector2D coordinates, Game* game, const Vector2D destination, const float range
    ) : Entity(coordinates, game, -1)
    {
        this->destination = destination;
        this->range = range;
        dimensions = {10, 10};
        origin = coordinates;
    }

    void render(SDL_Renderer* renderer) override;

    void update(double deltaTime) override;

private:
    Vector2D destination{};
    Vector2D origin{};
    const float movementSpeed = 400.0f;
    float range = 300.0f;
};


#endif //ARNOLD_PROJECTILE_H
