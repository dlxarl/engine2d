#pragma once
#include "Scene.h"
#include "BitmapShape.h"
#include "AudioPlayer.h"
#include <array>
#include <vector>

class SlotGame : public Scene {
private:
    BitmapShape background;
    BitmapShape machine;
    BitmapShape leverUp;
    BitmapShape leverDown;
    BitmapShape symbol1;
    BitmapShape symbol2;
    BitmapShape symbol3;

    BitmapShape seven;
    BitmapShape cherry;
    BitmapShape bell;

    AudioPlayer backgroundAudio;
    AudioPlayer spinAudio;
    AudioPlayer coinsAudio;
    AudioPlayer winAudio;
    AudioPlayer jackpotAudio;

    bool leverActive = false;
    float spinTimer = 0.0f;
    float spinStepTimer = 0.0f;
    bool bgMutedForEffect = false;

    // --- Для спіну ---
    std::vector<BitmapShape*> slotSymbols; // усі доступні символи
    std::array<int, 3> reels;           // фінальні символи для трьох барабанів


public:
    SlotGame();
    void update(float dt, const Input& input) override;
    void draw(Renderer& r) override;
};
