#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

struct TransformationComponent {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    const glm::mat4 getMatrix() const {
        return glm::translate(position) * glm::scale(scale) * glm::toMat4(rotation);
    }
};