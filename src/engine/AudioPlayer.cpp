#include "AudioPlayer.h"
#include <iostream>

/**
 * @brief Konstruktor klasy AudioPlayer.
 *
 * Inicjalizuje system audio Allegro i dodatek do obsługi kodeków.
 * Rezerwuje miejsce na próbki dźwiękowe.
 */
AudioPlayer::AudioPlayer() {
    if (!al_is_audio_installed()) {
        al_install_audio();
    }
    if (!al_is_acodec_addon_initialized()) {
        al_init_acodec_addon();
    }
    al_reserve_samples(8);
}

/**
 * @brief Destruktor klasy AudioPlayer.
 *
 * Zwalnia pamięć zajętą przez próbki i instancje próbek.
 */
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

/**
 * @brief Wczytuje plik audio i tworzy instancję próbki.
 *
 * @param filename Ścieżka do pliku audio
 * @return true jeśli wczytanie powiodło się, false w przypadku błędu
 */
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

/**
 * @brief Odtwarza wczytany plik audio.
 *
 * @param loop Jeśli true, odtwarzanie będzie w pętli
 */
void AudioPlayer::play(bool loop) {
    if (!instance) return;
    al_set_sample_instance_playmode(instance, loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE);
    al_play_sample_instance(instance);
}

/**
 * @brief Zatrzymuje odtwarzanie próbki audio.
 */
void AudioPlayer::stop() {
    if (instance) {
        al_stop_sample_instance(instance);
    }
}

/**
 * @brief Ustawia głośność odtwarzanej próbki.
 *
 * @param volume Poziom głośności w zakresie 0.0 (cisza) – 1.0 (maksimum)
 */
void AudioPlayer::setVolume(float volume) {
    if (instance) {
        al_set_sample_instance_gain(instance, volume);
    }
}

/**
 * @brief Sprawdza, czy próbka audio jest aktualnie odtwarzana.
 *
 * @return true jeśli odtwarzanie trwa, false w przeciwnym wypadku
 */
bool AudioPlayer::isPlaying() const {
    return instance ? al_get_sample_instance_playing(instance) : false;
}
