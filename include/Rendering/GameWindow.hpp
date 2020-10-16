#pragma once
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>

#include "../Systems/GameRenderSystem.hpp"

struct KeyEvent;

class GameWindow {
private:
	GLFWwindow* m_window;	
	GameRenderSystem m_renderer;
	bool m_fullscreen = false;
    double lastMouseX, lastMouseY;

    entt::registry m_regsitry;

    static void sizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseMoveCallback(GLFWwindow* window, double x, double y);
    static void mouseScrollCallback(GLFWwindow* window, double dx, double dy);

    void handleKeyEvent(const KeyEvent& e);
public:
	GameWindow(int width, int height, const char* title);

    void init();

    void run();

    GLFWwindow* getWindow() const;
};

