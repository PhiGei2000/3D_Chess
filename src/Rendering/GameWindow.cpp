#include "../../include/Rendering/GameWindow.hpp"

#include "../../include/Events/EventDispatcher.hpp"
#include "../../include/Resources/ResourceManager.hpp"

#include "../../include/Systems/GameRenderSystem.hpp"
#include "../../include/Systems/InputSystem.hpp"

#include "../../include/Components/MeshComponent.hpp"
#include "../../include/Components/TransformationComponent.hpp"
#include "../../include/Components/CameraComponent.hpp"

#include "../../include/Utility/SceneLoader.hpp"

#include <exception>

GameWindow::GameWindow(int width, int height, const char* title)
    : m_regsitry(entt::registry()) {

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
    m_systems.emplace_back(new GameRenderSystem(m_regsitry));
    m_systems.emplace_back(new InputSystem(m_regsitry));    

    entt::entity entity = m_regsitry.create();
    CameraComponent& camera = m_regsitry.emplace<CameraComponent>(entity);
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);

    camera.updateViewMatrix();
    camera.updateProjectionMatrix(width, height);

    Utility::SceneLoader::loadScene("scene.json", m_regsitry);
}

void GameWindow::run() {
    while (!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int time = (int)(glfwGetTime() / 1000);

        for(auto system : m_systems) {
            system->update(time);
        }

        glfwSetTime(0);
        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }
}

GLFWwindow* GameWindow::getWindow() const {
    return m_window;
}
