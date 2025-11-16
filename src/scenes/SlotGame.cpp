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

    // Завантаження аудіо
    if (backgroundAudio.load("assets/audio/background.ogg")) {
        backgroundAudio.setVolume(0.6f);
        backgroundAudio.play(true);
    }
    spinAudio.load("assets/audio/spin.ogg");
    coinsAudio.load("assets/audio/coins.ogg");
    winAudio.load("assets/audio/win.ogg");
    jackpotAudio.load("assets/audio/jackpot.ogg");

    // Масив вказівників на символи
    slotSymbols.push_back(&seven);
    slotSymbols.push_back(&cherry);
    slotSymbols.push_back(&bell);

    // Початковий стан
    leverActive = false;
    spinTimer = 0.0f;
    spinStepTimer = 0.0f;
    reels.fill(0);
}

void SlotGame::update(float dt, const Input& input) {
    float mx = input.mouseX;
    float my = input.mouseY;

    // Курсор на важіль
    if (mx >= 672 && mx <= 751 && my >= 300 && my <= 600) {
        al_set_system_mouse_cursor(al_get_current_display(), ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
    } else {
        al_set_system_mouse_cursor(al_get_current_display(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    }

    // Старт спіну
    if (!leverActive && input.isMouseJustPressed(0)) {
        if (mx >= 672 && mx <= 751 && my >= 300 && my <= 600) {
            leverActive = true;
            spinTimer = 0.8f;  // тривалість спіну
            spinStepTimer = 0.0f;
            spinAudio.play(false);
        }
    }

    if (leverActive) {
        spinTimer -= dt;
        spinStepTimer -= dt;

        // Анімація обертання символів
        if (spinStepTimer <= 0.0f) {
            spinStepTimer = 0.05f;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, slotSymbols.size() - 1);

            // Копіюємо випадкові символи в барабани
            symbol1 = *slotSymbols[dist(gen)];
            symbol1.position = Point2D(235, 300);

            symbol2 = *slotSymbols[dist(gen)];
            symbol2.position = Point2D(365, 300);

            symbol3 = *slotSymbols[dist(gen)];
            symbol3.position = Point2D(495, 300);
        }

        // Кінець спіну
        if (spinTimer <= 0.0f) {
            leverActive = false;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, slotSymbols.size() - 1);

            // Вибираємо фінальні символи
            for (int i = 0; i < 3; i++) {
                reels[i] = dist(gen);
            }

            // Присвоюємо фінальні символи
            symbol1 = *slotSymbols[reels[0]];
            symbol1.position = Point2D(235, 300);

            symbol2 = *slotSymbols[reels[1]];
            symbol2.position = Point2D(365, 300);

            symbol3 = *slotSymbols[reels[2]];
            symbol3.position = Point2D(495, 300);

            // Перевірка виграшу
            if (reels[0] == reels[1] && reels[1] == reels[2]) {
                jackpotAudio.play(false);
                std::cout << "JACKPOT!" << std::endl;
            } else if (reels[0] == reels[1] || reels[1] == reels[2] || reels[2] == reels[0]) {
                winAudio.play(false);
                coinsAudio.play(false);
            }
        }
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
}
