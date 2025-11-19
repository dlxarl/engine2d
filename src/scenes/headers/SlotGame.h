#pragma once
#include "Scene.h"
#include "BitmapShape.h"
#include "AudioPlayer.h"
#include "FileManager.h"
#include "LineShape.h"
#include "AnimatedBitmap.h"
#include <array>
#include <vector>

/**
 * @brief Scena gry slotowej (SlotGame) w silniku 2D.
 *
 * Reprezentuje mini-grę kasynową z automatem do gry (slot machine).
 * Zawiera tło, dźwięki, animacje, symbole oraz logikę zakładów i wygranych.
 */
class SlotGame : public Scene {
private:
    /// Tło gry
    BitmapShape background;

    /// Automat slotowy (animowany)
    AnimatedBitmap machine;

    /// Dźwignia w pozycji górnej
    BitmapShape leverUp;

    /// Dźwignia w pozycji dolnej
    BitmapShape leverDown;

    /// Symbole slotów
    BitmapShape symbol1;
    BitmapShape symbol2;
    BitmapShape symbol3;

    /// Specjalne symbole
    BitmapShape seven;
    BitmapShape cherry;
    BitmapShape bell;

    /// Dźwięki gry
    AudioPlayer backgroundAudio;
    AudioPlayer spinAudio;
    AudioPlayer coinsAudio;
    AudioPlayer winAudio;
    AudioPlayer jackpotAudio;

    /// Linie wygranej
    LineShape* winLine = nullptr;
    LineShape* extraWinLine = nullptr;

    /// Flaga aktywności dźwigni
    bool leverActive = false;

    /// Timer animacji obrotu slotów
    float spinTimer = 0.0f;

    /// Timer kroku animacji obrotu
    float spinStepTimer = 0.0f;

    /// Wskaźniki do symboli slotów
    std::vector<BitmapShape*> slotSymbols;

    /// Aktualne symbole na bębnach
    std::array<int, 3> reels;

    /// Kredyty gracza
    int playerCredits = 100;

    /// Kwota zakładu
    int betAmount = 10;

    /// Flaga animacji jackpota
    bool jackpotAnimating = false;

    /// Timer animacji jackpota
    float jackpotTimer = 0.0f;

    /**
     * @brief Zastosowanie wygranej do kredytów gracza.
     */
    void applyWin();

    /**
     * @brief Zapis stanu kredytów do pliku.
     */
    void saveBalance();

    /**
     * @brief Wczytanie stanu kredytów z pliku.
     */
    void loadBalance();

public:
    /**
     * @brief Konstruktor gry slotowej.
     *
     * Inicjalizuje wszystkie symbole, tło, animacje oraz dźwięki.
     */
    SlotGame();

    /**
     * @brief Aktualizuje logikę gry.
     *
     * Obraca sloty, obsługuje dźwignię, wygrane oraz input od gracza.
     *
     * @param dt Czas od ostatniej aktualizacji w sekundach
     * @param input Obiekt klasy Input do obsługi klawiatury i myszy
     */
    void update(float dt, const Input& input) override;

    /**
     * @brief Rysuje scenę gry slotowej.
     *
     * Rysuje tło, automat, symbole, linie wygranych i animacje.
     *
     * @param r Obiekt Renderer używany do rysowania
     */
    void draw(Renderer& r) override;
};
