#include "../../include/Systems/GameRenderSystem.hpp"

#include "../../include/Events/EventDispatcher.hpp"
#include "../../include/Rendering/GameWindow.hpp"
#include "../../include/Rendering/Light.hpp"

#include "../../include/Resources/Geometry.hpp"
#include "../../include/Resources/Material.hpp"
#include "../../include/Resources/ResourceManager.hpp"
#include "../../include/Resources/Shader.hpp"

#include "../../include/Components/CameraComponent.hpp"
#include "../../include/Components/MeshComponent.hpp"
#include "../../include/Components/TransformationComponent.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

void GameRenderSystem::handleResize(const WindowSizeEvent& e) {
    glViewport(0, 0, e.width, e.height);
    m_size = glm::vec2{e.width, e.height};
}

// void GameRenderSystem::handleMouseInput(const MouseMoveEvent& e) {
//     if (glfwGetMouseButton(e.window->getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
//         float deltaX = e.x - e.prevX;
//         float deltaY = e.y - e.prevY;

//         float newPhi = m_camera.phi + deltaX;
//         m_camera.phi = newPhi - 360 * glm::floor(newPhi / 360);

//         m_camera.theta = glm::clamp(m_camera.theta - deltaY, 1.0f, 179.0f);
//     }
// }

// void GameRenderSystem::handleScroll(const ScrollEvent& e) {
//     m_camera.distance = glm::clamp(m_camera.distance - (float)e.dy, 0.1f, 10.0f);
// }

GameRenderSystem::GameRenderSystem(entt::registry& registry)
    : System{registry} {
    // SUBSCRIBE(WindowSizeEvent, handleResize);
    // SUBSCRIBE(MouseMoveEvent, handleMouseInput);
    // SUBSCRIBE(ScrollEvent, handleScroll);
}

void GameRenderSystem::update(int dt) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    const CameraComponent& camera = m_registry.get<CameraComponent>(m_registry.view<CameraComponent>().front());
    glm::mat4 viewMatrix = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix(m_size.x, m_size.y);
    glm::vec3 viewPos = camera.getPosition();

    auto& view = m_registry.view<MeshComponent, TransformationComponent>();
    view.each([&](MeshComponent& mesh, const TransformationComponent& transform) {
        for(auto& [geometry, material] : mesh.data) {
            material->shader->bind();
            material->shader->upload("view", viewMatrix);
            material->shader->upload("projection", projection);
            material->shader->upload("model", transform.getMatrix());

            material->shader->upload("material", *material);
            material->shader->upload("light", m_light);

            material->shader->upload("viewPos", viewPos);

            geometry->draw();
        }
    });
}
