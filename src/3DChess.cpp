#include "../include/Rendering/GameWindow.hpp"
#include "../include/Resources/ResourceManager.hpp"
#include "../include/Systems/GameRenderSystem.hpp"
#include <iostream>

void initResources();

int main() {
    GameWindow window = GameWindow(800, 600, "3D Chess");

    ResourceManager::init();

    window.init();

    window.run();
}
