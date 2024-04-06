//
// Created by david on 06/04/24.
//

#include "Game.h"

bool Game::init(const char *title,
                int xpos, int ypos,
                int width, int height)
{
    isRunning = false;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Failed to init SDL!\n");
        return false;
    }

    window = SDL_CreateWindow(
            title,
            xpos, ypos,
            width, height,
            SDL_WINDOW_SHOWN);

    printf("%d", getRefreshRate());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    spawnEntities(width, height);

    isRunning = true;
    return true;
}

void Game::spawnEntities(int width, int height)
{
    player = Player(width / 2, height / 2);

    enemies.push_back(Enemy(1, (width / 2) + 50, (height / 2) + 50));
    enemies.push_back(Enemy(2, (width / 2) + 100, (height / 2) + 100));
}

int Game::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}

bool isArrowKey(SDL_Keycode key)
{
    return key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT || key == SDLK_LEFT;
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (isArrowKey(sdlEvent.key.keysym.sym))
                {
                    player.isMoving = true;
                    pressedKey = sdlEvent.key.keysym.sym;
                }
                break;
            case SDL_KEYUP:
                if (isArrowKey(sdlEvent.key.keysym.sym))
                    player.isMoving = false;
                break;
            default:
                break;
        }
    }
    if (player.isMoving)
    {
        switch (pressedKey)
        {
            case SDLK_UP:
                player.moveUp();
                break;
            case SDLK_DOWN:
                player.moveDown();
                break;
            case SDLK_LEFT:
                player.moveLeft();
                break;
            case SDLK_RIGHT:
                player.moveRight();
                break;
            default:
                break;
        }
    }
}

bool Game::isPlayerEnemyColliding()
{
    for (Enemy &enemy : enemies)
    {
        bool isColliding = player.rect.x < enemy.rect.x + enemy.rect.w &&
                           player.rect.x + player.rect.w > enemy.rect.x &&
                           player.rect.y < enemy.rect.y + enemy.rect.h &&
                           player.rect.y + player.rect.h > enemy.rect.y;
        if (isColliding)
            return true;
    }
    return false;
}

void Game::update()
{
    for (Enemy &enemy : enemies)
    {
        enemy.goCrazy();

        // check if player is within the bounds of an enemy
        isColliding = player.rect.x < enemy.rect.x + enemy.rect.w &&
                      player.rect.x + player.rect.w > enemy.rect.x &&
                      player.rect.y < enemy.rect.y + enemy.rect.h &&
                      player.rect.y + player.rect.h > enemy.rect.y;

        if (isColliding && enemy.ID != collidedEnemyId)
        {
            collidedEnemyId = enemy.ID;
            collisionCount++;
            std::cout << "Collision #" << collisionCount << " with enemy: " << collidedEnemyId << std::endl;
        }
    }
    if (!isPlayerEnemyColliding())
        collidedEnemyId = -1;
}

void Game::render()
{
    SDL_RenderClear(renderer);

    for (Enemy &enemy : enemies)
    {
        enemy.render(renderer);
    }

    player.render(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game cleaned\n");
}
