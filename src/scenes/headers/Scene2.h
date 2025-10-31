#pragma once
#include "Scene.h"

class Scene2 : public Scene {
    float timer = 0;
    bool finished = false;
public:
    void update(float deltaTime, const Input& input) override;
    void draw(Renderer& r) override;
    bool isFinished() const override;
    Scene* nextScene() const override;
};