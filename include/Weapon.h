#ifndef WEAPON_H
#define WEAPON_H

#pragma once

namespace Weapon
{
    void fireShotgun(Vector2D origin, Vector2D target, Game* game);
    void fireRifle(Vector2D origin, Vector2D target, Game* game);
    void fireUzi(const Vector2D* origin, const Vector2D* target, Game* game, const bool* mouseHeld);
}

#endif //WEAPON_H
