#pragma once
#include "Input.h"
#include <iostream>

class DefinePoint {
private:
    bool enabled = false;

public:
    void setEnabled(bool state) { enabled = state; }
    bool isEnabled() const { return enabled; }

    void update(const Input& input) {
        if (!enabled) return;

        if (input.isMouseJustPressed(0)) {
            std::cout << "Clicked at: (" 
                      << input.mouseX << ", " 
                      << input.mouseY << ")" << std::endl;
        }
    }
};