#include "headers/Scene1.h"
#include "headers/Scene2.h"

Scene1::Scene1()
    : line(Point2D(100, 100), Point2D(700, 100), Color(255, 0, 0)),
      rect(Point2D(300, 100), 150, 100, Color(0, 255, 0), Color(0, 0, 0)),
      circle(Point2D(400, 400), 80, Color(0, 0, 255)),
      triangle(Point2D(600, 300), 60, Color(255, 255, 0)),
      image("assets/test_static.png", Point2D(400, 300)),
      anim("assets/samurai/ATTACK.png", 96, 96, 7, 0.05f, Point2D(200, 200), 4.0f)
{}

void Scene1::update(float dt, const Input& input) {
    timer += dt;
    anim.update(dt);

    // Рух прямокутника стрілками
    float rectSpeed = 2.0f;
    if (input.isKeyPressed(ALLEGRO_KEY_LEFT)) {
        rect.pos.x -= rectSpeed;
    }
    if (input.isKeyPressed(ALLEGRO_KEY_RIGHT)) {
        rect.pos.x += rectSpeed;
    }
    if (input.isKeyPressed(ALLEGRO_KEY_UP)) {
        rect.pos.y -= rectSpeed;
    }
    if (input.isKeyPressed(ALLEGRO_KEY_DOWN)) {
        rect.pos.y += rectSpeed;
    }

    // Circle follows cursor
    circle.center.x = input.mouseX;
    circle.center.y = input.mouseY;

    // Switch filling
    if (input.isKeyJustPressed(ALLEGRO_KEY_F)) {
        circle.toggleFill();
    }

    if (input.isKeyJustPressed(ALLEGRO_KEY_T)) {
        triangle.toggleFill();
    }

    // End scene
    if (input.isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        timer = 999.0f;
    }

    triangle.update();
}

void Scene1::draw(Renderer& r) {
    line.draw(r);
    rect.draw(r);
    circle.draw(r);
    triangle.draw(r);
    image.draw(r);
    anim.draw(r);
}

bool Scene1::isFinished() const {
    return timer > 5.0f;
}

Scene* Scene1::nextScene() const {
    return new Scene2();
}