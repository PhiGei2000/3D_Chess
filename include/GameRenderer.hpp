#pragma once
#include <entt/entt.hpp>
#include "Camera.hpp"

struct WindowSizeEvent;
struct MouseMoveEvent;
struct ScrollEvent;

class GameRenderer {
private:	
    entt::registry &m_registry;
    Camera m_camera;

    glm::vec2 m_size;    

    void handleResize(const WindowSizeEvent& e);
    void handleMouseInput(const MouseMoveEvent& e);
    void handleScroll(const ScrollEvent& e);

  public:
	GameRenderer(entt::registry& registry);

	void render();	
};

