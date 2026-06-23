#ifndef SPEAKER_H
#define SPEAKER_H

#include <SDL2/SDL_audio.h>
#include <SDL2/SDL.h>
#include <atomic>
#include <algorithm>

struct AudioState
{
    std::atomic<bool> playing{false};
    std::atomic<float> volume{0.25f};
    float phase = 0.0f;
};

class Speaker
{
public:
    Speaker();
    ~Speaker();

    void start();
    void stop();
    void setVolume(float volume);

private:
    static void audio_callback(
        void* userdata,
        Uint8* stream,
        int len);

private:
    SDL_AudioDeviceID device_{0};
    AudioState state_;
};

#endif //SPEAKER_H