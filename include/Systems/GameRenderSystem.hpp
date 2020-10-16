#pragma once
#include "System.hpp"
#include "../Rendering/Light.hpp"
#include <glm/glm.hpp>

struct WindowSizeEvent;
struct MouseMoveEvent;
struct ScrollEvent;

class GameRenderSystem : public System {
  private:    
    glm::vec2 m_size;
    DirectionalLight m_light;

    void handleResize(const WindowSizeEvent& e);
    void handleMouseInput(const MouseMoveEvent& e);
    void handleScroll(const ScrollEvent& e);

  public:
    GameRenderSystem(entt::registry& registry);

    void update(int dt) override;
};
