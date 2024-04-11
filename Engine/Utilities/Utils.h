#ifndef ARNOLD_UTILS_H
#define ARNOLD_UTILS_H

#include <ctgmath>
#include <SDL2/SDL_mixer.h>

namespace Utils {

    namespace Geometry {

        struct Vector2D {
            float x;
            float y;
        };

        Vector2D normalise(Vector2D coordinates);

        Vector2D getUnitVector(Vector2D origin, Vector2D destination);
    }

    namespace Audio {
        Mix_Chunk *loadMedia(const char *path);

        void playSound(Mix_Chunk *audio);
    }
}

#endif //ARNOLD_UTILS_H
