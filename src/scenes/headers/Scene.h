#pragma once
#include "Renderer.h"
#include "Input.h"

class Scene {
public:
    virtual ~Scene() = default;
    virtual void update(float deltaTime, const Input& input) = 0;
    virtual void draw(Renderer& r) = 0;
    virtual bool isFinished() const { return false; }
    virtual Scene* nextScene() const { return nullptr; }
};