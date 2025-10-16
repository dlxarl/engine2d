#include "Engine.h"
#include "RectangleShape.h"
#include "CircleShape.h"
#include "LineShape.h"

int main() {
    Engine engine(800, 600, 60.0f);
    if (!engine.init()) return -1;

    RectangleShape rect({100, 100}, 200, 120, {1, 0, 0, 1});
    CircleShape circle({400, 300}, 60, {0, 1, 0, 1});
    LineShape line({100, 500}, {700, 500}, {0, 0, 1, 1});

    engine.addShape(&rect);
    engine.addShape(&circle);
    engine.addShape(&line);

    engine.run();
    return 0;
}
#