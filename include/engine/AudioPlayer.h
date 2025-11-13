#pragma once
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>

class AudioPlayer {
private:
    ALLEGRO_SAMPLE* sample = nullptr;
    ALLEGRO_SAMPLE_INSTANCE* instance = nullptr;

public:
    AudioPlayer();
    ~AudioPlayer();

    bool load(const std::string& filename);
    void play(bool loop = true);
    void stop();

    void setVolume(float volume);
    bool isPlaying() const;
};