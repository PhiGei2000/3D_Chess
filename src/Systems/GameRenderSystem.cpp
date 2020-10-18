#include "../../include/Systems/GameRenderSystem.hpp"

#include "../../include/Events/EventDispatcher.hpp"
#include "../../include/Rendering/GameWindow.hpp"
#include "../../include/Rendering/Light.hpp"

#include "../../include/Resources/Geometry.hpp"
#include "../../include/Resources/Material.hpp"
#include "../../include/Resources/ResourceManager.hpp"
#include "../../include/Resources/Shader.hpp"

#include "../../include/Components/CameraComponent.hpp"
#include "../../include/Components/MeshComponent.hpp"
#include "../../include/Components/TransformationComponent.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

void GameRenderSystem::handleResize(const WindowSizeEvent& e) {
    glViewport(0, 0, e.width, e.height);

    m_registry.view<CameraComponent>().each(
        [&](CameraComponent& camera) {
            if (e.height != 0) {
                camera.updateProjectionMatrix(e.width, e.height);
            }
        });
}

GameRenderSystem::GameRenderSystem(entt::registry& registry)
    : System{registry} {
    SUBSCRIBE(WindowSizeEvent, handleResize);
    glViewport(0, 0, 800, 600);
}

void GameRenderSystem::update(int dt) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    const CameraComponent& camera = m_registry.get<CameraComponent>(m_registry.view<CameraComponent>().front());
    const glm::mat4& viewMatrix = camera.getViewMatrix();
    const glm::mat4& projection = camera.getProjectionMatrix();
    glm::vec3 viewPos = camera.getPosition();

    auto& view = m_registry.view<MeshComponent, TransformationComponent>();
    view.each([&](MeshComponent& mesh, const TransformationComponent& transform) {
        Shader* shader = mesh.material->shader;
        shader->bind();
        shader->upload("view", viewMatrix);
        shader->upload("projection", projection);
        shader->upload("model", transform.getMatrix());

        mesh.material->use();

        shader->upload("light", m_light);
        shader->upload("viewPos", viewPos);
        mesh.geometry->draw();
    });
}
