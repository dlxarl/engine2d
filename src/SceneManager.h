#pragma once
#include "scenes/headers/Scene.h"

class SceneManager {
private:
    Scene* current = nullptr;

public:
    SceneManager(Scene* startScene);
    ~SceneManager();

    void update(float deltaTime, const Input& input);
    void draw(Renderer& r);

    bool isRunning() const;
};

void update(float deltaTime, const Input& input);