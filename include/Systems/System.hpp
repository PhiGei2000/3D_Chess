#pragma once
#include <entt/entt.hpp>

class System {
  protected:
    entt::registry& m_registry;

  public:
    inline System(entt::registry& registry)
        : m_registry{registry} {
    }

    virtual void update(int dt) = 0;
};
