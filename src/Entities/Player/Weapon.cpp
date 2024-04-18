#include <Arnold.h>

void Weapon::fireShotgun(const Vector2D origin, const Vector2D target, Game* game)
{
    constexpr int spread = 4;
    constexpr int range = 125.0f;

    const float deltaX = static_cast<float>(target.x) - origin.x;
    const float deltaY = static_cast<float>(target.y) - origin.y;

    game->addEntity(Projectile(origin, game, getUnitVector(origin, target), range));

    if (abs(deltaX) > abs(deltaY))
    {
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
    }
    else
    {
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

void Weapon::fireRifle(const Vector2D origin, const Vector2D target, Game* game)
{
    constexpr int range = 325.0f;
    game->addEntity(Projectile(origin, game, getUnitVector(origin, target), range));
}

void Weapon::fireUzi(const Vector2D* origin, const Vector2D* target, Game* game, const bool* mouseHeld)
{
    while (*mouseHeld)
    {
        constexpr int range = 175.0f;
        std::cout << target->x << " - " << target->y << std::endl;
        game->addEntity(Projectile(*origin, game, getUnitVector(*origin, *target), range));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
