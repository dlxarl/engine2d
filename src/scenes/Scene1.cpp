#include "headers/Scene1.h"
#include "headers/Scene2.h"

Scene1::Scene1()
    : line(Point2D(100, 100), Point2D(700, 100), Color(255, 0, 0)),
      rect(Point2D(300, 100), 150, 100, Color(0, 255, 0)),
      circle(Point2D(400, 400), 80, Color(0, 0, 255)),
      triangle(Point2D(600, 300), 60, Color(255, 255, 0)),
      image("assets/test_static.png", Point2D(400, 300)),
      anim("assets/samurai/ATTACK.png", 96, 96, 7, 0.05f, Point2D(200, 200), 4.0f)
{
    anim.play(true);
}

void Scene1::update(float dt, const Input& input) {
    timer += dt;
    anim.update(dt);

    float moveSpeed = 2.0f;
    float rotateSpeed = 0.05f;
    float scaleStep = 1.01f;


    //if (input.isKeyPressed(ALLEGRO_KEY_LEFT))  rect.move(-moveSpeed, 0);
    //if (input.isKeyPressed(ALLEGRO_KEY_RIGHT)) rect.move(moveSpeed, 0);
    //if (input.isKeyPressed(ALLEGRO_KEY_UP))    rect.move(0, -moveSpeed);
    //if (input.isKeyPressed(ALLEGRO_KEY_DOWN))  rect.move(0, moveSpeed);


    if (input.isKeyPressed(ALLEGRO_KEY_Q)) rect.rotate(-rotateSpeed);
    if (input.isKeyPressed(ALLEGRO_KEY_E)) rect.rotate(rotateSpeed);


    if (input.isKeyPressed(ALLEGRO_KEY_W)) circle.scale(scaleStep);
    if (input.isKeyPressed(ALLEGRO_KEY_S)) circle.scale(1.0f/scaleStep);

    float animSpeed = 2.0f;
    if (input.isKeyPressed(ALLEGRO_KEY_LEFT)) {
        anim.position.x -= animSpeed;
    }

    if (input.isKeyPressed(ALLEGRO_KEY_RIGHT)) {
        anim.position.x += animSpeed;
    }
    if (input.isKeyPressed(ALLEGRO_KEY_UP)) {
        anim.position.y -= animSpeed;
    }
    if (input.isKeyPressed(ALLEGRO_KEY_DOWN)) {
        anim.position.y += animSpeed;
    }


    circle.position.x = input.mouseX;
    circle.position.y = input.mouseY;


    if (input.isKeyJustPressed(ALLEGRO_KEY_F)) {
        circle.toggleFill();
    }

    if (input.isKeyJustPressed(ALLEGRO_KEY_T)) {
        triangle.toggleFill();
    }

    if (input.isKeyJustPressed(ALLEGRO_KEY_K)) {
        rect.toggleFill();
    }


    if (input.isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        timer = 999.0f;
    }


}

void Scene1::draw(Renderer& r) {
    //line.draw(r);
    rect.draw(r);
    circle.draw(r);
    triangle.draw(r);
    //image.draw(r);
    anim.draw(r);
}

bool Scene1::isFinished() const {
    return timer > 5.0f;
}

Scene* Scene1::nextScene() const {
    return new Scene2();
}