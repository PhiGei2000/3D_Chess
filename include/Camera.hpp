#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera {
    float distance = 5;
    float phi = 0;
    float theta = 45;
    float fov = 60;

    glm::vec3 getPosition() const;

    glm::vec3 getUpVector() const;

    glm::mat4 getViewMatrix() const;

    glm::mat4 getProjectionMatrix(const float width, const float height) const;
};