#pragma once
#include "Scene.h"
#include "BitmapShape.h"
#include "AudioPlayer.h"
#include "FileManager.h"
#include "LineShape.h"
#include "AnimatedBitmap.h"
#include <array>
#include <vector>

class SlotGame : public Scene {
private:
    BitmapShape background;
    AnimatedBitmap machine;
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

    LineShape* winLine = nullptr;
    LineShape* extraWinLine = nullptr;

    bool leverActive = false;
    float spinTimer = 0.0f;
    float spinStepTimer = 0.0f;

    std::vector<BitmapShape*> slotSymbols;
    std::array<int, 3> reels;

    int playerCredits = 100;
    int betAmount = 10;

    bool jackpotAnimating = false;
    float jackpotTimer = 0.0f;

    void applyWin();
    void saveBalance();
    void loadBalance();

public:
    SlotGame();
    void update(float dt, const Input& input) override;
    void draw(Renderer& r) override;
};
