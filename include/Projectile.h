#ifndef ARNOLD_PROJECTILE_H
#define ARNOLD_PROJECTILE_H

#pragma once

using namespace Utils::Geometry;

class Projectile : public Entity
{
public:
    Projectile(Vector2D coordinates, Game* game, Vector2D destination
    ) : Entity(coordinates, game, -1)
    {
        dimensions = {10, 10};
        this->destination = destination;
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
