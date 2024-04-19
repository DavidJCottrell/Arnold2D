#include <Arnold.h>

void Weapon::fireShotgun(const Vector2D origin, const Vector2D target, Game *game, Mix_Chunk *sound) {
    Audio::playSound(sound);

    constexpr int spread = 4;
    constexpr int range = 150.0f;

    const float deltaX = static_cast<float>(target.x) - origin.x;
    const float deltaY = static_cast<float>(target.y) - origin.y;

    game->addEntity(Projectile(origin, game, getUnitVector(origin, target), range));

    if (abs(deltaX) > abs(deltaY)) {
        game->addEntity(
                Projectile(
                        origin,
                        game,
                        getUnitVector(origin, {target.x, target.y + deltaX / spread}),
                        range
                ));
        game->addEntity(
                Projectile(
                        origin,
                        game,
                        getUnitVector(origin, {target.x, target.y - deltaX / spread}),
                        range
                ));
    } else {
        game->addEntity(
                Projectile(
                        origin,
                        game,
                        getUnitVector(origin, {target.x + deltaY / spread, target.y}),
                        range
                ));
        game->addEntity(
                Projectile(
                        origin,
                        game,
                        getUnitVector(origin, {target.x - deltaY / spread, target.y}),
                        range
                ));
    }
}

void Weapon::fireRifle(const Vector2D origin, const Vector2D target, Game *game, Mix_Chunk *sound) {
    Audio::playSound(sound);
    constexpr int range = 325.0f;
    game->addEntity(Projectile(origin, game, getUnitVector(origin, target), range));
}

void Weapon::fireUzi(const Vector2D *origin, const Vector2D *target, Game *game, const bool *mouseHeld,
                     Mix_Chunk *sound) {
    while (*mouseHeld && game->getPlayer()->weaponType == uzi) {
        constexpr int range = 175.0f;
        Audio::playSound(sound);
        game->addEntity(Projectile(*origin, game, getUnitVector(*origin, *target), range));
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }
}
