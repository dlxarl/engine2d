#pragma once
#include "Scene.h"
#include "Input.h"
#include "Point2D.h"
#include "Color.h"
#include <vector>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class SnakeGame : public Scene {
private:
    std::vector<Point2D> snake;
    Direction dir = Direction::RIGHT;
    float moveTimer = 0.0f;
    float moveInterval = 0.2f;
    bool finished = false;

public:
    SnakeGame();
    void update(float dt, const Input& input) override;
    void draw(Renderer& r) override;
    bool isFinished() const override;
    Scene* nextScene() const override;
};