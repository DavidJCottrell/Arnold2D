#include <Arnold.h>

void Player::registerMovementKey(const SDL_Keycode key, const bool isHeld)
{
    auto const movementKey = movementKeys.find(key);
    if (movementKey != movementKeys.end())
        movementKey->second = isHeld;
}

Projectile Player::spawnProjectile(const Vector2D destination)
{
    Vector2D direction = getUnitVector(coordinates, destination);
    return {coordinates, game, direction};
}

void Player::handleEvents(const SDL_Event& sdlEvent)
{
    switch (sdlEvent.type)
    {
    case SDL_KEYDOWN:
        registerMovementKey(sdlEvent.key.keysym.sym, true);
        break;
    case SDL_KEYUP:
        registerMovementKey(sdlEvent.key.keysym.sym, false);
        break;
    case SDL_MOUSEBUTTONDOWN:
        {
            int mouseX = 0, mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            game->addEntity(spawnProjectile({static_cast<float>(mouseX), static_cast<float>(mouseY)}));
            MessageHandler::getInstance().SendMsg("Pew");
            Audio::playSound(gunSound);
            break;
        }
    default:
        break;
    }
}

void Player::render(SDL_Renderer* renderer)
{
    // Draw player rectangle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    const SDL_Rect playerRect = {
        static_cast<int>(coordinates.x),
        static_cast<int>(coordinates.y),
        static_cast<int>(dimensions.x),
        static_cast<int>(dimensions.y)
    };
    SDL_RenderFillRect(renderer, &playerRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 10);
    const SDL_Rect healthBarBackground = {
        static_cast<int>(coordinates.x - (dimensions.x / 2)),
        static_cast<int>(coordinates.y + dimensions.x) + 5,
        healthCapacitity,
        2,
    };
    SDL_RenderFillRect(renderer, &healthBarBackground);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    const SDL_Rect healthBar = {
        static_cast<int>(coordinates.x - (dimensions.x / 2)),
        static_cast<int>(coordinates.y + dimensions.x) + 5,
        health,
        2
    };
    SDL_RenderFillRect(renderer, &healthBar);
}

bool Player::isCollidingWithWall(Vector2D potentialCoordinates) const
{
    // Wall collisions
    const Map::pointer_to_arrays map = game->map->getMap();
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            if (map[row][column].tileType == water)
            {
                if (isColliding(potentialCoordinates, dimensions, map[row][column].coordinates,
                                map[row][column].dimensions))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Player::update(double deltaTime)
{
    if (health <= 0)
    {
        MessageHandler::getInstance().SendMsg("Game Over");
        game->endGame();
    }

    Vector2D moveAmount = {0.0f, 0.0f};

    for (auto& movementKey : movementKeys)
    {
        // Key is being pressed
        if (movementKey.second)
        {
            if (movementKey.first == SDLK_w)
            {
                moveAmount.y -= 1.0f;
                if (isCollidingWithWall({
                    (float)coordinates.x, coordinates.y + static_cast<float>(moveAmount.y * movementSpeed * deltaTime)
                }))
                {
                    moveAmount.y = 0.0f;
                }
            }
            if (movementKey.first == SDLK_a)
            {
                moveAmount.x -= 1.0f;
                if (isCollidingWithWall({
                    coordinates.x + static_cast<float>(moveAmount.x * movementSpeed * deltaTime), coordinates.y
                }))
                {
                    moveAmount.x = 0.0f;
                }
            }
            if (movementKey.first == SDLK_s)
            {
                moveAmount.y += 1.0f;
                if (isCollidingWithWall({
                    (float)coordinates.x, coordinates.y + static_cast<float>(moveAmount.y * movementSpeed * deltaTime)
                }))
                {
                    moveAmount.y = 0.0f;
                }
            }

            if (movementKey.first == SDLK_d)
            {
                moveAmount.x += 1.0f;
                if (isCollidingWithWall({
                    coordinates.x + static_cast<float>(moveAmount.x * movementSpeed * deltaTime), coordinates.y
                }))
                {
                    moveAmount.x = 0.0f;
                }
            }
        }
    }

    moveAmount = normalise(moveAmount);

    coordinates.x += static_cast<float>(moveAmount.x * movementSpeed * deltaTime);
    coordinates.y += static_cast<float>(moveAmount.y * movementSpeed * deltaTime);
}

void Player::takeDamage() const
{
    health -= 5;
    if (health <= 0) health = 0;
}
