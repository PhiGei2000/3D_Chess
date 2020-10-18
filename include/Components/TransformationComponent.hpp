#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

struct TransformationComponent {
    glm::vec3 position = glm::vec3{0.0f};
    glm::quat rotation = glm::quat();
    glm::vec3 scale = glm::vec3{1.0f};

    const glm::mat4 getMatrix() const {
        return glm::translate(position) * glm::scale(scale) * glm::toMat4(rotation);
    }
};