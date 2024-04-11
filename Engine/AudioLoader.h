#ifndef ARNOLD_AUDIOLOADER_H
#define ARNOLD_AUDIOLOADER_H

#include <SDL2/SDL_mixer.h>

class AudioLoader {

public:
    static AudioLoader &getInstance() {
        static AudioLoader instance;
        return instance;
    }

    static bool init();

    Mix_Chunk *loadMedia(const char *path);

    void playSound(Mix_Chunk *audio);


private:
    AudioLoader();

    ~AudioLoader();


};


#endif //ARNOLD_AUDIOLOADER_H
