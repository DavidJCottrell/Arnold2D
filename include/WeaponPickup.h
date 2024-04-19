#ifndef ARNOLD_WEAPONPICKUP_H
#define ARNOLD_WEAPONPICKUP_H

#include <Arnold.h>

class WeaponPickup : public Entity {
public:
    WeaponPickup(const Vector2D coordinates, Game *game, WeaponType weaponType) : Entity(coordinates, game, -1) {
        dimensions = {20, 20};
        this->weaponType = weaponType;
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

private:
    WeaponType weaponType;
};


#endif //ARNOLD_WEAPONPICKUP_H
