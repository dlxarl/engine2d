#pragma once
#include "Scene.h"
#include "BitmapShape.h"
#include "AudioPlayer.h"

class SlotGame : public Scene {
private:
    BitmapShape background;
    BitmapShape machine;
    BitmapShape leverUp;
    BitmapShape leverDown;
    BitmapShape symbol1;
    BitmapShape symbol2;
    BitmapShape symbol3;

    AudioPlayer backgroundAudio;
    AudioPlayer spinAudio;
    AudioPlayer coinsAudio;
    AudioPlayer winAudio;
    AudioPlayer jackpotAudio;

    bool leverActive = false;
    float spinTimer = 0.0f;
    bool bgMutedForEffect = false;

public:
    SlotGame();
    void update(float dt, const Input& input) override;
    void draw(Renderer& r) override;
};