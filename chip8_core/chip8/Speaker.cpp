#include "Speaker.h"

#include <cmath>
#include <cstring>
#include <stdexcept>

Speaker::Speaker()
{
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) != 0)
    {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_AudioSpec desired{};
    SDL_AudioSpec obtained{};

    desired.freq = 44100;
    desired.format = AUDIO_F32SYS;
    desired.channels = 1;
    desired.samples = 512;
    desired.callback = audio_callback;
    desired.userdata = &state_;

    device_ = SDL_OpenAudioDevice(
        nullptr,
        0,
        &desired,
        &obtained,
        0);

    if (device_ == 0)
    {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_PauseAudioDevice(device_, 0);
}

Speaker::~Speaker()
{
    if (device_ != 0)
        SDL_CloseAudioDevice(device_);
}

void Speaker::start()
{
    state_.playing = true;
}

void Speaker::stop()
{
    state_.playing = false;
}

void Speaker::audio_callback(
    void* userdata,
    Uint8* stream,
    int len)
{
    AudioState* state =
        static_cast<AudioState*>(userdata);

    float* buffer =
        reinterpret_cast<float*>(stream);

    int samples = len / sizeof(float);

    constexpr float frequency = 440.0f;
    constexpr float sample_rate = 44100.0f;

    float volume = state->volume.load(std::memory_order_relaxed);

    for (int i = 0; i < samples; ++i)
    {
        if (state->playing)
        {
            buffer[i] =
                buffer[i] =
                ((state->phase < 0.5) ? 0.25f : -0.25f)
                * state->volume;

            state->phase += frequency / sample_rate;

            if (state->phase >= 1.0)
                state->phase -= 1.0;
        }
        else
        {
            buffer[i] = 0.0f;
        }
    }
}

void Speaker::setVolume(float volume)
{
    state_.volume = std::clamp(volume, 0.0f, 1.0f);
}