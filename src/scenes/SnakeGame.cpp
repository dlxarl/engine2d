#include "headers/SnakeGame.h"
#include "headers/Scene1.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

SnakeGame::SnakeGame() {
    snake.push_back(Point2D(200, 200));
    snake.push_back(Point2D(180, 200));
    snake.push_back(Point2D(160, 200));
}

void SnakeGame::update(float dt, const Input& input) {
    moveTimer += dt;

    // Зміна напрямку
    if (input.isKeyJustPressed(ALLEGRO_KEY_UP) && dir != Direction::DOWN) dir = Direction::UP;
    if (input.isKeyJustPressed(ALLEGRO_KEY_DOWN) && dir != Direction::UP) dir = Direction::DOWN;
    if (input.isKeyJustPressed(ALLEGRO_KEY_LEFT) && dir != Direction::RIGHT) dir = Direction::LEFT;
    if (input.isKeyJustPressed(ALLEGRO_KEY_RIGHT) && dir != Direction::LEFT) dir = Direction::RIGHT;

    // Вихід зі сцени
    if (input.isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        finished = true;
    }

    // Рух змійки
    if (moveTimer >= moveInterval) {
        moveTimer = 0.0f;

        Point2D head = snake.front();
        Point2D newHead = head;

        switch (dir) {
            case Direction::UP:    newHead.y -= 20; break;
            case Direction::DOWN:  newHead.y += 20; break;
            case Direction::LEFT:  newHead.x -= 20; break;
            case Direction::RIGHT: newHead.x += 20; break;
        }

        snake.insert(snake.begin(), newHead);
        snake.pop_back();
    }
}

void SnakeGame::draw(Renderer& r) {
    r.clear(Color(0, 0, 0));
    al_draw_filled_rectangle(200, 200, 220, 220, al_map_rgb(0, 255, 0));

    for (const auto& segment : snake) {
        al_draw_filled_rectangle(
            segment.x, segment.y,
            segment.x + 18, segment.y + 18,
            al_map_rgb(0, 255, 0)
        );
    }
}

bool SnakeGame::isFinished() const {
    return finished;
}

Scene* SnakeGame::nextScene() const {
    return new Scene1(); // або nullptr
}