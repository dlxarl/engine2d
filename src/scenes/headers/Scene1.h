#pragma once
#include "Scene.h"
#include "LineShape.h"
#include "RectangleShape.h"
#include "CircleShape.h"
#include "TriangleShape.h"
#include "BitmapShape.h"
#include "AnimatedBitmap.h"

class Scene1 : public Scene {
private:
    LineShape line;
    RectangleShape rect;
    CircleShape circle;
    TriangleShape triangle;
    BitmapShape image;
    AnimatedBitmap anim;

    float timer = 0;

public:
    Scene1();
    void update(float dt, const Input& input) override;
    void draw(Renderer& r) override;
    bool isFinished() const override;
    Scene* nextScene() const override;
};