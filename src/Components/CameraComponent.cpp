#include "../../include/Components/CameraComponent.hpp"

glm::vec3 CameraComponent::getPosition() const {
    return distance * glm::vec3{
                          glm::cos(glm::radians(phi)) * glm::sin(glm::radians(theta)),
                          glm::cos(glm::radians(theta)),
                          glm::sin(glm::radians(phi)) * glm::sin(glm::radians(theta))};
}

glm::vec3 CameraComponent::getUpVector() const {
    glm::vec3 position = getPosition();
    glm::vec3 n = glm::cross(glm::vec3{0, 1, 0}, position);
    return glm::normalize(glm::cross(position, n));
}

void CameraComponent::updateViewMatrix() {
    glm::vec3 position = getPosition();
    glm::vec3 up = getUpVector();

    viewMatrix = glm::lookAt(position, glm::vec3{0.0f, 0.0f, 0.0f}, up);
}

void CameraComponent::updateProjectionMatrix(const float width, const float height) {
    projectionMatrix = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
}

const glm::mat4& CameraComponent::getViewMatrix() const {
    return viewMatrix;
}

const glm::mat4& CameraComponent::getProjectionMatrix() const {
    return projectionMatrix;
}