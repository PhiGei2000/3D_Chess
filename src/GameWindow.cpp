#include "../include/GameWindow.hpp"

#include "../include/EventDispatcher.hpp"

#include "../include/Mesh.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Transformation.hpp"

#include <exception>

GameWindow::GameWindow(int width, int height, const char* title)
    : m_regsitry(entt::registry()), m_renderer(m_regsitry) {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    if (!glfwInit()) {
        throw std::exception("GLFW init not succeeded!");
    }

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!m_window) {
        glfwTerminate();

        throw std::exception("Error while creating window");
    }

    glfwMakeContextCurrent(m_window);

    glewInit();

    glfwSetFramebufferSizeCallback(m_window, GameWindow::sizeCallback);
    glfwSetKeyCallback(m_window, GameWindow::keyCallback);
    glfwSetCursorPosCallback(m_window, GameWindow::mouseMoveCallback);
    glfwSetScrollCallback(m_window, GameWindow::mouseScrollCallback);

    glfwSetWindowUserPointer(m_window, this);

    SUBSCRIBE(KeyEvent, handleKeyEvent);
}

void GameWindow::sizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(window);

    WindowSizeEvent e = {gameWindow, width, height};
    EventDispatcher::invoke(e);
}

void GameWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(window);

    KeyEvent e = {gameWindow, key, scancode, action, mods};
    EventDispatcher::invoke(e);
}

void GameWindow::mouseMoveCallback(GLFWwindow* window, double x, double y) {
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(window);

    MouseMoveEvent e{gameWindow, gameWindow->lastMouseX, gameWindow->lastMouseY, x, y};
    EventDispatcher::invoke(e);

    gameWindow->lastMouseX = x;
    gameWindow->lastMouseY = y;
}

void GameWindow::mouseScrollCallback(GLFWwindow* window, double dx, double dy) {
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(window);

    ScrollEvent e{gameWindow, dx, dy};
    EventDispatcher::invoke(e);
}

void GameWindow::handleKeyEvent(const KeyEvent& e) {
    if (e.key == GLFW_KEY_F && e.action == GLFW_PRESS) {
        if (!m_fullscreen) {
            glfwMaximizeWindow(m_window);
            m_fullscreen = true;
        }
        else {
            glfwRestoreWindow(m_window);
            m_fullscreen = false;
        }
    }
    if (e.key == GLFW_KEY_ESCAPE && e.action == GLFW_PRESS) {
        glfwDestroyWindow(m_window);
    }
}

void GameWindow::init() {
    entt::entity entity = m_regsitry.create();
    m_regsitry.emplace<Transformation>(entity, glm::vec3(), glm::quat(), glm::vec3(1.0f));
    const Mesh* mesh = ResourceManager::getResource<Mesh>("cube");
}

void GameWindow::run() {
    while (!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_renderer.render();

        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }
}

GLFWwindow* GameWindow::getWindow() const {
    return m_window;
}