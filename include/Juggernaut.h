#ifndef JUGGERNAUT_H
#define JUGGERNAUT_H

#pragma once

class Juggernaut final : public Entity {
public:
    Juggernaut(const Vector2D coordinates, Game *game) : Entity(coordinates, game, 80) {
        dimensions = {40, 40};
    }

    void takeDamage() const;

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

private:
    const int healthCapacity = 80;
    const float movementSpeed = 70.0f;
};


#endif //JUGGERNAUT_H
