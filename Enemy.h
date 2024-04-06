//
// Created by david on 06/04/24.
//

#ifndef ARNOLD_ENEMY_H
#define ARNOLD_ENEMY_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy();
    Enemy(int id, int x, int y) : Entity(x, y) { ID = id; }
    ~Enemy();

    int ID;

    void goCrazy();
};


#endif //ARNOLD_ENEMY_H
