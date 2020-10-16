#pragma once
#include <glm/glm.hpp>

struct DirectionalLight {
    glm::vec3 direction = glm::vec3{1.0f, -1.0f, 0.0f};
    glm::vec3 color = glm::vec3{0.5f, 0.5f, 0.5f};
};