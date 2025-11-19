#include "headers/Scene1.h"
#include "headers/Scene2.h"

/**
 * @brief Konstruktor sceny Scene2
 *
 * Inicjalizuje różne kształty i animacje:
 * - linia, prostokąt, okrąg, trójkąt
 * - animacja RUN
 * - bitmapa statyczna jest zakomentowana
 */
Scene2::Scene2()
    : line(Point2D(100, 100), Point2D(700, 100), Color(255, 0, 0)),
      rect(Point2D(300, 100), 150, 100, Color(0, 255, 0)),
      circle(Point2D(400, 400), 80, Color(0, 0, 255)),
      triangle(Point2D(600, 300), 60, Color(255, 255, 0)),
      // image("assets/test_static.png", Point2D(400, 300)),
      anim("assets/samurai/RUN.png", 96, 96, 16, 0.05f, Point2D(200, 200), 4.0f)
{
    anim.play(true); ///< uruchomienie animacji w pętli
}

/**
 * @brief Aktualizacja logiki sceny Scene2
 *
 * Obsługuje:
 * - przesuwanie prostokąta strzałkami
 * - obrót trójkąta (Q/E)
 * - skalowanie okręgu (W/S)
 * - ustawienie pozycji okręgu według myszy
 * - włączanie/wyłączanie wypełnienia kształtów (F, T, K)
 * - zakończenie sceny po czasie > 5 sekund lub ESC
 *
 * @param dt Czas delta w sekundach
 * @param input Obiekt klasy Input
 */
void Scene2::update(float dt, const Input& input) {
    timer += dt;
    anim.update(dt);

    float moveSpeed = 2.0f;
    float rotateSpeed = 0.05f;
    float scaleStep = 1.01f;

    // Ruch prostokąta
    if (input.isKeyPressed(ALLEGRO_KEY_LEFT))  rect.move(-moveSpeed, 0);
    if (input.isKeyPressed(ALLEGRO_KEY_RIGHT)) rect.move(moveSpeed, 0);
    if (input.isKeyPressed(ALLEGRO_KEY_UP))    rect.move(0, -moveSpeed);
    if (input.isKeyPressed(ALLEGRO_KEY_DOWN))  rect.move(0, moveSpeed);

    // Obrót trójkąta
    if (input.isKeyPressed(ALLEGRO_KEY_Q)) triangle.rotate(-rotateSpeed);
    if (input.isKeyPressed(ALLEGRO_KEY_E)) triangle.rotate(rotateSpeed);

    // Skalowanie okręgu
    if (input.isKeyPressed(ALLEGRO_KEY_W)) circle.scale(scaleStep);
    if (input.isKeyPressed(ALLEGRO_KEY_S)) circle.scale(1.0f/scaleStep);

    // Aktualizacja pozycji okręgu zgodnie z pozycją myszy
    circle.position.x = input.mouseX;
    circle.position.y = input.mouseY;

    // Przełączanie wypełnienia kształtów
    if (input.isKeyJustPressed(ALLEGRO_KEY_F)) circle.toggleFill();
    if (input.isKeyJustPressed(ALLEGRO_KEY_T)) triangle.toggleFill();
    if (input.isKeyJustPressed(ALLEGRO_KEY_K)) rect.toggleFill();

    // Zakończenie sceny przy ESC
    if (input.isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        timer = 999.0f;
    }
}

/**
 * @brief Rysowanie sceny Scene2
 *
 * Wyświetla wszystkie kształty i animacje.
 *
 * @param r Obiekt Renderer
 */
void Scene2::draw(Renderer& r) {
    // line.draw(r); ///< Opcjonalna linia
    rect.draw(r);
    circle.draw(r);
    triangle.draw(r);
    // image.draw(r); ///< Zakomentowana bitmapa statyczna
    anim.draw(r);
}

/**
 * @brief Sprawdza, czy scena zakończona
 *
 * Scena kończy się po 5 sekundach lub przy naciśnięciu ESC.
 *
 * @return true jeśli scena zakończona
 */
bool Scene2::isFinished() const {
    return timer > 5.0f;
}

/**
 * @brief Zwraca wskaźnik na następną scenę
 *
 * @return wskaźnik na Scene1 (sceny się przełączają cyklicznie)
 */
Scene* Scene2::nextScene() const {
    return new Scene1();
}
