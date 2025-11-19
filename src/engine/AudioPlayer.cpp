#include "AudioPlayer.h"
#include <iostream>

AudioPlayer::AudioPlayer() {
    if (!al_is_audio_installed()) {
        al_install_audio();
    }
    if (!al_is_acodec_addon_initialized()) {
        al_init_acodec_addon();
    }
    al_reserve_samples(8);
}

AudioPlayer::~AudioPlayer() {
    if (instance) {
        al_destroy_sample_instance(instance);
        instance = nullptr;
    }
    if (sample) {
        al_destroy_sample(sample);
        sample = nullptr;
    }
}

bool AudioPlayer::load(const std::string& filename) {
    sample = al_load_sample(filename.c_str());
    if (!sample) {
        std::cerr << "Failed to load audio: " << filename << std::endl;
        return false;
    }
    instance = al_create_sample_instance(sample);
    if (!instance) {
        std::cerr << "Failed to create sample instance!" << std::endl;
        return false;
    }
    al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
    return true;
}

void AudioPlayer::play(bool loop) {
    if (!instance) return;
    al_set_sample_instance_playmode(instance, loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE);
    al_play_sample_instance(instance);
}

void AudioPlayer::stop() {
    if (instance) {
        al_stop_sample_instance(instance);
    }
}

void AudioPlayer::setVolume(float volume) {
    if (instance) {
        al_set_sample_instance_gain(instance, volume);
    }
}

bool AudioPlayer::isPlaying() const {
    return instance ? al_get_sample_instance_playing(instance) : false;
}