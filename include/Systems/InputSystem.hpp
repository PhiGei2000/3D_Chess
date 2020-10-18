#pragma once
#include "System.hpp"

struct MouseMoveEvent;
struct ScrollEvent;

class InputSystem : public System {
  private:    
    void handleMouseInput(const MouseMoveEvent& e);
    void handleScroll(const ScrollEvent& e);

    public:
      InputSystem(entt::registry& registry);

      void update(int dt) override;
};