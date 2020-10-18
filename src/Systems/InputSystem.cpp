#include "../../include/Systems/InputSystem.hpp"

#include "../../include/Components/CameraComponent.hpp"
#include "../../include/Events/EventDispatcher.hpp"
#include "../../include/Rendering/GameWindow.hpp"

#include <GLFW/glfw3.h>

InputSystem::InputSystem(entt::registry& registry)
    : System{registry} {
    SUBSCRIBE(MouseMoveEvent, handleMouseInput);
    SUBSCRIBE(ScrollEvent, handleScroll);
}

void InputSystem::handleMouseInput(const MouseMoveEvent& e) {
    if (glfwGetMouseButton(e.window->getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        CameraComponent& camera = m_registry.get<CameraComponent>(m_registry.view<CameraComponent>().front());
        float dx = e.x - e.prevX;
        float dy = e.y - e.prevY;

        float phi = camera.phi + dx;
        camera.phi = phi - 360 * glm::floor(phi / 360);

        camera.theta = glm::clamp(camera.theta - dy, 1.0f, 179.0f);
        camera.updateViewMatrix();
    }
}

void InputSystem::handleScroll(const ScrollEvent& e) {
    CameraComponent& camera = m_registry.get<CameraComponent>(m_registry.view<CameraComponent>().front());
    camera.distance = glm::clamp(camera.distance - (float)e.dy, 0.1f, 10.0f);
    camera.updateViewMatrix();
}

void InputSystem::update(int dt) {
}
