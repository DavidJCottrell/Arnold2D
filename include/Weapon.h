#ifndef WEAPON_H
#define WEAPON_H

#pragma once

namespace Weapon
{
    void fireShotgun(Vector2D origin, Vector2D target, Game* game, Mix_Chunk* sound);
    void fireRifle(Vector2D origin, Vector2D target, Game* game, Mix_Chunk* sound);
    void fireUzi(const Vector2D* origin, const Vector2D* target, Game* game, const bool* mouseHeld, Mix_Chunk* sound);
}

#endif //WEAPON_H
