//
// Created by david on 06/04/24.
//

#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::goCrazy()
{
    rect.x += rand() % 19 + (-9);
    rect.y += rand() % 19 + (-9);
}
