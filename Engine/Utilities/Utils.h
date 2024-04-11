#ifndef ARNOLD_UTILS_H
#define ARNOLD_UTILS_H

#include "Geometry.h"
#include <ctgmath>
#include <SDL2/SDL_mixer.h>

namespace Utils {
    Coordinates normalise(Coordinates coordinates);

    namespace Audio {
        Mix_Chunk *loadMedia(const char *path);

        void playSound(Mix_Chunk *audio);
    }
}

#endif //ARNOLD_UTILS_H
