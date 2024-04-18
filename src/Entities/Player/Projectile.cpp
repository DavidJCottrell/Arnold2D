#include <Arnold.h>


void Projectile::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect const projectileRect = {
        static_cast<int>(coordinates.x),
        static_cast<int>(coordinates.y),
        static_cast<int>(dimensions.x),
        static_cast<int>(dimensions.y),
    };
    SDL_RenderFillRect(renderer, &projectileRect);
}

void Projectile::update(double const deltaTime)
{
    // Entity collisions
    for (const auto& entity : game->getEntities())
    {
        // Check for enemy collisions
        if (const auto* pEnemy = dynamic_cast<Enemy*>(entity.get()))
        {
            if (isColliding(coordinates, dimensions, pEnemy->coordinates, pEnemy->dimensions))
            {
                isMarkedForRemoval = true;
                pEnemy->takeDamage();
            }
        }
        if (const auto* pJuggernaut = dynamic_cast<Juggernaut*>(entity.get()))
        {
            if (isColliding(coordinates, dimensions, pJuggernaut->coordinates, pJuggernaut->dimensions))
            {
                isMarkedForRemoval = true;
                pJuggernaut->takeDamage();
            }
        }
    }

    // Wall collisions
    const Map::pointer_to_arrays map = game->map->getMap();
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            if (map[row][column].tileType == water)
            {
                if (isColliding(coordinates, dimensions, map[row][column].coordinates, map[row][column].dimensions))
                {
                    isMarkedForRemoval = true;
                }
            }
        }
    }

    float distanceX = abs(abs(coordinates.x) - abs(origin.x));
    float distanceY = abs(abs(coordinates.y) - abs(origin.y));

    if (distanceX >= range || distanceY >= range) isMarkedForRemoval = true;

    Vector2D moveAmount = {
        static_cast<float>(destination.x * movementSpeed * deltaTime),
        static_cast<float>(destination.y * movementSpeed * deltaTime)
    };
    moveAmount = normalise(moveAmount);

    coordinates.x += static_cast<float>(moveAmount.x * movementSpeed * deltaTime);
    coordinates.y += static_cast<float>(moveAmount.y * movementSpeed * deltaTime);
}
