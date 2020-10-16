#pragma once
#include <entt/entt.hpp>
#include <glm/glm.hpp>

struct WindowSizeEvent;
struct MouseMoveEvent;
struct ScrollEvent;

class GameRenderSystem {
  private:
    entt::registry& m_registry;
    glm::vec2 m_size;

    void handleResize(const WindowSizeEvent& e);
    void handleMouseInput(const MouseMoveEvent& e);
    void handleScroll(const ScrollEvent& e);

  public:
    GameRenderSystem(entt::registry& registry);

    void update();
};
