#pragma once
#include "../Rendering/Light.hpp"
#include "System.hpp"
#include <glm/glm.hpp>

struct WindowSizeEvent;

class GameRenderSystem : public System {
  private:
    DirectionalLight m_light;

    void handleResize(const WindowSizeEvent& e);

  public:
    GameRenderSystem(entt::registry& registry);

    void update(int dt) override;
};
