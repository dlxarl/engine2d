#pragma once
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>

/**
 * @class AudioPlayer
 * @brief Klasa odpowiedzialna za odtwarzanie efektów dźwiękowych i muzyki.
 *
 * Udostępnia funkcje ładowania pliku audio, odtwarzania, zatrzymywania
 * oraz regulacji głośności. Wykorzystuje Allegro 5 Audio API.
 */
class AudioPlayer {
private:
    ALLEGRO_SAMPLE* sample = nullptr;              ///< Załadowana próbka dźwiękowa
    ALLEGRO_SAMPLE_INSTANCE* instance = nullptr;   ///< Instancja próbki używana do odtwarzania

public:
    /**
     * @brief Konstruktor inicjalizujący odtwarzacz audio.
     *
     * Tworzy obiekt, ale nie ładuje jeszcze pliku dźwiękowego.
     */
    AudioPlayer();

    /**
     * @brief Destruktor zwalniający pamięć próbek audio.
     */
    ~AudioPlayer();

    /**
     * @brief Ładuje plik dźwiękowy z dysku.
     *
     * @param filename Ścieżka do pliku audio (np. .wav, .ogg)
     * @return true jeśli wczytano poprawnie, false w przypadku błędu
     */
    bool load(const std::string& filename);

    /**
     * @brief Odtwarza dźwięk.
     *
     * Jeśli wcześniej załadowano plik, metoda uruchamia jego odtwarzanie.
     *
     * @param loop Czy dźwięk ma odtwarzać się w pętli
     */
    void play(bool loop = true);

    /**
     * @brief Zatrzymuje aktualnie odtwarzany dźwięk.
     */
    void stop();

    /**
     * @brief Ustawia głośność odtwarzanego dźwięku.
     *
     * @param volume Głośność w zakresie 0.0–1.0
     */
    void setVolume(float volume);

    /**
     * @brief Sprawdza, czy dźwięk jest aktualnie odtwarzany.
     *
     * @return true jeśli dźwięk gra, false jeśli jest zatrzymany
     */
    bool isPlaying() const;
};
