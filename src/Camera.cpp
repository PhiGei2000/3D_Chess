#include "../include/Camera.hpp"

glm::vec3 Camera::getPosition() const {    
    return distance * glm::vec3{
        glm::cos(glm::radians(phi)) * glm::sin(glm::radians(theta)),
        glm::cos(glm::radians(theta)),
        glm::sin(glm::radians(phi)) * glm::sin(glm::radians(theta))
    };
}

glm::vec3 Camera::getUpVector() const {
    glm::vec3 position = getPosition();
    glm::vec3 n = glm::cross(glm::vec3{0, 1, 0}, position);
    return glm::normalize(glm::cross(position, n));
}

glm::mat4 Camera::getViewMatrix() const {
    glm::vec3 position = getPosition();
    glm::vec3 up = getUpVector();

    return glm::lookAt(position, glm::vec3{0.0f, 0.0f, 0.0f}, up);
}

glm::mat4 Camera::getProjectionMatrix(const float width, const float height) const {
    return glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
}