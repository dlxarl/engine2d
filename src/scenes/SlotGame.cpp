#include "headers/SlotGame.h"
#include "DefinePoint.h"
#include <random>
#include <iostream>

DefinePoint devPointTool;

SlotGame::SlotGame()
    : background("assets/img/bg.png", Point2D(0, 0)),
      machine("assets/img/slot-machine.png", Point2D(0, 0)),
      leverUp("assets/img/leverUp.png", Point2D(0, 0)),
      leverDown("assets/img/leverDown.png", Point2D(0, 0)),
      symbol1("assets/img/seven.png", Point2D(235, 300)),
      symbol2("assets/img/cherry.png", Point2D(365, 300)),
      symbol3("assets/img/bell.png", Point2D(495, 300)),
      seven("assets/img/seven.png", Point2D(0,0)),
      cherry("assets/img/cherry.png", Point2D(0,0)),
      bell("assets/img/bell.png", Point2D(0,0))
{
    devPointTool.setEnabled(false);

    if (backgroundAudio.load("assets/audio/background.ogg")) {
        backgroundAudio.setVolume(0.6f);
        backgroundAudio.play(true);
    }
    spinAudio.load("assets/audio/spin.ogg");
    coinsAudio.load("assets/audio/coins.ogg");
    winAudio.load("assets/audio/win.ogg");
    jackpotAudio.load("assets/audio/jackpot.ogg");

    slotSymbols.push_back(&seven);
    slotSymbols.push_back(&cherry);
    slotSymbols.push_back(&bell);

    leverActive = false;
    spinTimer = 0.0f;
    spinStepTimer = 0.0f;
    reels.fill(0);

    loadBalance();
}

void SlotGame::update(float dt, const Input& input) {
    float mx = input.mouseX;
    float my = input.mouseY;

    if (mx >= 672 && mx <= 751 && my >= 300 && my <= 600) {
        al_set_system_mouse_cursor(al_get_current_display(), ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
    } else {
        al_set_system_mouse_cursor(al_get_current_display(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    }

    if (!leverActive && input.isMouseJustPressed(0)) {
        if (mx >= 672 && mx <= 751 && my >= 300 && my <= 600) {
            leverActive = true;
            spinTimer = 0.8f;
            spinStepTimer = 0.0f;
            spinAudio.play(false);

            winLine = nullptr;
            extraWinLine = nullptr;

            // списуємо ставку
            playerCredits -= betAmount;
            std::cout << "Spin started. Bet: -" << betAmount
                      << " | Balance: " << playerCredits << std::endl;
        }
    }

    if (leverActive) {
        spinTimer -= dt;
        spinStepTimer -= dt;

        if (spinStepTimer <= 0.0f) {
            spinStepTimer = 0.05f;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, slotSymbols.size() - 1);

            symbol1 = *slotSymbols[dist(gen)];
            symbol1.position = Point2D(235, 300);

            symbol2 = *slotSymbols[dist(gen)];
            symbol2.position = Point2D(365, 300);

            symbol3 = *slotSymbols[dist(gen)];
            symbol3.position = Point2D(495, 300);
        }

        if (spinTimer <= 0.0f) {
            leverActive = false;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, slotSymbols.size() - 1);

            for (int i = 0; i < 3; i++) {
                reels[i] = dist(gen);
            }

            symbol1 = *slotSymbols[reels[0]];
            symbol1.position = Point2D(235, 300);

            symbol2 = *slotSymbols[reels[1]];
            symbol2.position = Point2D(365, 300);

            symbol3 = *slotSymbols[reels[2]];
            symbol3.position = Point2D(495, 300);

            applyWin();

            saveBalance();
        }
    }
}

void SlotGame::applyWin() {
    winLine = nullptr;
    int lineY = 470;

    if (reels[0] == reels[1] && reels[1] == reels[2]) {
        int win = betAmount * 5;
        playerCredits += win;
        jackpotAudio.play(false);
        std::cout << "JACKPOT! +" << win
                  << " | Balance: " << playerCredits << std::endl;
    winLine = new LineShape(Point2D(230, lineY), Point2D(595, lineY), Color(255, 0, 0));
    } else if (reels[0] == reels[1] || reels[1] == reels[2] || reels[2] == reels[0]) {
        int win = betAmount * 2;
        playerCredits += win;
        winAudio.play(false);
        coinsAudio.play(false);
        std::cout << "WIN +" << win
                  << " | Balance: " << playerCredits << std::endl;
        if (reels[0] == reels[1]) {
            winLine = new LineShape(Point2D(230, lineY), Point2D(464, lineY), Color(0, 255, 0));
        } else if (reels[1] == reels[2]) {
            winLine = new LineShape(Point2D(357, lineY), Point2D(595, lineY), Color(0, 255, 0));
        } else {
            LineShape* line1 = new LineShape(Point2D(230, lineY), Point2D(337, lineY), Color(0, 255, 0));
            LineShape* line2 = new LineShape(Point2D(488, lineY), Point2D(595, lineY), Color(0, 255, 0));
            winLine = line1;
            extraWinLine = line2;
        }
    } else {
        std::cout << "No win. Balance: " << playerCredits << std::endl;
    }
}

void SlotGame::saveBalance() {
    FileManager::saveToFile("balance.txt", std::to_string(playerCredits));
}

void SlotGame::loadBalance() {
    std::string data;
    if (FileManager::loadFromFile("balance.txt", data)) {
        try {
            playerCredits = std::stoi(data);
        } catch (...) {
            playerCredits = 100;
        }
    } else {
        playerCredits = 100;
        saveBalance();
        std::cout << "Balance file not found. Created new with 100 credits." << std::endl;
    }
}


void SlotGame::draw(Renderer& r) {
    background.draw(r);
    machine.draw(r);

    if (leverActive)
        leverDown.draw(r);
    else
        leverUp.draw(r);

    symbol1.draw(r);
    symbol2.draw(r);
    symbol3.draw(r);

    if (winLine) {
    winLine->draw(r);
    LineShape extra1(winLine->p1 + Point2D(0, 1), winLine->p2 + Point2D(0, 1), winLine->color);
    LineShape extra2(winLine->p1 + Point2D(0, -1), winLine->p2 + Point2D(0, -1), winLine->color);
    extra1.draw(r);
    extra2.draw(r);
    }

    if (extraWinLine) {
        extraWinLine->draw(r);
        LineShape extra3(extraWinLine->p1 + Point2D(0, 1), extraWinLine->p2 + Point2D(0, 1), extraWinLine->color);
        LineShape extra4(extraWinLine->p1 + Point2D(0, -1), extraWinLine->p2 + Point2D(0, -1), extraWinLine->color);
        extra3.draw(r);
        extra4.draw(r);
}
}
