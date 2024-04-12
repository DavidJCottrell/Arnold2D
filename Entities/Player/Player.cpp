#include "Player.h"

void Player::registerMovementKey(SDL_Keycode key, bool isHeld)
{
    auto movementKey = movementKeys.find(key);
    if (movementKey != movementKeys.end())
        movementKey->second = isHeld;
}

Projectile Player::spawnProjectile(Vector2D destination)
{
    Vector2D direction = Utils::Geometry::getUnitVector(coordinates, destination);
    return {coordinates, game, direction};
}

void Player::handleEvents(SDL_Event sdlEvent)
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
        game->addEntity(spawnProjectile({(float)mouseX, (float)mouseY}));
        MessageHandler::getInstance().SendMsg("Pew");
        Utils::Audio::playSound(gunSound);
        break;
    }
    default:
        break;
    }
}

void Player::render(SDL_Renderer *renderer)
{

    int const scale = 3;

    // 17,
    // 21,

    SDL_Rect source = {
        17,
        21,
        dimensions.x,
        dimensions.y,
    };

    SDL_Rect dest = {
        coordinates.x,
        coordinates.y,
        dimensions.x * scale,
        dimensions.y * scale,
    };

    SDL_Surface *tempSurface = IMG_Load("../assets/sprites/characters/player.png");
    if (tempSurface == nullptr)
        printf("Failed to load image\n");
    SDL_Texture *playerTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_RenderCopy(renderer, playerTex, &source, &dest);

    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_Rect shape = {
    //         (int) coordinates.x,
    //         (int) coordinates.y,
    //         (int) dimensions.x,
    //         (int) dimensions.y,
    // };
    // SDL_RenderFillRect(renderer, &shape);
}

void Player::update(double deltaTime)
{
    // if (health <= 0)
    // {
    //     MessageHandler::getInstance().SendMsg("Game Over");
    //     game->endGame();
    // }

    Geometry::Vector2D moveAmount = {0.0f, 0.0f};

    for (auto &movementKey : movementKeys)
    {
        // Key is being pressed
        if (movementKey.second)
        {
            if (movementKey.first == SDLK_w)
                moveAmount.y -= 1.0f;
            if (movementKey.first == SDLK_a)
                moveAmount.x -= 1.0f;
            if (movementKey.first == SDLK_s)
                moveAmount.y += 1.0f;
            if (movementKey.first == SDLK_d)
                moveAmount.x += 1.0f;
        }
    }

    moveAmount = Geometry::normalise(moveAmount);

    coordinates.x += (float)(moveAmount.x * movementSpeed * deltaTime);
    coordinates.y += (float)(moveAmount.y * movementSpeed * deltaTime);
}

void Player::takeDamage(double damage) const
{
    health - damage;
}
