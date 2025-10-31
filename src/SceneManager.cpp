#include "SceneManager.h"

#include <iostream>

SceneManager::SceneManager(Scene* startScene) : current(startScene) {}

SceneManager::~SceneManager() {
    delete current;
}

void SceneManager::update(float dt, const Input& input) {
    if (!current) return;

    current->update(dt, input);

    if (current->isFinished()) {
        Scene* next = current->nextScene();
        delete current;
        current = next;

        if (!current) {
            std::cout << "SceneManager: no next scene, terminating." << std::endl;
            return;
        }
    }
}

void SceneManager::draw(Renderer& r) {
    if (current)
        current->draw(r);
}

bool SceneManager::isRunning() const {
    return current != nullptr;
}