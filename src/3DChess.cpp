#include "../include/GameRenderer.hpp"
#include "../include/GameWindow.hpp"
#include <iostream>

void initResources();

int main() {
    GameWindow window = GameWindow(800, 600, "3D Chess");

    initResources();

    window.run();
}

#include "../include/Geometry.hpp"
#include "../include/Material.hpp"
#include "../include/ObjLoader.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Shader.hpp"
#include "../include/Texture.hpp"

void initResources() {
    const Geometry* board = Utility::ObjLoader::loadObj("Resources/models/board.obj");    
    ResourceManager::addResource("modelBoard", board);

    Shader* shader = new Shader("Resources/shaders/mesh.vert", "Resources/shaders/mesh.frag", "Resources/shaders/mesh.geom");
    ResourceManager::addResource("meshShader", shader);

    Texture* diffuse = new Texture("Resources/textures/Wood050_2K_Color.jpg");
    Texture* normal = new Texture("Resources/textures/Wood050_2K_Normal.jpg");
    Texture* specular = new Texture("Resources/textures/Wood050_2K_Displacement.jpg");

    Material* boardMaterial = new Material();
    boardMaterial->diffuse = diffuse;
    boardMaterial->normal = normal;
    boardMaterial->specular = specular;
    ResourceManager::addResource("materialBoard", boardMaterial);
}
